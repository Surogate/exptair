/* 
 * File:   Node.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:53 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <list>

class BoolFunc;

//Les variable booléenne 
class Node {
public:
    typedef std::list<BoolFunc> FuncList;

    Node();
    Node(const char letters);
    Node(const Node& orig);
    virtual ~Node();
    Node& operator=(const Node& orig);
    
    void addBoolFunc(BoolFunc& func);
    virtual bool operator()();
    void operator=(bool);

    virtual int complexity();
private:
    bool _value;
    bool _evaluate; //a-t-on deja calculé la valeur ?
    bool _compEvaluate; //est-on en train d'evaluer la difficulté
    const char _let; // la lettre
    FuncList _boolFuncList; // liste triee des fonction qui peuvent donné la valeur
};

#endif	/* NODE_H */

