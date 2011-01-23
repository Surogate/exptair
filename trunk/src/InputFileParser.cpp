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
        if (parseline(to) && consumeNewLine()) {
            std::cout << "caca" << std::endl;
            while (parseline(to) && consumeNewLine());
        }
        if (eof())
            return true;
        else
            std::cout << "error at line " << getLineConsumed() << " letter " << getLetterPos() << " letter value " << getTextIterator() << std::endl;
    } else
        std::cout << "cannot load " << filepath << std::endl;
    return false;
}

bool InputFileParser::parseline(Ai& to) {
    BoolFunc func;

    if (parseBoolFunc(to, func)) {
        if (consumeSpace() && char_('=') && consumeSpace()) {
            Node* node = parseNode(to);
            if (node) {
                node->addBoolFunc(func);
                to.addNode(node);
                std::cout << "parse line ok" << std::endl;
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
        Oper* op = parseOper();
        tmp = parseNode(to);
        while (op && tmp) {
            in.addOperator(*op);
            in.addOperand(*tmp);
            op = parseOper();
            tmp = parseNode(to);
        }
        if (!op && !tmp)
            return true;
    }
    return false;
}

Node* InputFileParser::parseNode(Ai& to) {
    if (consumeSpace() && peek('A', 'Z')) {
        std::string letter;
        char_('A', 'Z', letter);
        std::cout << "parse node " << letter << std::endl;
        Node* node = to.getNode(letter[0]);
        if (!node) {
            node = new Node(letter[0]);
            return node;
        }
    }
    return 0;
}

Oper* InputFileParser::parseOper() {
    OperatorMap::iterator it = _operMap.begin();
    OperatorMap::iterator ite = _operMap.end();

    while (it != ite) {
        if (consumeSpace() && readText(it->first) && consumeSpace()) {
            std::cout << "operator " << it->first << std::endl;
            return it->second;
        }
        ++it;
    }
    return 0;
}
