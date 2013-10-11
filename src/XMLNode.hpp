#ifndef H_XMLNODE
#define H_XMLNODE

#include <string>
#include <vector>
#include <map>

#include <expat.h>

#include "Cargo.hpp"

class XMLNode {
public:
  /** Create an empty XMLNode to be used as root. */
  XMLNode();

  /** Create an XMLNode with a parent node. */
  XMLNode(XMLNode *parent);

  /** Parse an XML string to populate this root node */
  std::string buildXMLString();

  /** Delete an XMLNode (and it's children) */
  ~XMLNode();

  /** Parse an XMLString, producing a tree of XMLNode */
  static XMLNode *ParseString(std::string string);

  /** Return a CargoType* built from this XMLNode (assuming this is a
 	 * valid CargoType node), or NULL on failure.
 	 */
  CargoType *getCargoType();

private:
  /** Expat function computing the current node and calling its
 	 * companion function */
  static void ParseXMLNodeBegin(void *xmlnode, const XML_Char *name,
                                const XML_Char **atts);
  /** Expat function computing the current node and calling its
 	 * companion function */
  static void ParseXMLNodeEnd(void *xmlnode, const XML_Char *name);
  /** Expat function computing the current node and calling its
 	 * companion function */
  static void ParseXMLNodeCharacterData(void *xmlnode, const XML_Char *name,
                                        int size);

  /** Expat function used to parse the XML string responsible for XML
 	 * elements */
  void ParseElementBegin(const XML_Char *name, const XML_Char **atts);

  /** Expat function used to parse the XML string responsible for
 	 * ending XML elements */
  void ParseElementEnd(const XML_Char *name);

  /** Expat function used to parse the XML string */
  void ParseElementCharacterData(const XML_Char *name, int size);
  XMLNode *parent;
  std::vector<XMLNode *> children;
  std::string name;
  std::string characterdata;
  std::map<std::string, std::string> attributes;
};

#endif //H_XMLNODE
