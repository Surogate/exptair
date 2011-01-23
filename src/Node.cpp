/* 
 * File:   Node.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:53 PM
 */

#include <list>
#include <map>
#include <iostream>


#include "Node.h"
#include "BoolFunc.h"

Node::Node() : _value(xundefined), _evaluate(false), _let(0) {
}

Node::Node(const char letter) : _value(xundefined), _evaluate(false), _let(letter) {
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

char Node::getLetter() const {
    return _let;
}


// ajoute une regle dans la liste, suivant sa complexite

void Node::addBoolFunc(BoolFunc& func) {
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

void Node::operator=(xbool val) {
    _evaluate = true;
    _value = val;
}

xbool Node::forward(ClosedList* list) {
    char let = getLetter();

    if (_evaluate)
        return _value;

    if (!list) {
        ClosedList _list;
        return this->forward(&_list);
    }

    if (list->find(_let) == list->end()) {
        FuncList::iterator it = _boolFuncList.begin();
        FuncList::iterator ite = _boolFuncList.end();
        xbool answer = xundefined;

        list->operator [](_let) = true;
        while (it != ite) {
            xbool result = it->forward(list);

            if (result == xfalse)
                answer = xfalse;
            if (result == xtrue) {
                this->operator =(xtrue);
                return xtrue;
            }
            ++it;
        }
        return answer;
    } else {
        return xreevaluate;
    }
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

void Node::addInClosedList(ClosedList& list, char letter) {
    list[letter] = true;
}
