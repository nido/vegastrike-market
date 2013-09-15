#ifndef H_PRODUCTIONOPTION
#define H_PRODUCTIONOPTION
#include <vector>
#include <string>

#include "scew/scew.h"


//<item name,amount>
typedef std::pair<std::string,double> Stack;

//list of Stacks
typedef std::vector<Stack> Products;

class ProductionOption {

public:
	ProductionOption(Products outputs,Products inputs, double sectorsize, double sectormin, Products costofanother);
	ProductionOption(Products outputs,Products inputs, double sectorsize, Products costofanother);
	Products outputs;
	Products inputs;
	double sectorsize;
    double sectormin;
	Products costofanother;
	void addElement(scew_element* root) const;
    static ProductionOption *productionOptionFromElement(scew_element* root);

};
	void Products_addElement(const Products &products, scew_element* root);
    Products *productsFromElement(scew_element* root);
#endif // H_PRODUCTIONOPTION
