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
        while ((parseLine(to) && consumeNewLine()) || consumeNewLine());
        if (eof())
            return true;
        else
            std::cout << "error at line " << getLineConsumed() << " letter " << getLetterPos() << " letter value " << getTextIterator() << std::endl;
    } else
        std::cout << "cannot load " << filepath << std::endl;
    return false;
}

bool InputFileParser::parseLine(Ai& to) {
    return (parseComplexAttr(to) || parseBaseAttr(to));
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
    if (char_('(')) {
        BoolFunc* func = new BoolFunc;
        if (parseBoolFunc(to, *func) && char_(')')) {
            SmartPtr<Node> node = func;
            return node;
        }
        delete func;
    }
    return SmartPtr<Node> ();
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

bool InputFileParser::parseBaseAttr(Ai& to) {
    if (char_('=')) {
        BoolFunc right;
        if (parseBoolFunc(to, right)) {
            right = xtrue;
            return true;
        }
    }
    if (readText("!=")) {
        BoolFunc right;
        if (parseBoolFunc(to, right)) {
            right = xfalse;
            return true;
        }
    }
    if (readText("?=")) {
        BoolFunc right;
        if (parseBoolFunc(to, right)) {
            right = xundefined;
            return true;
        }
    }
    return false;
}

bool InputFileParser::parseComplexAttr(Ai& to) {
    BoolFunc left;

    unsigned int iterator = getIterator();
    if (parseBoolFunc(to, left)) {
        if (char_('=')) {
            BoolFunc right;
            if (parseBoolFunc(to, right)) {
                right.addBoolFunc(left);
                return true;
            }
        }
    }
    setIterator(iterator);
    return false;
}

bool InputFileParser::parseInterogation(Ai& to) {
    BoolFunc left;

    if (parseBoolFunc(to, left)) {
        if (char_('?')) {
            xbool value = left.backward();
            std::cout << left.dump() << " is " << to.getXboolValue(value) << std::endl;
            return true;
        }
    }
    return false;
}

bool InputFileParser::parseContinue() {
    return !readText("exit");
}

bool InputFileParser::parseForward(Ai& to) {
    if(readText("forward")) {
        to.forward();
        return true;
    }
    return false;
}

bool InputFileParser::parseLoad(Ai& to) {
    std::string path;
    if (readText("load") && consumeSpace() && readQuotedTextIn(path)) {
        if (parseFile(path, to)) {
            std::cout << "load \"" << path << "\" ok !!§§" << std::endl;
            to.forward();
            return true;
        } else {
            std::cout << "load fail" << std::endl;
        }
    }
    return false;
}