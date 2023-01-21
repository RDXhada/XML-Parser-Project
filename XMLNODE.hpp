#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include "utils.hpp"
#include <iostream>
#include <cmath>
#include <map>
#include <iostream>
#include <sstream>

//Stores a set of nodes
class Node;
class XMLnode;

//Stores a pointer to a XMLNode and it exposes its methods.
struct NodePtr
{
    NodePtr(XMLnode& node) : node(&node) {}
    Node operator()(const std::string& name);
    std::string operator[](const std::string& attr);
    XMLnode &operator*() {return *node;}
    XMLnode *operator->() {return node;}
    const XMLnode *operator->() const {return node;}
    
    XMLnode* node;
};

//class Node stores a set of nodes
class Node
{
private:
    std::vector<NodePtr> nodeset;
    Node _findNodesByName(const std::string& name);
    
public:
    
    // Return an attribute of all the elements
    std::vector<std::string> operator[](const std::string& attributes);
    
    //Operators
    Node operator()(const std::string& path);
    Node operator()(const std::string& path, const std::string& separation);
    // Return the i-th element
    XMLnode &operator[](int i);
    XMLnode &operator[](std::string attributes);
    //Return all nodes
    std::vector<NodePtr>& operator()();
    //find elem by name
    Node find(const std::string& name);
    
    
    //Iterators
    std::vector<NodePtr>::iterator begin();
    std::vector<NodePtr>::iterator end();
    std::vector<NodePtr>::const_iterator begin() const;
    std::vector<NodePtr>::const_iterator end()   const;
    
    //Adds a node
    void addNode(XMLnode* node);
    //Adds all nodes of an other Node
    void addNode(const Node& Node);
    
    //prints nodes
    void prettyPrint() const;
};

//class XMLnode is just the node elements of the xml parser
class XMLnode
{
private:
    //node names
    std::string _name; //adress
    std::string _value;
    XMLnode* _top;
    Node _subNodes;
    std::map<std::string, std::string> _attributes;
public:
    //constructor
    XMLnode();
    XMLnode(std::string name);
    
    
    ~XMLnode()
    {
        for (auto &nodes: _subNodes)
        {
            delete nodes.node;
        }
    }
    //Changes node value/data
    void setValue(const std::string &data);
    
    //Changes nodes attributes
    void setAttributes(const std::map<std::string,std::string> &attribute);
    
    //Operator methods
    Node operator()(const std::string &path);
    Node operator()(const std::string &path, const std::string &separation);
    //Access an attribute by its name
    std::string operator[](const std::string &attribute);
    std::string get(const std::string &attribute) const;
    
    //add subnodes
    XMLnode *addSubNode(const std::string &name);
    //Returns all sub nodes
    Node &getNodeSet();
    
    // Return node's name
    std::string getName() const;
    //return as string
    std::string asString() const;
private:
    void prettyprint(std::string indent) const;
public:
    //print sub nodes
    void prettyPrint() const;
    
public:
    //oppp
    void operationsEq(std::string desired);
};;

#endif
