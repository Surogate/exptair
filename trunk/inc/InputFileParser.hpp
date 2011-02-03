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
#include "Singleton.hpp"

class InputFileParser : public AParser, public Singleton<InputFileParser> {
    SINGLETON_CLASS(InputFileParser);
public:
    typedef std::map<std::string, Oper*> OperatorMap;

    InputFileParser();
    bool parseFile(const std::string& filepath, Ai& to);
    bool parseLine(Ai& to);
    bool parseBaseAttr(Ai& to);
    bool parseComplexAttr(Ai& to);
    bool parseInterogation(Ai& to);
    bool parseContinue();
    bool parseForward(Ai& to);
    bool parseLoad(Ai& to);

private:

    bool parseBoolFunc(Ai& to, BoolFunc& in);
    SmartPtr<Node> parseNode(Ai& to);
    Oper* parseOper();
    OperatorMap _operMap;
};

#endif	/* INPUTFILEPARSER_HPP */

