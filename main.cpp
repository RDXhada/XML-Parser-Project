#include "XMLparser.hpp"
#include <iostream>
#include <string>
#include <vector>
//XML parser program by Dzhem Shenolov, 8MI0700009


void test_output_of_person_name()
{
    //std::string std;
    //those can easily be made to be written on the console with std::getline(std::cin, str);
    std::cout << '\n';
    std::cout << "Testing person/name output: " << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node personName = root("person/name");
    personName.prettyPrint();
    std::cout << '\n';
}

void test_output_of_person_address()
{
    //std::string std;
    //those can easily be made to be written on the console with std::getline(std::cin, str);
    std::cout << "Testing person/address output: " << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node personAddress= root("person/address");
    personAddress.prettyPrint();
    std::cout << '\n';
}

void test_output_of_person_occupation()
{
    //std::string std;
    //those can easily be made to be written on the console with std::getline(std::cin, str);
    std::cout << "Testing person/occupation output: " << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node personOccupation = root("person/occupation");
    personOccupation.prettyPrint();
    std::cout << '\n';
}

//testing operator[]
void test_operator_()
{
    std::cout << "Testing operator [] as [digit_type]" << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node personName = root("person/name");
    Node personAddress = root("person/address");
    personName[0].prettyPrint();
    std::cout << "--------" << '\n';
    personAddress[2].prettyPrint();
    std::cout << "--------" << '\n';
    personName[1].prettyPrint();
    std::cout << '\n';
}

void test_at_sign()
{
    //std::string std;
    //those can easily be made to be written on the console with std::getline(std::cin, str);
    std::cout << "Testing @id sign: " << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node getIds = root("person");
    for (auto ids : getIds)
    {
        //std::cout << ids[str];
        std::cout << ids["@id"] << " ";
    }
    std::cout << '\n';
}

void test_TYPE_sign()
{
    //std::string std;
    //those can easily be made to be written on the console with std::getline(std::cin, str);
    std::cout << "Testing @type sign: " << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    Node getIds = root("person/address");
    for (auto types : getIds)
    {
        //std::cout << types[str];
        std::cout << types["@type"] << " ";
    }
    std::cout << '\n';
}

void print_the_whole_root()
{
    std::cout << "Printing the whole root(pretty print): ";
    std::cout << '\n';
    XMLnode root = XMLParser::parse(FILE_NAME);
    root.prettyPrint();
    std::cout << '\n';
}

void test_operator_equals()
{
    XMLnode root = XMLParser::parse(FILE_NAME);
    std::string desiredInput;
    std::cout << "Please write your desired input. Here are some examples: \n   (just copy and paste them in the input) " << '\n';
    std::cout << "person[address=\"Bulgaria\"]/name" << '\n';
    std::cout << "person[address=\"Poland\"]/name" << '\n';
    std::cout << "person[address=\"Manhattan, NYC\"]/occupation" <<'\n';
    std::cout << "person[address=\"Turkey\"]/occupation" << '\n';
    std::cout << "person[address=\"Poland\"]/occupation" << '\n';
    std::cout << "person[name=\"Dzhem\"]/occupation" << '\n';
    std::cout << "person[name=\"John Smith\"]/occupation" << '\n';
    std::cout << "person[name=\"Radina\"]/occupation" << '\n';
    std::cout << "Input: ";
    std::getline(std::cin, desiredInput);
    std::cout << "Output: " << '\n';
    root.operationsEq(desiredInput);
   
}


int main()
{
    //person/name outputs properly
    test_output_of_person_name();
    //person/address outputs properly
    test_output_of_person_address();
    //person/occupation outputs properly
    test_output_of_person_occupation();
    //operator [] outputs properly the set of elements
    test_operator_();
    //operator @ outputs properly the ids -> "0" , "1" and etc.
    test_at_sign();
    std::cout << std::endl;
    //operator @ outputs properly the types -> work and home
    test_TYPE_sign();
    //properly print the whole root, but its prettyPrint and can easily be removed and printed only as a list of elements
    std::cout << std::endl;
    print_the_whole_root();
    
    test_operator_equals();
    
    
    return 0;
}
