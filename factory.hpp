/*
 * Factory for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */
#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <string>

#include <vector>

#include <map>

#include "roottracker.hpp"

#include "btree_iterator.hpp"

#include "market.hpp"

#include "scew/scew.h"

//<item name,amount>
typedef pair<string,double> Stack;

//list of Stacks
typedef vector<Stack> Products;

//TODO web this class in as a base class
//for keeping a balance sheet(improvement over capital) and having a name(used as bidderid)
//also keep track of goods in possession
//try to get rid of friend-modifiers
class EconomicEntity {
    //TODO
};

class Factory;
class Consumer;

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

class Reserve {
public:
    Reserve();
    double getReserve();
    double getReserveValue();
    double getPrice();
    void addReserve(double amount,double total,string why);
    void subtractReserve(double amount,string why);
	void addElement(scew_element* root) const;
    static Reserve *reserveFromElement(scew_element* root);
private:
    double reserve;
    double reserveValue;
};

class Factory {

friend class Economy;

public:
	//create an empty factory
	Factory(double capital, Economy *economy,double rateofreturn,string name);

	void setRateofreturn(double rateofreturn);

	//add outputs(positive) and inputs(negative)
	void addProductionOption(ProductionOption po);

	//reset all calculated values (for example because markets have changed)
	void reset();

	//find the best profit to be made
	void maxProfit(double capitalavailable);

	//try to execute the option last estimated as having best profit and return the number of produced items
	double executeBestProductionOption();

	//receive or remove resources from the reserve
	void addResources(string what,double amount,double price);

	//dump factory status report for development
	void dump();

	//destructor
	~Factory();

	//track own activity
	double totalproduction;

	void addElement(scew_element* root) const;
    static Factory *factoryFromElement(scew_element* root,Economy *economy);

private:
	//create a really empty factory with default values for filling from XML
	Factory();

	string name;
	vector<ProductionOption> options;

	ProductionOption *bestOptionPtr;
	double bestOptionProfit;
	double bestOptionInvestment;
	double bestOptionProductionUnits;
    double bestOptionPriceMultiplier;//to get out of a production hole

    double initialcapital;
	double capital;
	double dividends;

        Economy *economy;

	double rateofreturn;

    //amounts and values
	std::map<string,Reserve> reserve;

    //calculate profit; side-effect: set the best Option as the better option
    double calculate_profit(ProductionOption &po,double productionsize,double capitalavailable,bool makeitwork);

    //calculate the sum of capital needed for buying the inputs from the markets
	double calculate_moneyneeded(ProductionOption &po,double productionsize);

    //calculate how much can be produced with no resources being bought
    double calculate_production_base(ProductionOption &po,double productionsize);

    //calculate the profit expected
    double calculate_moneyresulting(ProductionOption &po,double production_units);

    //build another factory of this type, if possible
    void growSector(double production);
};

	void Products_addElement(const Products &products, scew_element* root);
    Products *productsFromElement(scew_element* root);

#endif
