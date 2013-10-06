#ifndef H_XMLNODE
#define H_XMLNODE

#include <string>
#include <vector>
#include <map>

#include <expat.h>

#include "Cargo.hpp"

class XMLNode{
public:
	/** Create a node */
	XMLNode();
	XMLNode(XMLNode* parent);
	~XMLNode();

	static XMLNode* ParseString(std::string string);

	std::string buildXMLString();

	void ParseElementBegin(const XML_Char *name, const XML_Char **atts);
	void ParseElementEnd(const XML_Char *name);
	void ParseElementCharacterData(const XML_Char* name, int size);

	static void ParseXMLNodeBegin(void *xmlnode, const XML_Char *name, const XML_Char **atts);
	static void ParseXMLNodeEnd(void *xmlnode, const XML_Char *name);
	static void ParseXMLNodeCharacterData(void *xmlnode, const XML_Char* name, int size);

private:
	XMLNode* parent;
	std::vector<XMLNode*> children;
	std::string name;
	std::string characterdata;
	std::map<std::string, std::string> attributes;
};

#endif //H_XMLNODE
