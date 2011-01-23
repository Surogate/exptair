/* 
 * File:   ImputFileParser.hpp
 * Author: Errata
 *
 * Created on 19 janvier 2011, 22:30
 */

#ifndef INPUTFILEPARSER_HPP
#define	INPUTFILEPARSER_HPP

#include "AParser.hpp"
#include "Ai.h"
#include "BoolFunc.h"

class InputFileParser : public AParser {
public:
    typedef std::map<std::string, Oper*> OperatorMap;

    InputFileParser();
    bool parseFile(const std::string& filepath, Ai& to);
    bool parseLine(const std::string& line, Ai& to);
private:
    bool parseLine(Ai& to);
    bool parseBoolFunc(Ai& to, BoolFunc& in);
    Node* parseNode(Ai& to);
    Oper* parseOper();

    OperatorMap _operMap;
};

#endif	/* INPUTFILEPARSER_HPP */

