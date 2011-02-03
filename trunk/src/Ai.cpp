/* 
 * File:   Ai.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:46 PM
 */

#include <map>
#include <iostream>

#include "Ai.h"
#include "Node.h"
#include "InputFileParser.hpp"

Ai::Ai() {
    _xboolValue[xtrue] = std::string("TRUE");
    _xboolValue[xfalse] = std::string("FALSE");
    _xboolValue[xreevaluate] = std::string("UNDEFINED");
    _xboolValue[xundefined] = std::string("UNDEFINED");
}

bool Ai::loadPath(const std::string& filePath) {
    return Singleton<InputFileParser>::Instance().parseFile(filePath, *this);
}

void Ai::addNode(SmartPtr<Node> no) {
    _nodeList[no->getLetter()] = no;
}

SmartPtr<Node> Ai::getNode(char letter) {
    NodeCont::iterator it = _nodeList.find(letter);

    if (it != _nodeList.end()) {
        return it->second;
    }
    return SmartPtr<Node > ();
}

void Ai::forward() {
    std::vector<char> nodeTrue;
    std::vector<char> nodeFalse;
    std::vector<char> nodeUnde;

    NodeCont::iterator it = _nodeList.begin();
    NodeCont::iterator ite = _nodeList.end();

    while (it != ite) {
        xbool result = (it->second)->forward();
        char value = it->second->getLetter();
        if (result == xtrue) {
            nodeTrue.push_back(value);
        } else if (result == xfalse) {
            nodeFalse.push_back(value);
        } else {
            nodeUnde.push_back(value);
        }
        ++it;
    }

    std::cout << "True" << std::endl;
    for (unsigned int i = 0; i < nodeTrue.size(); i++) {
        std::cout << nodeTrue[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "False" << std::endl;
    for (unsigned int i = 0; i < nodeFalse.size(); i++) {
        std::cout << nodeFalse[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Undefined" << std::endl;
    for (unsigned int i = 0; i < nodeUnde.size(); i++) {
        std::cout << nodeUnde[i] << " ";
    }
    std::cout << std::endl;
}

void Ai::backward() {
    bool continue_ = true;
    std::string str;
    std::cout << "command : ={func} ; !={func} ; ?={func} ; {func}={func} ; {func}? ; forward ; exit ; load \"{path}\"" << std::endl;
    while (continue_) {
        str.clear();
        std::getline(std::cin, str);
        if (str.size()) {
            Singleton<InputFileParser>::Instance().setText(str);
            if (!(Singleton<InputFileParser>::Instance().parseLine(*this)
                    || Singleton<InputFileParser>::Instance().parseInterogation(*this)
                    || Singleton<InputFileParser>::Instance().parseForward(*this)
                    || Singleton<InputFileParser>::Instance().parseLoad(*this))) {
                continue_ = Singleton<InputFileParser>::Instance().parseContinue();
                if (continue_)
                    std::cout << "invalid command" << std::endl;
            }
        }
    }
}

std::string Ai::getXboolValue(xbool val) const {
    XBoolList::const_iterator it = _xboolValue.find(val);
    if (it != _xboolValue.end()) {
        return it->second;
    }
    return std::string("OMGWTFBBQ something happen with xbool and XBoolList");
}

void Ai::devaluateAll() {
    NodeCont::iterator it = _nodeList.begin();
    NodeCont::iterator ite = _nodeList.end();

    while (it != ite) {
        it->second->devaluate();
        ++it;
    }
}