/* 
 * File:   BoolFunc.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:55 PM
 */

#include "BoolFunc.h"
#include "xbool.hpp"

BoolFunc::BoolFunc() : Node() {
}

BoolFunc::BoolFunc(const BoolFunc& orig) : Node(orig), _operand(orig._operand), _operator(orig._operator) {
}

BoolFunc::~BoolFunc() {

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
        (*it)->operator =(value);
        ++it;
    }
}

bool BoolFunc::operator <(const BoolFunc& comp) const {
    return (complexity() < comp.complexity());
}

xbool BoolFunc::forward(ClosedList* list) {
    if (!list) {
        ClosedList _list;
        return this->forward(&_list);
    }
    if (_operand.size() == 1)
        return _operand.front()->forward(list);

    OperatorCont::iterator it = _operator.begin();
    OperatorCont::iterator ite = _operator.end();

    NodeCont::iterator itx = _operand.begin();
    NodeCont::iterator itxe = _operand.end();

    xbool result = (*itx)->forward(list);
    itx++;

    while (it != ite && itx != itxe) {
        result = (*it)->execute(result, (*itx)->forward(list));
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
        return _operand.front()->backward(list);

    OperatorCont::iterator it = _operator.begin();
    OperatorCont::iterator ite = _operator.end();

    NodeCont::iterator itx = _operand.begin();
    NodeCont::iterator itxe = _operand.end();

    xbool result = (*itx)->backward(list);
    itx++;

    while (it != ite && itx != itxe) {
        result = (*it)->execute(result, (*itx)->backward(list));
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
    _operand.push_back(&no);
}

void BoolFunc::addBoolFunc(BoolFunc& func) {
    NodeCont::iterator it = _operand.begin();
    NodeCont::iterator ite = _operand.end();

    OperatorCont::iterator itx = _operator.begin();
    OperatorCont::iterator itxe = _operator.end();

    if (_operand.size() == 1) {
        (*it)->addBoolFunc(func);
        return;
    }

    while (it != ite && itx != itxe && (*itx)->getCode() == AND) {
        (*it)->addBoolFunc(func);
        ++it;
    }
}