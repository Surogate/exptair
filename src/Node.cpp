/* 
 * File:   Node.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:53 PM
 */

#include <list>


#include "Node.h"
#include "BoolFunc.h"

Node::Node() : _value(false), _evaluate(false), _let(0) {
}

Node::Node(const char letter) : _value(false), _let(letter) {
}

Node::Node(const Node& orig) : _let(orig._let) {
    this->operator =(orig);
}

Node::~Node() {
}

Node& Node::operator=(const Node& orig) {
    if (this != &orig) {
        _value = orig._value;
        _evaluate = orig._evaluate;
        _compEvaluate = orig._compEvaluate;
        _boolFuncList = orig._boolFuncList;
    }
    return *this;
}


// ajoute une regle dans la liste, suivant sa complexite

void Node::addBoolFunc(Node& func) {
    int complexity = func.complexity();

    FuncList::iterator it = _boolFuncList.begin();
    FuncList::iterator ite = _boolFuncList.end();

    while (it != ite && it->complexity() < complexity) {
        ++it;
    }

    if (it != ite) {
        _boolFuncList.insert(it, func);
    } else {
        _boolFuncList.push_back(func);
    }
}

//on assigne une valeur par defaut a une node

void Node::operator=(bool val) {
    _evaluate = true;
    _value = val;
}

//on tente d'evaluer une node suivant ses regle

bool Node::operator ()() {
    if (!_evaluate) {
        _evaluate = true;
        FuncList::iterator it = _boolFuncList.begin();
        FuncList::iterator ite = _boolFuncList.begin();

        while (it != ite && it->operator ()()) {
            ++it;
        }

        if (it != ite) {
            _value = true;
        }
    }
    return _value;
}

// on evalue la dificulte d'evaluer une node

int Node::complexity() {
    int comp;
    if (_compEvaluate)
        return 1;
    if (_evaluate) {
        return 0;
    } else {
        comp = 0;
        _compEvaluate = true;
        FuncList::iterator it = _boolFuncList.begin();
        FuncList::iterator ite = _boolFuncList.end();

        while (it != ite) {
            if (comp < it->complexity())
                comp = it->complexity();
            ++it;
        }
        _compEvaluate = false;
        return comp;
    }
}
