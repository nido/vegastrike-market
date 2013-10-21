#ifndef H_XMLNODE
#define H_XMLNODE

#include <vector>

#include <expat.h>

#include "Cargo.hpp"

/** Class representing a Node in an XML Structure */
class XMLNode {
public:
  /** Create an empty XMLNode to be used as root. */
  XMLNode();

  /** Copy constructor
   * @param that the XMLNode to copy
   */
  XMLNode(const XMLNode& that);

  /** Assignment operator
   * @param that the XMLNode to copy
   * @return reference to this XMLNode
   */
  XMLNode& operator=(const XMLNode& that);

  /** Create an XMLNode with a parent node.
   * @param parent the XMLNode the parent should point to
   */
  XMLNode(XMLNode *parent);

  /** Parse an XML string to populate this root node
   * @return XML string representing this XMLNode
   */
  std::string buildXMLString();

  /** Delete an XMLNode (and it's children) */
  ~XMLNode();

  /** Parse an XMLString, producing a tree of XMLNode
   * @param string the XML string to parse
   * @return XMLNode representing said string
   */
  static XMLNode *ParseString(std::string string);

  /** Parse this XMLNode to a CargoType
   * @return a CargoType* built from this XMLNode (assuming this is a
   * valid CargoType node), or NULL on failure.
   */
  CargoType *getCargoType();

private:
  /** Expat function computing the current node and calling its
   * companion function
   * @param xmlnode void pointer pointing to the head XMLNode
   * @param name name of this XML node
   * @param atts attributes of this XML node
   */
  static void ParseXMLNodeBegin(void* xmlnode, const XML_Char *name,
                                const XML_Char **atts);

  /** Expat function computing the current node and calling its
   * companion function
   * @param xmlnode void pointer pointing to the head XMLNode
   * @param name name of this XML node
   */
  static void ParseXMLNodeEnd(void *xmlnode, const XML_Char *name);

  /** Expat function computing the current node and calling its
   * companion function
   * @param xmlnode void pointer pointing to the head XMLNode
   * @param name name of this XML node
   * @param size number of bytes of this CharacterData entry
   */
  static void ParseXMLNodeCharacterData(void *xmlnode, const XML_Char *name,
                                        int size);

  /** XMLNode function setting up the XML node
   * @param name name of this XML node
   * @param atts attributes for this XML node
   */
  void ParseElementBegin(const XML_Char *name, const XML_Char **atts);

  /** XMLNode function setting up the XML node
   * @param name name of this XML node
   * @param size number of bytes of this CharacterData entry
   */
  void ParseElementCharacterData(const XML_Char *name, int size);

  /** Pointer to the parent XMLNode */
  XMLNode* parent;

  /** Pointers to the child XMLNodes */
  std::vector<XMLNode *> children;

  /** Name of this XMLNode */
  std::string name;

  /** Character Data of this XMLNode */
  std::string characterdata;

  /** Attributes of this XMLNode */
  std::map<std::string, std::string> attributes;
};

#endif //H_XMLNODE
