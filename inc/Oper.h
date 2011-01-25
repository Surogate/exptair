/* 
 * File:   Oper.h
 * Author: ancelf
 *
 * Created on January 13, 2011, 3:34 PM
 */

#ifndef OPER_H
#define	OPER_H

#include "Singleton.hpp"
#include "xbool.hpp"

class Node;

// interface des operator possible
class Oper {
public:
    virtual ~Oper() {}
    virtual xbool execute(xbool a, xbool b) const = 0;
    virtual int complexity() const = 0;
    virtual operCode getCode() const = 0;
};

class And : public Oper, public Singleton<And> {
    SINGLETON_CLASS(And)
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

class Or : public Oper, public Singleton<Or> {
    SINGLETON_CLASS(Or)
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

#endif	/* OPER_H */

