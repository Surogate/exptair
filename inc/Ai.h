/* 
 * File:   Ai.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:46 PM
 */

#ifndef AI_H
#define	AI_H

#include <string>
#include <map>
#include "Node.h"

class Ai {
public:
    typedef std::map<char, Node*> NodeCont;

    void loadPath(const std::string& filepath);
    void addNode(Node* no);
    Node* getNode(char letter);
    void forward();
    void backward();
private:
     NodeCont _nodeList;
};

#endif	/* AI_H */

