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

#ifdef USE_SCEW
#include <scew.h>
#endif

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

class Economy{
friend class Factory;
friend class Consumer;
public:
	Economy();

	~Economy();

	//define the currency
	void setCurrency(string name);

	//define the race name of the populace
	void setPopulace(string name);

	//set the dividend rate 0..1
	void setDividendrate(double dividendrate);

	//add a factory and the markets necessary for it
	void addFactory(Factory *factory);

	//add a consumer
	void addConsumer(Consumer *consumer);

	//make the consumer profit from the gains of this factory
	void addConsumerMap(string factoryName,string consumerName);

	//set a decay rate of goods sold on the market.
	//0.0<=decay<=1.0 the amount of goods is multplied by the decay rate
	void setDecayRate(string name, double decayrate);

	//a time tick (which triggers production and decay)
	void tick();

	//dump status
	void dump();

	//initialize a market by placing orders
	void placeSellOrders(string what, double loprice, int loamount,double hiprice,int hiamount, int steps);

	//initialize a market by placing orders
	void placeBuyOrders(string what, double loprice, int loamount,double hiprice,int hiamount, int steps);

	//distribute successful market transactions
	bool executeTransactions();

    //flush the statistics
    void reset_statistics();

#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static Economy *economyFromElement(scew_element* root, Economy *pe);
#endif

protected:
	//add a market
	void addMarket(string name);

	//sell
	void sellProduct(string what, int amount, double price, string who);

	//buy
	void buyProduct(string what, int amount, double price, string who);

private:
	string currencyName;
	string populaceName;

	std::map <string,Market*> markets;

	std::map <string,Factory*> factories;

	std::map <string,Consumer*> consumers;

    //<factoryName,consumerName
	std::map <string,string> consumerMap;

	double dividendrate;
};


class ProductionOption {

public:
	ProductionOption(Products outputs,Products inputs, double sectorsize, double sectormin, Products costofanother);
	ProductionOption(Products outputs,Products inputs, double sectorsize, Products costofanother);
	Products outputs;
	Products inputs;
	double sectorsize;
    double sectormin;
	Products costofanother;
#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static ProductionOption *productionOptionFromElement(scew_element* root);
#endif

};

class Reserve {
public:
    Reserve();
    double getReserve();
    double getReserveValue();
    double getPrice();
    void addReserve(double amount,double total,string why);
    void subtractReserve(double amount,string why);
#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static Reserve *reserveFromElement(scew_element* root);
#endif
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

#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static Factory *factoryFromElement(scew_element* root,Economy *economy);
#endif

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

class Consumer{
friend class Economy;
public:
    Consumer(double capital, Economy *economy, Products consumption, string name,double subsidyrate);

    void tick();

    ~Consumer();

#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static Consumer *consumerFromElement(scew_element* root,Economy *economy,string name);
#endif

private:
    string name;
    double capital;
    Economy *economy;
    Products consumption;
    double subsidyrate;
};

#ifdef USE_SCEW
	void Products_addElement(const Products &products, scew_element* root);
    Products *productsFromElement(scew_element* root);
#endif

#endif
