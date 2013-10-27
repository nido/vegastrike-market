#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

#include "XMLNode.hpp"

XMLNode::XMLNode()
: parent(NULL), children(std::vector<XMLNode *>()),
attributes(std::map<std::string, std::string>()) {}

XMLNode::XMLNode(const XMLNode& that) :
parent(that.parent),
children(std::vector<XMLNode*>()),
name(that.name),
attributes(std::map<std::string, std::string>(that.attributes))
{
    for(std::vector<XMLNode*>::const_iterator i = that.children.begin();
        i < that.children.end();
        ++i
    ) {
        this->children.push_back(new XMLNode(*i));
    }
}


XMLNode::XMLNode(XMLNode *parent)
: parent(parent), children(std::vector<XMLNode *>()),
attributes(std::map<std::string, std::string>()) {}

XMLNode::~XMLNode()
{
    for(std::vector<XMLNode*>::const_iterator i = this->children.begin();
        i < this->children.end();
        ++i
    ) {
        delete *i;
    }
}


XMLNode::XMLNode(CargoType& c) : parent(NULL),
children(std::vector<XMLNode *>()),
name("CargoType"),
attributes(std::map<std::string, std::string>())
{
    std::stringstream s;
    this->attributes["name"] = c.getName();
    this->attributes["category"] = c.getCategory();

    s<<c.getMass();
    this->attributes["mass"] = s.str();

    s.str("");
    s.clear();
    s<<c.getVolume();
    this->attributes["value"] = s.str();

    s.str("");
    s.clear();
    s<<c.getBasePrice();
    this->attributes["price"] = s.str();
}


void XMLNode::ParseElementBegin(const XML_Char *name, const XML_Char **atts)
{
    this->name = std::string(name);
    for (int i = 0; atts[i] != NULL; i += 2) {
        std::string name = std::string(atts[i]);
        std::string value = std::string(atts[i + 1]);
        this->attributes[name] = value;
    }
}


XMLNode *XMLNode::ParseString(std::string string)
{
    const char *data = string.c_str();
    XMLNode *root = new XMLNode();

    XML_Parser parser = XML_ParserCreate(NULL);

    XML_SetElementHandler(parser, XMLNode::ParseXMLNodeBegin,
        XMLNode::ParseXMLNodeEnd);
    XML_SetCharacterDataHandler(parser, XMLNode::ParseXMLNodeCharacterData);

    XML_SetUserData(parser, static_cast<void *>(root));
    XML_Parse(parser, data, string.size(), 0);

    XML_ParserFree(parser);

    return (root);
}


void XMLNode::ParseXMLNodeBegin(void *xmlnode, const XML_Char *name,
const XML_Char **atts)
{
    XMLNode *root = static_cast<XMLNode *>(xmlnode);
    XMLNode *last = root->parent;
    if (last == NULL) {
        // in this case, we are doing the root node itself
        // since we use root's parent pointer as a 'last node'
        // pointer, we need to pay special attention to handling
        // root
        root->ParseElementBegin(name, atts);
        last = root;
    }
    else {

        XMLNode *current = new XMLNode(last);
        current->ParseElementBegin(name, atts);

        last->children.push_back(current);
        last = current;
    }
    root->parent = last;
}


void XMLNode::ParseXMLNodeEnd(void *xmlnode, const XML_Char *name)
{
    XMLNode *root = static_cast<XMLNode *>(xmlnode);
    XMLNode *last = root->parent;
    if (last == root) {
        root->parent = NULL;
    }
    else {
        root->parent = last->parent;
    }
    assert(strcmp(last->name. c_str(), name)==0);
}


void XMLNode::ParseElementCharacterData(const XML_Char *name, int size)
{
    this->characterdata = std::string(name, size);
}


void XMLNode::ParseXMLNodeCharacterData(void *xmlnode, const XML_Char *name,
int size)
{
    XMLNode *root = static_cast<XMLNode *>(xmlnode);
    XMLNode *last = root->parent;
    assert(last != NULL);
    last->ParseElementCharacterData(name, size);
}


std::string XMLNode::getXML()
{
    // TODO: Properly warn for shoddy implementation

    std::string XML = "<" + this->name;

    if (!this->attributes.empty()) {
        for (std::map<std::string, std::string>::iterator i = attributes.begin();
        i != attributes.end(); ++i) {
            XML += " " + i->first + "=\"" + i->second + "\"";
        }
    }
    if (this->children.empty() && this->characterdata.empty()) {
        XML += " />";
    }
    else {
        XML += ">";
    }
    for (std::vector<XMLNode *>::iterator child = this->children.begin();
    child != this->children.end(); ++child) {
        XML += (*child)->getXML();
    }
    if (this->characterdata.empty() != true) {
        XML += this->characterdata;
    }
    if (!(this->children.empty() && this->characterdata.empty())) {
        XML += "</" + this->name + ">";
    }
    return XML;
}


Cargo* XMLNode::getCargo()
{
    if (this->name.compare("Cargo") != 0) {
        return NULL;
    }
    Cargo* c = new Cargo();
    //<Cargo><entry><CargoType name=\"name\" category=\"category\"
    //mass=\"1\" volume=\"2\" price=\"3\" />10</entry><entry><CargoType
    //name=\"otherstuff\" category=\"category\" mass=\"1\" volume=\"2\"
    //price=\"3\" />12</entry></Cargo>

    for (std::vector<XMLNode *>::iterator child = this->children.begin();
    child != this->children.end(); ++child) {
        assert((*child)->children.empty() == false);
        CargoType* t = (*(*child)->children.begin())->getCargoType();
        assert(t != NULL);

        int i = atoi((*child)->characterdata.c_str());
        c->addCargo(*t, i);
        delete t;
    }
    return c;
}


CargoType* XMLNode::getCargoType()
{
    if (this->name.compare("CargoType") != 0) {
        return NULL;
    }

    std::string cargoName = this->attributes["name"];
    std::string cargoDescription = this->attributes["category"];
    float cargoMass = strtof(this->attributes["mass"].c_str(), NULL);
    float cargoVolume = strtof(this->attributes["volume"].c_str(), NULL);
    float cargoPrice = strtof(this->attributes["price"].c_str(), NULL);
    CargoType *cargo = new CargoType(cargoName, cargoDescription, cargoMass,
        cargoVolume, cargoPrice);
    return cargo;
}
