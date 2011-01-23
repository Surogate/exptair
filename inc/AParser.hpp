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
    void setText(const std::string& str);
    inline bool eof();
    inline bool peek(const char c);
    inline bool peek(const char a, const char b);
    inline bool char_(const char c);
    bool char_(std::string& in);
    bool char_(const char c, std::string& in);
    bool char_(const char from, const char to, std::string& in);
    bool char_(const char from, const char to, char& in);
    bool readQuotedText(const std::string& textToConsumed);
    bool readText(const std::string& textToConsumed);
    bool readQuotedTextIn(std::string& in);
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

inline bool AParser::peek(const char c) {
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
    if (readText("\r\n") || char_('\n') || char_('\r')) {
        ++_lineConsumed;
        _letterPos = _iterator;
        return true;
    }
    return false;
}

inline bool AParser::consumeSpace() {
    while (char_(' ') || char_('\t'));
    return !eof();
}

inline bool AParser::consumeBlanks() {
    while (consumeSpace() || consumeNewLine());
    return !eof();
}

#endif	/* APARSER_HPP */

