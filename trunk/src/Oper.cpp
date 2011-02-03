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

namespace Not {

    xbool execute(xbool a) {
        if (a == xtrue)
            return xfalse;
        if (a == xfalse)
            return xtrue;
        return a;
    }
}

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

std::string And::getValue() const {
    return "AND";
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

std::string Or::getValue() const {
    return "OR";
}

xbool AndNot::execute(xbool a, xbool b) const {
    b = Not::execute(b);
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    if (a == xtrue && b == xtrue)
        return xtrue;
    return xfalse;
}

int AndNot::complexity() const {
    return 1;
}

operCode AndNot::getCode() const {
    return ANDNOT;
}

std::string AndNot::getValue() const {
    return "AND NOT";
}

xbool OrNot::execute(xbool a, xbool b) const {
    b = Not::execute(b);
    if (a == xtrue || b == xtrue)
        return xtrue;
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    return xfalse;
}

int OrNot::complexity() const {
    return 2;
}

operCode OrNot::getCode() const {
    return ORNOT;
}

std::string OrNot::getValue() const {
    return "OR NOT";
}

xbool Xor::execute(xbool a, xbool b) const {
    if ((a == xtrue || b == xtrue) && !(a == xtrue && b == xtrue))
        return xtrue;
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    return xfalse;
}

int Xor::complexity() const {
    return 3;
}

operCode Xor::getCode() const {
    return XOR;
}

std::string Xor::getValue() const {
    return "XOR";
}

xbool XorNot::execute(xbool a, xbool b) const {
    b = Not::execute(b);
    if ((a == xtrue || b == xtrue) && !(a == xtrue && b == xtrue))
        return xtrue;
    if (a == xreevaluate || b == xreevaluate)
        return xreevaluate;
    if (a == xundefined || b == xundefined)
        return xundefined;
    return xfalse;
}

int XorNot::complexity() const {
    return 4;
}

operCode XorNot::getCode() const {
    return XORNOT;
}

std::string XorNot::getValue() const {
    return "XOR NOT";
}