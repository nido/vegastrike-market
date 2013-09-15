#include <limits>
#include <string>

#include "Economy.hpp"
#include "Consumer.hpp"
#include "Market.hpp"

Economy::Economy()
{
    this->dividendrate = 1.0;
}

Economy::~Economy()
{
}

//protected:
//define the currency
void Economy::setCurrency(std::string name)
{
    this->currencyName = name;
    //this->addMarket(name);
}

//define the race name of the populace
void Economy::setPopulace(std::string name)
{
    this->populaceName = name;
    this->addMarket(name);
}

//set the dividend rate 0..1
void Economy::setDividendrate(double dividendrate)
{
    if (0.0 <= dividendrate && dividendrate <= 1.0) {
        this->dividendrate = dividendrate;
    }
}

//add a market
void Economy::addMarket(std::string name)
{
    this->markets[name] = new Market();
}

//add a factory
void Economy::addFactory(Factory * factory)
{
    this->factories[factory->name] = factory;
    //for each option
    for (vector < ProductionOption >::const_iterator itr =
         factory->options.begin(); itr != factory->options.end(); ++itr) {
        //add missing markets
        for (Products::const_iterator pitr = (*itr).outputs.begin();
             pitr != (*itr).outputs.end(); ++pitr) {
            std::string name = (*pitr).first;
            //add market for name if it doesn't exist
            if (this->markets.count(name) == 0) {
                this->markets[name] = new Market();
            }
        }
        for (Products::const_iterator pitr = (*itr).inputs.begin();
             pitr != (*itr).inputs.end(); ++pitr) {
            std::string name = (*pitr).first;
            //add market for name if it doesn't exist
            if (this->markets.count(name) == 0) {
                this->markets[name] = new Market();
            }
        }
        for (Products::const_iterator pitr = (*itr).costofanother.begin();
             pitr != (*itr).costofanother.end(); ++pitr) {
            std::string name = (*pitr).first;
            //add market for name if it doesn't exist
            if (this->markets.count(name) == 0) {
                this->markets[name] = new Market();
            }
        }
    }
}

//sell
void Economy::sellProduct(std::string what, int amount, double price,
                          std::string who)
{
    this->markets[what]->addSellOrder(price, amount, who);
}

//buy
void Economy::buyProduct(std::string what, int amount, double price,
                         std::string who)
{
    this->markets[what]->addBuyOrder(price, amount, who);
}

//distribute successful market transactions
bool Economy::executeTransactions()
{
    bool executed = false;
    for (std::map < std::string, Market * >::const_iterator itr =
         this->markets.begin(); itr != this->markets.end(); ++itr) {
        std::string marketName = (*itr).first;
        Market *pmarket = (*itr).second;
        vector < Elem * >sellorders = pmarket->getExecutedSellOrders();
        for (vector < Elem * >::const_iterator oitr = sellorders.begin();
             oitr != sellorders.end(); ++oitr) {
            double price = (*oitr)->m_key;
            long amount = (*oitr)->m_payload.first;
            std::string bidder = (*oitr)->m_payload.second;

            double total = amount * price;
            if (factories.count(bidder) > 0) {
                Factory *pfactory = factories[bidder];
                pfactory->addResources(this->currencyName, total, total);
                executed = true;
            }
        }
        vector < Elem * >buyorders = pmarket->getExecutedBuyOrders();
        for (vector < Elem * >::const_iterator oitr = buyorders.begin();
             oitr != buyorders.end(); ++oitr) {
            double price = (*oitr)->m_key;
            long amount = (*oitr)->m_payload.first;
            std::string bidder = (*oitr)->m_payload.second;

            double total = amount * price;
            if (factories.count(bidder) > 0) {
                Factory *pfactory = factories[bidder];
                //pfactory->addResources(this->currencyName,-total,-total); //commented out - has to be paid when placing the bid
                pfactory->addResources(marketName, amount, total);
                executed = true;
            } else {
                //cerr<<"bidder not found:"<<bidder<<endl;
            }
        }

        //pay back paybacks
        vector < Payback * >paybacks = pmarket->getPaybacks();
        for (vector < Payback * >::const_iterator oitr = paybacks.begin();
             oitr != paybacks.end(); ++oitr) {
            double amount = (*oitr)->first;
            std::string bidder = (*oitr)->second;
            if (factories.count(bidder) > 0) {
                Factory *pfactory = factories[bidder];
                pfactory->addResources(this->currencyName, amount, amount);
            } else if (consumers.count(bidder) > 0) {
                Consumer *pconsumer = consumers[bidder];
                pconsumer->capital += amount;
            } else {
                //cerr<<"bidder not found:"<<bidder<<endl;
            }
        }

        pmarket->resetExecutedOrders();
    }
    return executed;
}

//set a decay rate of goods sold on the market.
//0.0<=decay<=1.0 the amount of goods is multplied by the decay rate
void Economy::setDecayRate(std::string name, double decayrate)
{
    markets[name]->setDecayRate(decayrate);
}

