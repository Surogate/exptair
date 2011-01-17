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

bool AParser::LoadPath(const std::string& path) {
    std::ifstream script(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    if (script.good()) {
        std::ifstream::pos_type fileSize = script.tellg();
        script.seekg(0, std::ios::beg);
        std::vector<char> bytes(fileSize);
        script.read(&bytes[0], fileSize);
        script.close();
        _file.assign(bytes.begin(), bytes.end());
        iterator = 0;
        size = _file.size();
        lineConsumed = 1;
        letterPos = 0;
        return true;
    }
    return false;
}

void AParser::SetText(std::string& str) {
    _file = str;
    iterator = 0;
    size = _file.size();
    lineConsumed = 1;
    letterPos = 0;
}

bool AParser::char_(std::string& in) {
    if (!eof())
    {
        in += _file[iterator];
        ++iterator;
        return true;
    }
    return false;
}

bool AParser::char_(char c, std::string& in) {
    if (peek(c))
    {
        in += _file[iterator];
        ++iterator;
        return true;
    }
    return false;
}

bool AParser::char_(char from, char to, std::string& in) {
    if (peek(from, to))
    {
        in += _file[iterator];
        ++iterator;
        return true;
    }
    return false;
}

bool AParser::readQuotedText(std::string text) {
    if (char_('"') && readText(text) && char_('"')) {
        return true;
    }
    iterator--;
    return false;
}

bool AParser::readText(std::string textConsumed) {
    unsigned int tmp = iterator;
    for (unsigned int i = 0; i < textConsumed.size(); i++)
    {
        if (!char_(textConsumed[i]))
        {
            iterator = tmp;
            return false;
        }
    }
    return true;
}

bool AParser::readIdentifier(std::string& in) {
    unsigned int tmp = iterator;
    if (char_('"'))
    {
        while (!peek('"'))
            if (!char_(in)) {
                iterator = tmp;
                return false;
            }
        if (!char_('"')) {
            iterator = tmp;
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
    return lineConsumed;
}

unsigned int AParser::getIterator() {
    return iterator;
}

char AParser::getTextIterator() {
    return _file[iterator];
}

unsigned int AParser::getLetterPos() {
    return iterator - letterPos;
}
