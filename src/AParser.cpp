/*
 * File:   AParser.cpp
 * Author: Errata
 *
 * Created on 29 septembre 2010, 11:21
 */

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "AParser.hpp"

bool AParser::loadPath(const std::string& path) {
    std::ifstream script(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    if (script.good()) {
        std::ifstream::pos_type fileSize = script.tellg();
        script.seekg(0, std::ios::beg);
        std::vector<char> bytes(fileSize);
        script.read(&bytes[0], fileSize);
        script.close();
        _file.assign(bytes.begin(), bytes.end());
        _iterator = 0;
        _size = _file.size();
        _lineConsumed = 1;
        _letterPos = 0;
        return true;
    }
    return false;
}

void AParser::setText(std::string& str) {
    _file = str;
    _iterator = 0;
    _size = _file.size();
    _lineConsumed = 1;
    _letterPos = 0;
}

bool AParser::char_(std::string& in) {
    if (!eof())
    {
        in += _file[_iterator];
        ++_iterator;
        return true;
    }
    return false;
}

bool AParser::char_(char c, std::string& in) {
    if (peek(c))
    {
        in += _file[_iterator];
        ++_iterator;
        return true;
    }
    return false;
}

bool AParser::char_(char from, char to, std::string& in) {
    if (peek(from, to))
    {
        in += _file[_iterator];
        ++_iterator;
        return true;
    }
    return false;
}

bool AParser::readQuotedText(const std::string& text) {
    if (char_('"') && readText(text) && char_('"')) {
        return true;
    }
    _iterator--;
    return false;
}

bool AParser::readText(const std::string& textConsumed) {
    unsigned int tmp = _iterator;
    for (unsigned int i = 0; i < textConsumed.size(); i++)
    {
        if (!char_(textConsumed[i]))
        {
            _iterator = tmp;
            return false;
        }
    }
    return true;
}

bool AParser::readQuotedTextIn(std::string& in) {
    unsigned int tmp = _iterator;
    if (char_('"'))
    {
        while (!peek('"'))
            if (!char_(in)) {
                _iterator = tmp;
                return false;
            }
        if (!char_('"')) {
            _iterator = tmp;
            return false;
        }
        return true;
    }
    return false;
}

bool AParser::readInt(int& in) {
    std::string num;
    int sign = 1;
    while (peek('+') || peek('-')) {
        if (char_('-'))
            sign = sign * -1;
        else
            char_('+');
    }
    while (char_('0', '9', num));
    if (num.size() && (std::stringstream(num) >> in)) {
        in = in * sign;
        return true;
    }
    return false;
}

bool AParser::readInt(unsigned int& in) {
    std::string num;
    while (char_('0', '9', num));
    if (num.size() && (std::stringstream(num) >> in)) {
        return true;
    }
    return false;
}

bool AParser::readFloat(float& in) {
    std::string num;
    int sign = 1;
    while (peek('+') || peek('-'))
    {
        if (char_('-'))
            sign = sign * -1;
        else
            char_('+');
    }
    while (char_('0', '9', num));
    if (char_('.', num)) {
        while (char_('0', '9', num));
    }
    if (num.size() && (std::stringstream(num) >> in))
    {
        in = in * sign;
        return true;
    }
    return false;
}

unsigned int AParser::getLineConsumed() {
    return _lineConsumed;
}

unsigned int AParser::getIterator() {
    return _iterator;
}

char AParser::getTextIterator() {
    return _file[_iterator];
}

unsigned int AParser::getLetterPos() {
    return _iterator - _letterPos;
}
