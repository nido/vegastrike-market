#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>

#include "XMLNode.hpp"

XMLNode::XMLNode()
    : parent(NULL), children(std::vector<XMLNode>()),
      attributes(std::map<std::string, std::string>()) {}

// may be dangerous not to set parent and child relationships
XMLNode::XMLNode(std::string name, XMLNode *parent,
                 std::vector<XMLNode> children,
                 std::map<std::string, std::string> attributes, std::string characterdata)
    : parent(parent), children(children), name(name), characterdata(characterdata), attributes(attributes)
{}

XMLNode::XMLNode(const XMLNode &that)
    : parent(that.parent), children(std::vector<XMLNode>()), name(that.name), characterdata(that.characterdata), attributes(that.attributes)
{
  for (std::vector<XMLNode>::const_iterator i = that.children.begin();
       i < that.children.end(); ++i) {
    addChild(*i);
  }
}

XMLNode& XMLNode::addChild(const XMLNode& child){
  //becomes a problem when multithreading (though xml processing isn't really something that should be eligable for that
  this->children.push_back(child);
  XMLNode& kid = this->children.back();
  kid.parent = this;
  return kid;
}

XMLNode::XMLNode(XMLNode *parent)
    : parent(parent), children(std::vector<XMLNode>()),
      attributes(std::map<std::string, std::string>()) {}

XMLNode::~XMLNode() {
}

XMLNode::XMLNode(const CargoType &c)
    : parent(NULL), children(std::vector<XMLNode>()), name("CargoType"),
      attributes(std::map<std::string, std::string>()) {
  std::stringstream s;
  this->attributes["name"] = c.getName();
  this->attributes["category"] = c.getCategory();

  s << c.getMass();
  this->attributes["mass"] = s.str();

  s.str("");
  s.clear();
  s << c.getVolume();
  this->attributes["volume"] = s.str();

  s.str("");
  s.clear();
  s << c.getBasePrice();
  this->attributes["price"] = s.str();
}

void XMLNode::ParseElementBegin(const XML_Char *name, const XML_Char **atts) {
  this->name = std::string(name);
  for (int i = 0; atts[i] != NULL; i += 2) {
    std::string name = std::string(atts[i]);
    std::string value = std::string(atts[i + 1]);
    this->attributes[name] = value;
  }
}

XMLNode *XMLNode::ParseString(std::string string) {
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
                                const XML_Char **atts) {
  XMLNode *root = static_cast<XMLNode *>(xmlnode);
  XMLNode *last = root->parent;
  if (last == NULL) {
    // in this case, we are doing the root node itself
    // since we use root's parent pointer as a 'last node'
    // pointer, we need to pay special attention to handling
    // root
    root->ParseElementBegin(name, atts);
    root->parent = root;
  } else {
    XMLNode *current = new XMLNode(last);
    current->ParseElementBegin(name, atts);
    XMLNode& n = last->addChild(*current);
    root->parent = &n;
    delete current;
  }
}

void XMLNode::ParseXMLNodeEnd(void *xmlnode, const XML_Char *name) {
  XMLNode *root = static_cast<XMLNode *>(xmlnode);
  XMLNode *last = root->parent;
  assert(last->name == name);
  if (last == root) {
    root->parent = NULL;
  } else {
    root->parent = last->parent;
  }
//  assert(strcmp(last->name.c_str(), name) == 0);
}

void XMLNode::ParseXMLNodeCharacterData(void *xmlnode, const XML_Char *name,
                                        int size) {
  XMLNode *root = static_cast<XMLNode *>(xmlnode);
  XMLNode *last = root->parent;
  assert(last != NULL);
  last->characterdata = std::string(name, size);

  //root->characterdata = std::string(name, size);
}

std::stringstream& XMLNode::getXML(std::stringstream& ss) const
{
  // TODO: Properly warn for shoddy implementation
  std::string XML = "<" + this->name;
  ss<<"<"<< this->name;

  if (!this->attributes.empty()) {
    for (std::map<std::string, std::string>::const_iterator i = attributes.begin();
         i != attributes.end(); ++i) {
      ss<< " " << i->first << "=\"" << i->second << "\"";
    }
  }
  if (this->children.empty() && this->characterdata.empty()) {
    ss << " />";
  } else {
    ss << ">";
  }

  for (std::vector<XMLNode>::const_iterator child = this->children.begin();
       child != this->children.end(); ++child) {
    child->getXML(ss);
  }
  if (!this->characterdata.empty()) {
    ss << this->characterdata;
  }
  if (!(this->children.empty() && this->characterdata.empty())) {
    ss << "</" << this->name << ">";
  }
 return ss;
}
std::string XMLNode::getXML() const
{
  std::stringstream ss;
  getXML(ss);
  return(ss.str());
/*
  // TODO: Properly warn for shoddy implementation
  std::string XML = "<" + this->name;

  if (!this->attributes.empty()) {
    for (std::map<std::string, std::string>::const_iterator i = attributes.begin();
         i != attributes.end(); ++i) {
      XML += " " + i->first + "=\"" + i->second + "\"";
    }
  }
  if (this->children.empty() && this->characterdata.empty()) {
    XML += " />";
  } else {
    XML += ">";
  }

  for (std::vector<XMLNode>::const_iterator child = this->children.begin();
       child != this->children.end(); ++child) {
    XML += child->getXML();
  }
  if (!this->characterdata.empty()) {
    XML += this->characterdata;
  }
  if (!(this->children.empty() && this->characterdata.empty())) {
    XML += "</" + this->name + ">";
  }
  return XML;
*/
}