//a time tick (which triggers production and decay)
void Economy::tick()
{

    //for each market
    for (std::map < std::string, Market * >::iterator itr =
         markets.begin(); itr != markets.end(); ++itr) {
        cerr << "Market: " << (*itr).first << endl;
        (*itr).second->tick();

    }

    //for each factory
    for (std::map < std::string, Factory * >::iterator itr =
         factories.begin(); itr != factories.end(); ++itr) {
        cerr << "Factory: " << (*itr).first << endl;
        (*itr).second->maxProfit((*itr).second->capital);
        (*itr).second->executeBestProductionOption();
    }

    //for each factory map
    for (std::map < std::string, std::string >::iterator itr =
         consumerMap.begin(); itr != consumerMap.end(); ++itr) {
        cerr << "Consumer map: " << (*itr).first << " owned by " << (*itr).
            second << endl;
        Factory *pfactory = factories[(*itr).first];
        Consumer *pconsumer = consumers[(*itr).second];
        double profits = pfactory->capital - pfactory->initialcapital;
        if (profits > 0.0) {
            //pay dividends
            double dividend = profits * this->dividendrate;
            pconsumer->capital += dividend;
            pfactory->capital -= dividend;
            pfactory->dividends += dividend;
        }
    }

    //for each consumer
    for (std::map < std::string, Consumer * >::iterator itr =
         consumers.begin(); itr != consumers.end(); ++itr) {
        cerr << "Consumer: " << (*itr).first << endl;
        Consumer *pconsumer = (*itr).second;
        pconsumer->tick();
    }
}


//dump status
void Economy::dump()
{
    cerr << "========" << endl;
    //for each market
    for (std::map < std::string, Market * >::iterator itr =
         markets.begin(); itr != markets.end(); ++itr) {
        cerr << "Market:" << (*itr).first << endl;
        (*itr).second->dump();
    }
    cerr << "========" << endl;
    //for each market
    for (std::map < std::string, Market * >::iterator itr =
         markets.begin(); itr != markets.end(); ++itr) {
        cerr << "Market:" << (*itr).first << " ";
        (*itr).second->dump_summary();
    }
    cerr << "========" << endl;
    //for each factory
    for (std::map < std::string, Factory * >::iterator itr =
         factories.begin(); itr != factories.end(); ++itr) {
        cerr << "Factory:" << (*itr).first << " ";
        (*itr).second->dump();
    }
    cerr << "========" << endl;
    //for each consumer
    for (std::map < std::string, Consumer * >::iterator itr =
         consumers.begin(); itr != consumers.end(); ++itr) {
        cerr << "Consumer:" << (*itr).first << " ";
        cerr << "capital=" << (*itr).second->capital << endl;
    }
}

void Economy::reset_statistics()
{
    //for each market
    for (std::map < std::string, Market * >::iterator itr =
         markets.begin(); itr != markets.end(); ++itr) {
        (*itr).second->reset_statistics();
    }
}

//initialize a market by placing orders
void Economy::placeSellOrders(std::string what, double loprice,
                              int loamount, double hiprice, int hiamount,
                              int steps)
{
    Market *pmarket = this->markets[what];
    for (int i = 0; i <= steps; ++i) {
        double price = ((steps - i) * hiprice + i * loprice) / steps;
        int amount = ((steps - i) * hiamount + i * loamount) / steps;
        pmarket->addSellOrder(price, amount, "initializer");
    }
}

//initialize a market by placing orders
void Economy::placeBuyOrders(std::string what, double loprice,
                             int loamount, double hiprice, int hiamount,
                             int steps)
{
    Market *pmarket = this->markets[what];
    for (int i = 0; i <= steps; ++i) {
        double price = ((steps - i) * loprice + i * hiprice) / steps;
        int amount = ((steps - i) * loamount + i * hiamount) / steps;
        pmarket->addBuyOrder(price, amount, "initializer");
    }
}

//add a consumer
void Economy::addConsumer(Consumer * consumer)
{
    this->consumers[consumer->name] = consumer;
}

//make the consumer profit from the gains of this factory
void Economy::addConsumerMap(std::string factoryName,
                             std::string consumerName)
{
    this->consumerMap[factoryName] = consumerName;
}

