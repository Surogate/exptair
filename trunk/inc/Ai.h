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
    Ai();
    typedef std::map<char, SmartPtr<Node> > NodeCont;
    typedef std::map<xbool, std::string> XBoolList;

    bool loadPath(const std::string& filepath);
    void addNode(SmartPtr<Node> no);
    SmartPtr<Node> getNode(char letter);
    void forward();
    void backward();
    std::string getXboolValue(xbool val) const;
private:
    NodeCont _nodeList;
    XBoolList _xboolValue;
};

#endif	/* AI_H */

