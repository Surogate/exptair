/* 
 * File:   xbool.hpp
 * Author: ancelf
 *
 * Created on January 21, 2011, 3:41 PM
 */

#ifndef XBOOL_HPP
#define	XBOOL_HPP

enum xbool {
    xtrue = 1,
    xfalse = 0,
    xundefined = -1,
    xreevaluate = -2
};

enum operCode {
    AND,
    OR
};

#endif	/* XBOOL_HPP */

