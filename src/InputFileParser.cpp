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
    _operMap["*!"] = &Singleton<AndNot>::Instance();
    _operMap["+!"] = &Singleton<OrNot>::Instance();
}

bool InputFileParser::parseFile(const std::string& filepath, Ai& to) {
    if (loadPath(filepath)) {
        while (parseLine(to) && consumeNewLine());
        if (eof())
            return true;
        else
            std::cout << "error at line " << getLineConsumed() << " letter " << getLetterPos() << " letter value " << getTextIterator() << std::endl;
    } else
        std::cout << "cannot load " << filepath << std::endl;
    return false;
}

bool InputFileParser::parseLine(const std::string& line, Ai& to) {
    setText(line);
    return parseLine(to);
}

bool InputFileParser::parseLine(Ai& to) {
    BoolFunc left;

    if (parseBoolFunc(to, left)) {
        if (char_('=')) {
            BoolFunc right;
            if (parseBoolFunc(to, right)) {
                right.addBoolFunc(left);
                return true;
            }
        }
    } else {
        if (char_('=')) {
            BoolFunc right;
            if (parseBoolFunc(to, right)) {
                right = xtrue;
                return true;
            }
        }
    }
    return false;
}

bool InputFileParser::parseBoolFunc(Ai& to, BoolFunc& in) {
    if (char_('!'))
        in.setStartByNot(true);
    SmartPtr<Node> tmp = parseNode(to);
    Oper* op = 0;
    if (tmp.isInit()) {
        in.addOperand(tmp);
        do {
        op = parseOper();
        tmp = parseNode(to);
        if (op && tmp.isInit()) {
            in.addOperator(*op);
            in.addOperand(tmp);
        }
        } while (op && tmp.isInit());
        if (!op && !tmp.isInit())
            return true;
    }
    return false;
}

SmartPtr<Node> InputFileParser::parseNode(Ai& to) {
    char letter = 0;
    if (char_('A', 'Z', letter)) {
        SmartPtr<Node> node = to.getNode(letter);
        if (!node.isInit()) {
            SmartPtr<Node> Snode = new Node(letter);
            to.addNode(Snode);
            return Snode;
        }
        return node;
    }
    return SmartPtr<Node>();
}

Oper* InputFileParser::parseOper() {
    OperatorMap::iterator it = _operMap.begin();
    OperatorMap::iterator ite = _operMap.end();

    while (it != ite) {
        if (consumeSpace() && readText(it->first) && consumeSpace()) {
            return it->second;
        }
        ++it;
    }
    return 0;
}
