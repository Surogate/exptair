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

namespace Not {
    xbool execute(xbool a);
};

// interface des operator
class Oper {
public:

    virtual ~Oper() {}
    virtual xbool execute(xbool a, xbool b) const = 0;
    virtual int complexity() const = 0;
    virtual operCode getCode() const = 0;
};

class And : public Oper, public Singleton<And> {
    SINGLETON_CLASS(And);
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

class Or : public Oper, public Singleton<Or> {
    SINGLETON_CLASS(Or);
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

class AndNot : public Oper, public Singleton<AndNot> {
    SINGLETON_CLASS(AndNot);
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

class OrNot : public Oper, public Singleton<OrNot> {
    SINGLETON_CLASS(OrNot);
    xbool execute(xbool a, xbool b) const;
    int complexity() const;
    operCode getCode() const;
};

#endif	/* OPER_H */

