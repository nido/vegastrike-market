#include <limits>

#include <math.h>

#include "Consumer.hpp"

Consumer::Consumer(double capital, Economy * economy, Products consumption,
                   string name, double subsidyrate)
{
    this->capital = capital;
    this->economy = economy;
    this->consumption = consumption;
    this->name = name;
    this->subsidyrate = subsidyrate;
}

void Consumer::tick()
{
    if (capital <= 0.0)
        return;

    capital *= 1.0 + subsidyrate;   //the government is basically printing money to match economy growth

    //spend money progressively
    for (Products::const_iterator pitr = (this->consumption).begin();
         pitr != (this->consumption).end(); ++pitr) {
        if (this->capital <= 0.0)
            break;

        string aname = (*pitr).first;
        double amount = (*pitr).second;
        double amoneyneed;
        double marketprice =
            this->economy->markets[aname]->
            max_market_price_when_buying_n((int) ceil(amount), amoneyneed);
        if (marketprice == 0.0
            || marketprice >= std::numeric_limits < float >::max()) {
            marketprice = this->economy->markets[aname]->last_deal_price();
            amoneyneed = marketprice * amount;
        }
        double factor = capital / (marketprice * amount);   //amoneyneed here does not work (leads to negative capital)
        if (factor > 1.21) {    //was 4.0
            factor = 1.21;
        }

        if (factor > 0.25) {
            double price = marketprice * sqrt(factor);
            int aamount = (int) floor(amount * sqrt(factor));
            this->economy->buyProduct(aname, aamount, price, this->name);
            this->capital -= aamount * price;   //pay deposit immediately
        } else {
            break;
        }
    }
}

Consumer::~Consumer()
{
}

Consumer *Consumer::consumerFromElement(scew_element * element,
                                        Economy * economy, string name)
{
    Consumer *pc = NULL;

    XML_Char const *contents = NULL;

    Products *pconsumption = NULL;
    double capital = 0.0;
    double subsidyrate = 0.01;
    //string name= "";

    for (scew_element * sub_element = scew_element_next(element, NULL);
         NULL != sub_element;
         sub_element = scew_element_next(element, sub_element)) {
        if (0 == strcmp(scew_element_name(sub_element), "consumption")) {
            pconsumption = productsFromElement(sub_element);
        } else if (0 == strcmp(scew_element_name(sub_element), "capital")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                capital = doubleFromCString(contents, capital);
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element), "subsidyrate")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                subsidyrate = doubleFromCString(contents, subsidyrate);
            }
        } else if (0 == strcmp(scew_element_name(sub_element), "name")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                name = string(contents);
            }
        }
    }
    if (NULL != pconsumption) {
        if (0 != strcmp(name.c_str(), "")) {
            pc = new Consumer(capital, economy, *pconsumption, name,
                              subsidyrate);
        }
        delete pconsumption;
    }
    return pc;
}

void Consumer::addElement(scew_element * root) const const
{
    scew_element *element = NULL;

    element = scew_element_add(root, "capital");
    scew_element_set_contents(element, toCString(capital));
    element = scew_element_add(root, "consumption");
    Products_addElement(consumption, element);
    element = scew_element_add(root, "subsidyrate");
    scew_element_set_contents(element, toCString(subsidyrate));
}
