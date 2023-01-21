#include "XMLparser.hpp"
#include "XMLNODE.hpp"


//Node pointer
Node NodePtr::operator()(const std::string& name)
{
    return (*node)(name);
}

//operator using @ to get the attributes
std::string NodePtr::operator[](const std::string& attr)
{
    if (attr[0] == '@')
    {
        std::string atrrib = attr.substr(1);
        return (*node)[atrrib];
    }
    return "error";
}

//operator[] by given number returns node say person/address[0] returns the first positon address
XMLnode& Node::operator[](int i)
{
    return *(nodeset[i].node);
}


Node Node::find(const std::string& name)
{
    Node result;
    
    for (NodePtr& i : nodeset)
    {
        if (i->getName().compare(name) == 0)
            result.nodeset.push_back(i);
    }
    
    return result;
}

std::vector<std::string> Node::operator[](const std::string& attr)
{
    std::vector<std::string> result;
    for (NodePtr& i : nodeset)
    {
        result.push_back(i[attr]);
    }
    
    return result;
}

Node Node::_findNodesByName(const std::string& name)
{
    Node result;
    
    for (NodePtr i : nodeset)
    {
        result.addNode(i->getNodeSet().find(name));
    }
    
    return result;
}

//operator() path is for example person/name or person/address
Node Node::operator()(const std::string& path)
{
    return this->operator()(path, XMLParser::getDefaultSeparator());
}

//operator()
Node Node::operator()(const std::string& path, const std::string& sep)
{
    std::vector<std::string> nodes = split(path, sep);
    
    Node result;
    Node* currentSet = this;
    for (const std::string& names : nodes)
    {
        result = currentSet->_findNodesByName(names);
        currentSet = &result;
    }
    
    return result;
}


std::vector<NodePtr>& Node::operator()()
{
    return nodeset;
}

//Iterators
std::vector<NodePtr>::iterator Node::begin()
{
    return nodeset.begin();
}

std::vector<NodePtr>::iterator Node::end()
{
    return nodeset.end();
}

std::vector<NodePtr>::const_iterator Node::begin() const
{
    return nodeset.begin();
}

std::vector<NodePtr>::const_iterator Node::end() const
{
    return nodeset.end();
}

//adds a node to the end
void Node::addNode(XMLnode* node)
{
    nodeset.push_back(NodePtr(*node));
}

void Node::addNode(const Node& Node)
{
    for (NodePtr i : Node.nodeset)
    {
        nodeset.push_back(i);
    }
}

void Node::prettyPrint() const
{
    for (NodePtr elems : nodeset)
    {
        elems->prettyPrint();
    }
}

//XML node
// Constructors
XMLnode::XMLnode() : _name(""), _value(""), _top(nullptr) {}
XMLnode::XMLnode(std::string name) : _name(name), _value(""), _top(nullptr) {}

//changes node data
void XMLnode::setValue(const std::string &value)
{
    //std::string::front returns first character of string
    _value = value;
    while(_value.front() == ' ')
    {
        _value = _value.substr(1);
    }
}

//changes nodes attributes
void XMLnode::setAttributes(const std::map<std::string, std::string> &attribute)
{
    _attributes = attribute;
}

//different operator methods
Node XMLnode::operator()(const std::string &path)
{
    Node result;
    result.addNode(this);
    return result(path, XMLParser::getDefaultSeparator());
}

Node XMLnode::operator()(const std::string &path, const std::string &separation)
{
    Node result;
    result.addNode(this);
    return result(path, separation);
}

// Access an attribute by its name
std::string XMLnode::operator[](const std::string &attribute)
{
    return get(attribute);
}


std::string XMLnode::get(const std::string &attribute) const
{
    if (_attributes.find(attribute) != _attributes.end())
        return _attributes.at(attribute);
    return "";
}

// Creates and adds a sub node
XMLnode* XMLnode::addSubNode(const std::string &name)
{
    XMLnode* new_node = new XMLnode(name);
    _subNodes.addNode(new_node);
    new_node->_top = this;
    XMLnode *result = &(*_subNodes().back());
    return result;
}

// Returns all sub nodes
Node& XMLnode::getNodeSet()
{
    return _subNodes;
}

// Return node's name
std::string XMLnode::getName() const
{
    return _name;
}
//return value as a string
std::string XMLnode::asString() const
{
    return _value;
}


//print node and sub nodes
void XMLnode::prettyPrint() const
{
    prettyprint("");
}
//pretty print idea from pretty print tree
void XMLnode::prettyprint(std::string indent) const
{
    std::cout << indent << "+"+_name;
    if (!_value.empty())
        std::cout << " -> " << _value;
    std::cout << std::endl;
    
    for (auto& i : _subNodes)
        i->prettyprint(indent + "  ");
    
    std::cout << indent << "-" + _name << std::endl;
}

//operator= version
void XMLnode::operationsEq(std::string string1)
{
    XMLnode root = XMLParser::parse(FILE_NAME);
    std::string copyString1 = string1;
    std::string copyString2 = string1;
    std::string copyString3 = string1;
    //person[address="Bulgaria"]/name
    std::string get_Name = string1.substr(0, string1.find("[", 0));
    std::string get_Value = copyString1.substr(copyString1.find("[") + 1);
    std::string get_Value_2 = get_Value.substr(0, get_Value.find("=",0));
    std::string combine_input_values = get_Name + '/' + get_Value_2;
    
    
    std::string desired_Value = copyString1.substr(copyString3.find('"') + 1);
    std::string desired = desired_Value.substr(0, desired_Value.find('"',0));
    
    
    std::string output_Values = copyString2.substr(copyString2.find('/') + 1);
    std::string combine_output_values = get_Name + '/' + output_Values;
    
    
    Node param1 = root(combine_output_values);
    Node param2 = root(combine_input_values);
    Node something = root(desired);
    
    std::vector<std::string> param1Vect;
    for (auto i : param1)
    {
        param1Vect.push_back(i->asString());
    }
    
    std::vector<std::string> param2Vect;
    for (auto i : param2)
    {
        param2Vect.push_back(i->asString());
    }
    int getDifference = (int)param2Vect.size() - (int)param1Vect.size();
    
    int count = 0;
    for (auto i : param2)
    {
        if(desired == i->asString())
        {
            param1[std::max(0, count-getDifference)].prettyPrint();
        }
        count++;
    }
}






