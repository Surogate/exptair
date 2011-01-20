/*
 * File:   AParser.hpp
 * Author: Errata
 *
 * Created on 29 septembre 2010, 11:21
 */

#ifndef APARSER_HPP
#define	APARSER_HPP

#include <string>

class AParser {
public:
    bool loadPath(const std::string& path);
    void setText(std::string& str);
    inline bool eof();
    inline bool peek(char c);
    inline bool peek(char a, char b);
    inline bool char_(char c);
    bool char_(std::string& in);
    bool char_(char c, std::string& in);
    bool char_(char from, char to, std::string& in);
    bool readQuotedText(std::string text);
    bool readText(std::string text);
    bool readIdentifier(std::string& in);
    bool readInt(int& in);
    bool readInt(unsigned int& in);
    bool readFloat(float& in);
    bool consumeSpace();
    bool consumeNewLine();
    bool consumeBlanks();
    unsigned int getLineConsumed();
    unsigned int getIterator();
    char getTextIterator();
    unsigned int getLetterPos();

private:
    std::string _file;
    int _iterator;
    int _size;
    int _lineConsumed;
    int _letterPos;
};

inline bool AParser::eof() {
    return (_iterator >= _size);
}

inline bool AParser::peek(char c) {
    if (!eof())
        return (_file[_iterator] == c);
    return false;
}

inline bool AParser::peek(char a, char b) {
    if (!eof())
        return ((_file[_iterator] >= a) && (_file[_iterator] <= b));
    return false;
}

inline bool AParser::char_(char c) {
    if (peek(c)) {
        ++_iterator;
        return true;
    }
    return false;
}

inline bool AParser::consumeNewLine() {
    if (char_('\n')) {
        ++_lineConsumed;
        _letterPos = _iterator;
        return true;
    }
    return false;
}

inline bool AParser::consumeSpace() {
    while (char_(' ') || char_('\t'));
    return true;
}

inline bool AParser::consumeBlanks() {
    while (consumeSpace() || consumeNewLine());
    return true;
}

#endif	/* APARSER_HPP */

