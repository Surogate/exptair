/* 
 * File:   Oper.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 3:34 PM
 */

#ifndef OPER_H
#define	OPER_H

class Node;

// interface des operator possible
class Oper {
public:
    ~Oper() {}
    virtual bool operator()(Node& a, Node& b) const = 0;
    virtual int complexity() const = 0;
    virtual Oper* clone() = 0;
};

class And : public Oper {
    bool operator()(Node& a, Node& b) const;
    int complexity() const;
    Oper* clone();
};

class Or : public Oper {
    bool operator()(Node& a, Node& b) const;
    int complexity() const;
    Oper* clone();
};

#endif	/* OPER_H */

