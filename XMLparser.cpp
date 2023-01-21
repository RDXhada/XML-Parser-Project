#include "XMLparser.hpp"
#include "utils.hpp"

std::string XMLParser::_defaultSeparator = "/";

XMLnode XMLParser::parse(std::string filename)
{
    XMLnode new_node("Root");
    //read the file
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Cound not read file [" << filename << "]" << std::endl;
        return new_node;
    }
    
    //make a list where we put in the file elements
    std::list<XMLnode*> lst;
    lst.push_back(&new_node);
    
    std::string str;
    std::string line;
    //parse the file
    while (std::getline(infile, line))
    {
        str += line;
        
    }
    Tag tag = getNextTag(str);
    while (tag._isValid)
    {
        if (tag._type == CLOSE)
        {
            if (tag._name.compare(lst.back()->getName()) ==  0)
            {
                lst.back()->setValue(tag._data);
                lst.pop_back();
            }
        }
        else if (tag._type != COMMENTED)
        {
            if (tag._type != SPECIAL)
            {
                XMLnode* new_node;
                new_node = lst.back()->addSubNode(tag._name);
                lst.push_back(new_node);
                new_node->setAttributes(tag._params);
            }
        }
        
        tag = getNextTag(str, tag._position+1);
    }
    infile.close();
    if (lst.size() > 1)
    {
        std::cout << "\"" << lst.back()->getName() << "\" is not closed" << std::endl;
    }
    
    return new_node;
}

//default separator should be "/" for this specific project, can be set as all kinds of characters
//example ".", "," "/" "\" "-" <- note that some changes need to be made on the code for this to work
void XMLParser::setDefaultSeparator(const std::string& separator)
{
    _defaultSeparator = separator;
}

const std::string &XMLParser::getDefaultSeparator()
{
    return _defaultSeparator;
}





