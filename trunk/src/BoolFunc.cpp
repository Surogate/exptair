/* 
 * File:   BoolFunc.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:55 PM
 */

#include "BoolFunc.h"

BoolFunc::BoolFunc() {
}

BoolFunc::BoolFunc(const BoolFunc& orig) : Node(orig), _operand(orig._operand), _operator(orig._operator) {}

BoolFunc::~BoolFunc() {
    for (unsigned int i = 0; i < _operator.size(); i++) {
        delete _operator[i];
    }
}

BoolFunc& BoolFunc::operator =(const BoolFunc& orig) {
    Node::operator =(orig);
    _operand = orig._operand;

    OperatorCont::iterator it = _operator.begin();
    OperatorCont::iterator ite = _operator.end();

    while (it != ite) {
        _operator.push_back((*it)->clone());
        ++it;
    }
}

// on tente d'evaluer la valeur final de l'equation
bool BoolFunc::operator ()() {
    if (_operand.size() > 1 && _operator.size() > 0) {
        OperatorCont::iterator it = _operator.begin();
        OperatorCont::iterator ite = _operator.end();

        NodeCont::iterator itxb = ++_operand.begin();
        NodeCont::iterator itxe = _operand.end();

        Node result = (*_operand.begin())->operator ()();

        while (it != ite && itxb != itxe) {
            result = (*it)->operator ()(result, *(*itxb));
            ++it;
        }
        return result();
    }
    if (_operand.size() == 1) {
        return (*_operand.begin())->operator ()();
    }
    return false;
}

//on evalue la difficulté a evaluer l'equation suivant les operator dedans
int BoolFunc::compexity() {
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
    _operator.push_back(op.clone());
}

void BoolFunc::addOperand(Node& no) {
    _operand.push_back(&no);
}