#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "XMLNODE.hpp"
#include <iostream>
#include <string>
#include <list>
#include <fstream>

//PUT YOUR FILE DIRECTORY HERE
const std::string FILE_NAME = "/Users/dzhemshenolov/Downloads/01_xml_parser_8MI0700009 copy 3 3/01_xml_parser_8MI0700009/testing.xml";


class XMLParser
{
public:
    static XMLnode parse(std::string filename);
    static void setDefaultSeparator(const std::string& separator);

    static const std::string& getDefaultSeparator();

private:
    static std::string _defaultSeparator;
};

#endif
