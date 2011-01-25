/* 
 * File:   Oper.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 3:34 PM
 */

#include "Oper.h"
#include "Node.h"
#include "AParser.hpp"
#include "xbool.hpp"

xbool And::execute(xbool a, xbool b) const {
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    if (a == xtrue && b == xtrue)
        return xtrue;
    return xfalse;
}

int And::complexity() const {
    return 1;
}

operCode And::getCode() const {
    return AND;
}

xbool Or::execute(xbool a, xbool b) const {
    if (a == xtrue || b == xtrue)
        return xtrue;
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    return xfalse;
}

int Or::complexity() const {
    return 2;
}

operCode Or::getCode() const {
    return OR;
}

