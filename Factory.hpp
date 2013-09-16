/*
 * Factory for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */
#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <string>
#include <vector>
#include <map>

#include "scew/scew.h"

class Factory;

#include "ProductionOption.hpp"
#include "Reserve.hpp"
#include "Economy.hpp"


/**An economical sector defined by what it can output given its input.
 *
 * Not a single factory. Rather every factory of that type put together,
 * all following the same strategy as all other factories created.
 */
class Factory {

friend class Economy;

public:
	//create an empty factory
	Factory(double capital, Economy *economy,double rateofreturn,std::string name);

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
	void addResources(std::string what,double amount,double price);

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

	std::string name;
	std::vector<ProductionOption> options;

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
	std::map<std::string,Reserve> reserve;

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


#endif
