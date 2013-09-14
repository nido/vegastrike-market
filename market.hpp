/*
 * Market for trading goods, version 0.0.1
 * @author peter.schaefer@gmail.com
 */
#ifndef __MARKET_HPP__
#define __MARKET_HPP__

#include <string>

#include <vector>

#include "roottracker.hpp"

#include "btree_iterator.hpp"

#ifdef USE_SCEW
#include <scew.h>
#endif

typedef pair<double,string> Payback;

class Market {

public:
	//create an empty market
	Market();

	//adds a sell order
	void addSellOrder(double price, int amount, string id, long precedence=-1);

	//adds a buy order
	void addBuyOrder(double price, int amount, string id, long precedence=-1);

	//gets the orders in ascending order
	BTree_Iterator getSellOrders() const;

	//gets the orders descending order
	BTree_Iterator getBuyOrders() const;

	//gets the sell orders
	vector<Elem*>getExecutedSellOrders();

	//gets the buy orders
	vector<Elem*>getExecutedBuyOrders();

	//gets the payback, if there is a deposit higher than the deal price
	vector<Payback*>getPaybacks();

	//dump the executed sell/buy order vectors and elements
	void dumpExecutedOrders();

	//reset the executed sell/buy order vectors and elements
	void resetExecutedOrders();

	//get market price and accumulated cost of a buy order of count n
	double max_market_price_when_buying_n(int n,double &accumulated);

	//get market price and accumulated cost of a sell order of count n
	double min_market_price_when_selling_n(int n,double &accumulated);

	//last deal price
	double last_deal_price();

    //highest_buy_offer
    double highest_buy_offer();

    //lowest_sell_offer
    double lowest_sell_offer();

	//set a decay rate of goods sold on the market.
	//0.0<=decay<=1.0 the amount of goods is multplied by the decay rate
	//this is meant for tracking limited resources like population and lands, not for general use
	void setDecayRate(double decayrate);

	//a time tick (which triggers decay)
	void tick();

	//dump the summary
	void dump_summary();

	//dump the orders
	void dump();

    //statistics
    double lowest_price, highest_price;

    //number of trades
    double number_of_trades;

    //value of trades
    double value_of_trades;

    //average value of trades
    double avg_value_of_trades();

    //flush the statistics
    void reset_statistics();

	//destructor
	~Market();

#ifdef USE_SCEW
	void addElement(scew_element* root) const;
    static Market *marketFromElement(scew_element* root);
#endif

private:
	vector<Elem*>executedSellOrders;
	vector<Elem*>executedBuyOrders;
	vector<Payback*>paybacks;
	double last_deal;

	RootTracker trackerSell;
	RootTracker trackerBuy;

	long timer;

	double decayrate;

	void setLastDeal(double price, int amount);
};

#ifdef USE_SCEW
/* These functions use a static buffer, so strcat(toCString(1.0),toCString(0.5) does not work*/
const char *toCString(double d);
const char *toCString(long l);
const char *toCString(int i);

double doubleFromCString(const char* cstr, double defo=0.0);
long longFromCString(const char* cstr, long defo=0);
int intFromCString(const char* cstr, int defo=0);

static Elem* elemFrom(scew_element *sub_element);
#endif

#endif
