/* 
 * File:   Oper.cpp
 * Author: ancelf
 * 
 * Created on January 13, 2011, 3:34 PM
 */

#include "Oper.h"
#include "Node.h"
#include "AParser.hpp"

bool And::operator()(Node& a, Node& b) const {
    return a() && b();
}

int And::complexity() const {
    return 1;
}

Oper* And::clone() {
    return new And(*this);
}

bool Or::operator ()(Node& a, Node& b) const {
    return a() || b();
}

int Or::complexity() const {
    return 2;
}

Oper* Or::clone() {
    return new Or(*this);
}