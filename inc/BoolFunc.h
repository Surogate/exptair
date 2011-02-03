/* 
 * File:   BoolFunc.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 2:55 PM
 */

#ifndef BOOLFUNC_H
#define	BOOLFUNC_H

#include <vector>
#include <list>

#include "SmartPtr.hpp"
#include "Node.h"
#include "Oper.h"

// fonction booleenne

class BoolFunc : public Node {
public:
    typedef std::list< SmartPtr<Node> > NodeCont; //list des node
    typedef std::vector<Oper*> OperatorCont;

    BoolFunc();
    BoolFunc(const BoolFunc& orig);
    virtual ~BoolFunc();

    BoolFunc & operator =(const BoolFunc& orig);
    void operator =(xbool);
    bool operator<(const BoolFunc&) const;
    xbool forward(ClosedList* list = 0);
    xbool backward(ClosedList* list = 0);
    int complexity() const;
    void addBoolFunc(BoolFunc& func);
    void addOperator(Oper& op);
    void addOperand(SmartPtr<Node> no);
    bool containAPartOf(const BoolFunc& func) const;
    bool isStartByNot() const;
    void setStartByNot(bool value);
    void invertStartByNot();
    void addDynBoolFunc(SmartPtr<Node> func);
    void divideInAndBoolFunc(std::vector< SmartPtr<Node> >& in);
    std::string dump() const;

private:
    NodeCont _operand; // list des operand (A, B, C, etc)
    OperatorCont _operator; // list des operator (AND, OR, XOR, etc..)
    bool _startByNot; // true si elle commence par NOT
    bool _andFlags; // true si tout les element sont des AND
};

#endif	/* BOOLFUNC_H */

