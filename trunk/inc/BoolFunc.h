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

#include "Node.h"
#include "Oper.h"

// fonction booleenne
class BoolFunc : public Node {
public:
    typedef std::list<Node*> NodeCont;
    typedef std::vector<Oper*> OperatorCont;

    BoolFunc();
    BoolFunc(const BoolFunc& orig);
    virtual ~BoolFunc();

    BoolFunc& operator =(const BoolFunc& orig);
    void operator =(xbool);
    bool operator<(const BoolFunc&) const;
    xbool forward(ClosedList* list = 0);
    xbool backward(ClosedList* list = 0);
    int complexity() const;
    void addBoolFunc(BoolFunc& func);
    void addOperator(Oper& op);
    void addOperand(Node& no);
    bool containAPartOf(const BoolFunc& func) const;
private:
    NodeCont _operand; 
    OperatorCont _operator;
};

#endif	/* BOOLFUNC_H */

