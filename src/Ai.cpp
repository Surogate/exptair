/* 
 * File:   Ai.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 2:46 PM
 */

#include <map>

#include "Ai.h"
#include "Node.h"
#include "InputFileParser.hpp"

void Ai::loadPath(const std::string& filePath) {
    InputFileParser parser;
    parser.parseFile(filePath, *this);
}

void Ai::addNode(Node* no) {
    _nodeList[no->getLetter()] = no;
}

Node* Ai::getNode(char letter) {
    NodeCont::iterator it = _nodeList.find(letter);

    if (it != _nodeList.end()) {
        return it->second;
    }
    return 0;
}

void Ai::forward()  {
    
}

void Ai::backward() {
    
}
