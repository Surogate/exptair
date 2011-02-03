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
#include "SmartPtr.hpp"

class Ai {
public:
    typedef std::map<char, SmartPtr<Node> > NodeCont;

    bool loadPath(const std::string& filepath);
    void addNode(SmartPtr<Node> no);
    SmartPtr<Node> getNode(char letter);
    void forward();
    void backward();
private:
     NodeCont _nodeList;
};

#endif	/* AI_H */

