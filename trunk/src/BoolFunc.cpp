/* 
 * File:   BoolFunc.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:55 PM
 */

#include "BoolFunc.h"
#include "xbool.hpp"

BoolFunc::BoolFunc() : Node(), _operand(), _operator(), _startByNot(false) {
}

BoolFunc::BoolFunc(const BoolFunc& orig) : Node(orig), _operator(orig._operator) {
    NodeCont::const_iterator it = orig._operand.begin();
    NodeCont::const_iterator ite = orig._operand.end();

    while (it != ite) {
        NodePtr* ptrx = *it;
        _operand.push_back(ptrx->clone());
        ++it;
    }
}

BoolFunc::~BoolFunc() {
    NodeCont::iterator it = _operand.begin();
    NodeCont::iterator ite = _operand.end();

    while (it != ite) {
        delete *it;
        ++it;
    }
}

BoolFunc& BoolFunc::operator =(const BoolFunc& orig) {
    Node::operator =(orig);
    _operand = orig._operand;
    _operator = orig._operator;
    return *this;
}

void BoolFunc::operator =(xbool value) {
    NodeCont::iterator it = _operand.begin();
    NodeCont::iterator ite = _operand.end();

    while (it != ite) {
        (*(*it))->operator =(value);
        ++it;
    }
}

bool BoolFunc::operator<(const BoolFunc& comp) const {
    return (complexity() < comp.complexity());
}

xbool BoolFunc::forward(ClosedList* list) {
    if (!list) {
        ClosedList _list;
        return this->forward(&_list);
    }
    if (_operand.size() == 1)
        return (*_operand.front())->forward(list);

    OperatorCont::iterator it = _operator.begin();
    OperatorCont::iterator ite = _operator.end();

    NodeCont::iterator itx = _operand.begin();
    NodeCont::iterator itxe = _operand.end();

    xbool result = (*itx)->getPtr()->forward(list);
    if (isStartByNot())
        result = Not::execute(result);
    itx++;

    while (it != ite && itx != itxe) {
        result = (*it)->execute(result, (*itx)->getPtr()->forward(list));
        ++it;
        ++itx;
    }
    return result;
}

xbool BoolFunc::backward(ClosedList* list) {
    if (!list) {
        ClosedList _list;
        return this->backward(&_list);
    }
    if (_operand.size() == 1)
        return (*_operand.front())->backward(list);

    OperatorCont::iterator it = _operator.begin();
    OperatorCont::iterator ite = _operator.end();

    NodeCont::iterator itx = _operand.begin();
    NodeCont::iterator itxe = _operand.end();

    xbool result = (*itx)->getPtr()->backward(list);
    itx++;

    while (it != ite && itx != itxe) {
        result = (*it)->execute(result, (*itx)->getPtr()->backward(list));
        ++it;
        ++itx;
    }
    return result;
}

//on evalue la difficulté a evaluer l'equation suivant les operator dedans

int BoolFunc::complexity() const {
    int result = 0;

    OperatorCont::const_iterator it = _operator.begin();
    OperatorCont::const_iterator ite = _operator.end();

    while (it != ite) {
        if (result < (*it)->complexity()) {
            result = (*it)->complexity();
        }
        ++it;
    }
    return result;
}

void BoolFunc::addOperator(Oper& op) {
    _operator.push_back(&op);
}

void BoolFunc::addOperand(Node& no) {
    _operand.push_back(new SmartPtr<Node, UnsafeContainer<Node> >(&no));
}

void BoolFunc::addBoolFunc(BoolFunc& func) {
    NodeCont::iterator it = _operand.begin();
    NodeCont::iterator ite = _operand.end();

    OperatorCont::iterator itx = _operator.begin();
    OperatorCont::iterator itxe = _operator.end();

    if (_operand.size() == 1) {
        (*it)->getPtr()->addBoolFunc(func);
        return;
    }

    while (it != ite && itx != itxe && (*itx)->getCode() == AND) {
        NodePtr* ptrx = *it;
        ptrx->getPtr()->addBoolFunc(func);
        ++it;
    }
}

bool BoolFunc::containAPartOf(const BoolFunc& func) const {
    NodeCont::const_iterator itx = func._operand.begin();
    NodeCont::const_iterator itxe = func._operand.end();

    while (itx != itxe) {
        NodeCont::const_iterator it = _operand.begin();
        NodeCont::const_iterator ite = _operand.end();

        while (it != ite && (*(*itx))->getLetter() != (*(*it))->getLetter()){
            ++it;
        }
        if (it == ite)
            return false;
        ++itx;
    }
    return true;
}

bool BoolFunc::isStartByNot() const {
    return _startByNot;
}

void BoolFunc::setStartByNot(bool value) {
    _startByNot = value;
}

void BoolFunc::addDynBoolFunc(BoolFunc* func) {
    _operand.push_back(new SmartPtr<Node>(func));
}