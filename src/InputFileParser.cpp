/* 
 * File:   ImputFileParser.cpp
 * Author: Errata
 * 
 * Created on 19 janvier 2011, 22:30
 */

#include "Singleton.hpp"
#include "InputFileParser.hpp"
#include "Oper.h"
#include <iostream>

InputFileParser::InputFileParser() {
    _operMap["*"] = &Singleton<And>::Instance();
    _operMap["+"] = &Singleton<Or>::Instance();
}

bool InputFileParser::parseFile(const std::string& filepath, Ai& to) {
    if (loadPath(filepath)) {
        while (parseline(to) && consumeNewLine() && !eof());
        if (eof())
            return true;
        else
            std::cout << "error at line" << getLineConsumed() << " letter " << getLetterPos() << std::endl;
    }
    return false;
}

bool InputFileParser::parseline(Ai& to) {
    BoolFunc func;

    if (parseBoolFunc(to, func)) {
        if (consumeSpace()  && char_('=') && consumeSpace()) {
            Node* node = parseNode(to);
            if (node) {
                node->addBoolFunc(func);
                to.addNode(node);
                return true;
            }
        }
    } else {
        if (consumeSpace() && char_('=') && consumeSpace()) {
            Node* node = parseNode(to);
            if (node) {
                node->operator =(true);
                to.addNode(node);
                return true;
            }
        }
    }
    return false;
}

bool InputFileParser::parseBoolFunc(Ai& to, BoolFunc& in) {
    Node* tmp = parseNode(to);
    if (tmp) {
        in.addOperand(*tmp);
        Oper* op;
        while ((op = parseOper()) && (tmp = parseNode(to))) {
            in.addOperator(*op);
            in.addOperand(*tmp);
        }
        if (!op && !tmp)
            return true;
    }
    return false;
}

Node* InputFileParser::parseNode(Ai& to) {
    std::string letter;
    Node* node;
    if (consumeSpace() && char_('A', 'Z', letter) && consumeSpace()) {
        node = to.getNode(letter[0]);
        if (!node) {
            node = new Node(letter[0]);
            return node;
        }
    }
    return 0;
}

Oper* InputFileParser::parseOper() {
    std::string letter;
    if (consumeSpace() && char_(letter) && consumeSpace()) {
        OperatorMap::iterator it = _operMap.find(letter);
        if (it != _operMap.end()) {
            return it->second;
        }
    }
    return 0;
}
