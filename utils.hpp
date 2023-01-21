#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <list>
#include <map>
#include <string>
#include <vector>
#include <iostream>

//This was my view of the xml components, found it on the internet, specifically the tagType, because i didn't know the tag types and tag structure in XML
const std::string HEADER = "?xml";
const char SLASH    = '/';
const char START_TAG = '<';
const char END_TAG = '>';

enum TagType
{
    OPEN,
    CLOSE,
    SPECIAL,
    COMMENTED,
    AUTO_CLOSED
};

struct Tag
{
    std::string _name;
    std::string _data;
    std::map<std::string, std::string> _params;
    TagType _type;
    size_t  _position;
    bool    _isValid;
};

Tag getNextTag(std::string& str, size_t start=0);
bool isFound(size_t pos);
void parseDeclaration(const std::string& str, Tag& tag);
std::vector<std::string> split(const std::string& str, std::string sep);
std::vector<std::string> splitQuote(const std::string& str, char sep);
size_t findFirstElem(const std::string& str, char ch, size_t start=0);

#endif