void Economy::addElement(scew_element * root) const const
{
    scew_element *element = NULL;
    scew_element *sub_element = NULL;
//    scew_element* sub_sub_element = NULL;
//    scew_attribute* attribute = NULL;

    element = scew_element_add(root, "currencyName");
    scew_element_set_contents(element, currencyName.c_str());

    element = scew_element_add(root, "populaceName");
    scew_element_set_contents(element, populaceName.c_str());

    element = scew_element_add(root, "dividendrate");
    scew_element_set_contents(element, toCString(dividendrate));

    element = scew_element_add(root, "markets");
    //for each market
    for (std::map < string, Market * >::const_iterator itr =
         markets.begin(); itr != markets.end(); ++itr) {
        sub_element = scew_element_add(element, "market");
        scew_element_add_attr_pair(sub_element, "name",
                                   (*itr).first.c_str());
        (*itr).second->addElement(sub_element);
    }

    element = scew_element_add(root, "factories");
    //for each factory
    for (std::map < string, Factory * >::const_iterator itr =
         factories.begin(); itr != factories.end(); ++itr) {
        sub_element = scew_element_add(element, "factory");
        scew_element_add_attr_pair(sub_element, "name",
                                   (*itr).first.c_str());
        (*itr).second->addElement(sub_element);
    }

    element = scew_element_add(root, "consumers");
    //for each consumer
    for (std::map < string, Consumer * >::const_iterator itr =
         consumers.begin(); itr != consumers.end(); ++itr) {
        sub_element = scew_element_add(element, "consumer");
        scew_element_add_attr_pair(sub_element, "name",
                                   (*itr).first.c_str());
        (*itr).second->addElement(sub_element);
    }

    element = scew_element_add(root, "consumerMap");
    //for each consumer
    for (std::map < string, string >::const_iterator itr =
         consumerMap.begin(); itr != consumerMap.end(); ++itr) {
        sub_element = scew_element_add(element, "owner");
        scew_element_add_attr_pair(sub_element, "factory",
                                   (*itr).first.c_str());
        scew_element_set_contents(sub_element, (*itr).second.c_str());
    }
}

Economy *Economy::economyFromElement(scew_element * element, Economy * pe)
{
    XML_Char const *contents = NULL;

    for (scew_element * sub_element = scew_element_next(element, NULL);
         NULL != sub_element;
         sub_element = scew_element_next(element, sub_element)) {
        if (0 == strcmp(scew_element_name(sub_element), "currencyName")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                pe->currencyName = string(contents);
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element),
                          "populaceName")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                pe->populaceName = string(contents);
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element),
                          "dividendrate")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                pe->dividendrate =
                    doubleFromCString(contents, pe->dividendrate);
            }
        } else if (0 == strcmp(scew_element_name(sub_element), "markets")) {
            for (scew_element * sub_sub_element =
                 scew_element_next(sub_element, NULL);
                 NULL != sub_sub_element;
                 sub_sub_element =
                 scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                    strcmp(scew_element_name(sub_sub_element), "market")) {
                    XML_Char const *what = NULL;
                    scew_attribute *attribute = NULL;
                    attribute =
                        scew_attribute_by_name(sub_sub_element, "name");
                    if (NULL != attribute) {
                        what = scew_attribute_value(attribute);
                    }
                    if (NULL != what) {
                        Market *pmarket =
                            Market::marketFromElement(sub_sub_element);
                        if (NULL != pmarket) {
                            pe->markets[string(what)] = pmarket;
                            //delete pmarket;
                        }
                    }
                }
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element), "factories")) {
            for (scew_element * sub_sub_element =
                 scew_element_next(sub_element, NULL);
                 NULL != sub_sub_element;
                 sub_sub_element =
                 scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                    strcmp(scew_element_name(sub_sub_element),
                           "factory")) {
                    XML_Char const *what = NULL;
                    scew_attribute *attribute = NULL;
                    attribute =
                        scew_attribute_by_name(sub_sub_element, "name");
                    if (NULL != attribute) {
                        what = scew_attribute_value(attribute);
                    }
                    if (NULL != what) {
                        Factory *pf =
                            Factory::factoryFromElement(sub_sub_element,
                                                        pe);
                        if (NULL != pf) {
                            pe->factories[string(what)] = pf;
                            //delete pf;
                        }
                    }
                }
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element), "consumers")) {
            for (scew_element * sub_sub_element =
                 scew_element_next(sub_element, NULL);
                 NULL != sub_sub_element;
                 sub_sub_element =
                 scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                    strcmp(scew_element_name(sub_sub_element),
                           "consumer")) {
                    XML_Char const *what = NULL;
                    scew_attribute *attribute = NULL;
                    attribute =
                        scew_attribute_by_name(sub_sub_element, "name");
                    if (NULL != attribute) {
                        what = scew_attribute_value(attribute);
                    }
                    if (NULL != what) {
                        Consumer *pc =
                            Consumer::consumerFromElement(sub_sub_element,
                                                          pe,
                                                          string(what));
                        if (NULL != pc) {
                            pe->consumers[string(what)] = pc;
                            //delete pc;
                        }
                    }
                }
            }
        } else if (0 ==
                   strcmp(scew_element_name(sub_element), "consumerMap")) {
            for (scew_element * sub_sub_element =
                 scew_element_next(sub_element, NULL);
                 NULL != sub_sub_element;
                 sub_sub_element =
                 scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                    strcmp(scew_element_name(sub_sub_element), "owner")) {
                    XML_Char const *factory = NULL;
                    scew_attribute *attribute = NULL;
                    attribute =
                        scew_attribute_by_name(sub_sub_element, "factory");
                    if (NULL != attribute) {
                        factory = scew_attribute_value(attribute);
                    }
                    XML_Char const *owner = NULL;
                    owner = scew_element_contents(sub_sub_element);
                    if (NULL != factory && NULL != owner) {
                        pe->consumerMap[string(factory)] = string(owner);
                    }
                }
            }
        }
    }
    return pe;
}
