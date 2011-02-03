/* 
 * File:   Node.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:53 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <list>
#include <map>
#include <set>
#include "xbool.hpp"

class BoolFunc;

//Les variable booléenne 
class Node {
public:
    typedef std::list<BoolFunc> FuncList;
    typedef std::map<char, bool> ClosedList;

    Node();
    Node(const char letters);
    Node(const Node& orig);
    virtual ~Node();

    Node& operator=(const Node& orig);
    
    virtual void addBoolFunc(const BoolFunc& func);
    virtual xbool forward(ClosedList* list = 0);
    virtual xbool backward(ClosedList* list = 0);

    virtual void operator=(xbool);
    virtual std::string dump() const;
    char getLetter() const;

    virtual int complexity() const;

protected:
    void addInClosedList(ClosedList& list, char letter);
    
private:
    xbool _value;
    bool _evaluate; //a-t-on deja calculé la valeur ?
    bool _compEvaluate; //est-on en train d'evaluer la difficulté
    const char _let; // la lettre
    FuncList _boolFuncList; // liste triee des fonction qui donne la valeur

    xbool askUserToDefine();
};

#endif	/* NODE_H */

