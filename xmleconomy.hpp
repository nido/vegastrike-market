
#include "Factory.hpp"

#include "scew/scew.h"

class XMLEconomy : public Economy{
public:
	XMLEconomy();
	bool writeToFile(string filename);
	static XMLEconomy *readFromFile(string filename);
    static XMLEconomy *xmleconomyFromElement(scew_element* root);
	~XMLEconomy();
};
