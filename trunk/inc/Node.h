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
    
    void addBoolFunc(BoolFunc& func);
    virtual int forward(ClosedList* list = 0);
    virtual bool operator()();
    void operator=(bool);
    char getLetter() const;

    virtual int complexity();
protected:
    void addInClosedList(ClosedList& list, char letter);
    
private:
    bool _value;
    bool _evaluate; //a-t-on deja calculé la valeur ?
    bool _compEvaluate; //est-on en train d'evaluer la difficulté
    const char _let; // la lettre
    FuncList _boolFuncList; // liste triee des fonction qui peuvent donné la valeur
};

#endif	/* NODE_H */