XMLNode::XMLNode(const ProductionOption& o) :
parent(NULL),
children(std::vector<XMLNode>()),
  name("ProductionOption"),
characterdata(std::string()),
attributes(std::map<std::string, std::string>())
{
  XMLNode in = XMLNode(o.input());
  in.attributes["type"]="in";
  this->addChild(in);
  XMLNode out = XMLNode(o.output());
  out.attributes["type"]="out";
  this->addChild(out);
}

ProductionOption *XMLNode::getProductionOption() {
  ProductionOption *p;
  Cargo *in;
  Cargo *out;
  for (std::vector<XMLNode>::iterator child = this->children.begin();
       child != this->children.end(); ++child) {
    std::string type = child->attributes["type"];
    if (type.compare("in")) {
      in = child->getCargo();
    } else if (type.compare("out")) {
      out = child->getCargo();
    }
  }
  assert(in != NULL);
  assert(out != NULL);
  p = new ProductionOption(*out, *in);
  delete (in);
  delete (out);
  return p;
}

Cargo *XMLNode::getCargo() {
  if (this->name.compare("Cargo") != 0) {
    return NULL;
  }
  Cargo *c = new Cargo();
  for (std::vector<XMLNode>::iterator child = this->children.begin();
       child != this->children.end(); ++child) {
    CargoType *t = child->getCargoType();
    assert(t != NULL);
    int i = atoi(child->characterdata.c_str());
    c->addCargo(*t, i);
    delete t;
  }
  return c;
}

CargoType *XMLNode::getCargoType() {
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

XMLNode::XMLNode(const Cargo &c) :
parent(NULL), 
children(std::vector<XMLNode>()), 
  name("Cargo"), 
characterdata(std::string()),
attributes(std::map<std::string, std::string>())
{
  for (std::map<CargoType, unsigned int>::const_iterator ct = c.begin(); ct != c.end(); ++ct){
    XMLNode ctn = XMLNode(ct->first);
    std::ostringstream s;
    s << ct->second;
    ctn.setCharacterdata(s.str());
    this->addChild(ctn);
  }
}

void XMLNode::setCharacterdata(std::string chardata){
  this->characterdata = chardata;
}

XMLNode& XMLNode::operator=(const XMLNode &that){
  this->children = that.children;
  this->name = that.name;
  this->characterdata = that.characterdata;
  this->attributes = that.attributes;
  this->parent = that.parent;
  return *this;
}

XMLNode::XMLNode(const Factory& f) :
  parent(NULL),
  children(std::vector<XMLNode>()),
  name("Factory"),
  characterdata(std::string()),
  attributes(std::map<std::string, std::string>())
{
  for (std::vector<ProductionOption>::const_iterator i = f.begin();
     i != f.end(); ++i){
    XMLNode n = XMLNode(*i);
    if(i == f.indicator()) {
      n.attributes["active"] = "true";
    }
    this->addChild(n);
  }
}

Factory* XMLNode::getFactory(){
  Factory* f = new Factory();
  for (std::vector<XMLNode>::iterator i = this->children.begin(); i != this->children.end(); ++i)
  {
    ProductionOption* p = i->getProductionOption();
    assert (p != NULL);
    f->addProductionOption(*p);
    if (i->attributes.find("active") != i->attributes.end()){
      //I assume this is enough information. Changing it to 'false' is invalid anyhow.
      f->setProductionOption(*p);
      
    }
  }
  return f;
}


XMLNode::XMLNode(const Base& b) :
  parent(NULL),
  children(std::vector<XMLNode>()),
  name("Base"),
  characterdata(std::string()),
  attributes(std::map<std::string, std::string>())
{
  for (std::vector<Factory>::const_iterator i = b.begin();
     i != b.end(); ++i){
    XMLNode n = XMLNode(*i);
    this->addChild(n);
  }
}

Base* XMLNode::getBase(){
  Base* b = new Base();
  for (std::vector<XMLNode>::iterator i = this->children.begin(); i != this->children.end(); ++i)
  {
    Factory* f = i->getFactory();
    assert(f != NULL);
    b->addFactory(*f);
    free(f);
  }
  return b;
}

XMLNode::XMLNode(const Economy& e):
  parent(NULL),
  children(std::vector<XMLNode>()),
  name("Economy"),
  characterdata(std::string()),
  attributes(std::map<std::string, std::string>())
{
  for (std::vector<Base>::const_iterator i = e.begin();
     i != e.end(); ++i){
     XMLNode n = XMLNode(*i);
    this->addChild(n);
  }
}

Economy* XMLNode::getEconomy(){
  Economy* e = new Economy();
  for (std::vector<XMLNode>::iterator i = this->children.begin(); i != this->children.end(); ++i)
  {
    Base* b = i->getBase();
    assert(b != NULL);
    e->addBase(*b);
    free(b);
  }
  return e;
}
