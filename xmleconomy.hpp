
#include "factory.hpp"

#include <scew.h>

class XMLEconomy : public Economy{
public:
	XMLEconomy();
	bool writeToFile(string filename);
	static XMLEconomy *readFromFile(string filename);
    static XMLEconomy *xmleconomyFromElement(scew_element* root);
	~XMLEconomy();
};
