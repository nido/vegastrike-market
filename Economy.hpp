#ifndef H_ECONOMY
#define H_ECONOMY

#include <string>
#include <map>

#include "scew/scew.h"

class Economy;

#include "factory.hpp"

class Economy{
friend class Factory;
friend class Consumer;
public:
	Economy();

	~Economy();

	//define the currency
	void setCurrency(std::string name);

	//define the race name of the populace
	void setPopulace(std::string name);

	//set the dividend rate 0..1
	void setDividendrate(double dividendrate);

	//add a factory and the markets necessary for it
	void addFactory(Factory *factory);

	//add a consumer
	void addConsumer(Consumer *consumer);

	//make the consumer profit from the gains of this factory
	void addConsumerMap(std::string factoryName,std::string consumerName);

	//set a decay rate of goods sold on the market.
	//0.0<=decay<=1.0 the amount of goods is multplied by the decay rate
	void setDecayRate(std::string name, double decayrate);

	//a time tick (which triggers production and decay)
	void tick();

	//dump status
	void dump();

	//initialize a market by placing orders
	void placeSellOrders(std::string what, double loprice, int loamount,double hiprice,int hiamount, int steps);

	//initialize a market by placing orders
	void placeBuyOrders(std::string what, double loprice, int loamount,double hiprice,int hiamount, int steps);

	//distribute successful market transactions
	bool executeTransactions();

    //flush the statistics
    void reset_statistics();

	void addElement(scew_element* root) const;
    static Economy *economyFromElement(scew_element* root, Economy *pe);

protected:
	//add a market
	void addMarket(std::string name);

	//sell
	void sellProduct(std::string what, int amount, double price, std::string who);

	//buy
	void buyProduct(std::string what, int amount, double price, std::string who);

private:
	std::string currencyName;
	std::string populaceName;

	std::map <std::string,Market*> markets;

	std::map <std::string,Factory*> factories;

	std::map <std::string,Consumer*> consumers;

    //<factoryName,consumerName
	std::map <std::string,std::string> consumerMap;

	double dividendrate;
};


#endif //H_ECONOMY
