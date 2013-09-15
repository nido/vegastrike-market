/*
 * Copyright(c) 2009: peter.schaefer@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Factory for producing goods, v 0.1.3
 * @author peter.schaefer@gmail.com
 */  
#include <limits>
    
#include <string>
    
#include <vector>
    
#include "roottracker.hpp"
    
#include "btree_iterator.hpp"
    
#include "Market.hpp"
#include "Factory.hpp"
#include "ProductionOption.hpp"
    
#include <assert.h>
    
#include <math.h>
     
//create a really empty factory with default values for filling from XML
    Factory::Factory()
{
    this->initialcapital = 0.0;
    this->capital = 0.0;
    this->dividends = 0.0;
    this->economy = NULL;
    setRateofreturn(0.01);
    this->name = "";
    reset();
    this->totalproduction = 0.0;
}

 
//create an empty factory
    Factory::Factory(double capital, Economy * economy,
                     double rateofreturn, string name)
{
    this->initialcapital = capital;
    this->capital = capital;
    this->dividends = 0.0;
    this->economy = economy;
    setRateofreturn(rateofreturn);
    this->name = name;
    reset();
    this->totalproduction = 0.0;
}  void Factory::setRateofreturn(double rateofreturn)
{
    this->rateofreturn = rateofreturn;
}  

//add outputs(positive) and inputs(negative)
void Factory::addProductionOption(ProductionOption po)
{
    this->options.push_back(po);
}  

//reset all calculated values (for example because markets have changed)
void Factory::reset()
{
    this->bestOptionPtr = NULL;
    this->bestOptionProfit = -std::numeric_limits < float >::max();
    this->bestOptionProductionUnits = 0.0;
    this->bestOptionPriceMultiplier = 1.0;
}  

//estimate the best profit to be made
void Factory::maxProfit(double capitalavailable)
{
    cerr << name << ":" << "maxProfit " << name << " capital:" <<
        capitalavailable << endl;
    assert(capitalavailable >= 0.0);
     this->bestOptionPtr = NULL;
    this->bestOptionProfit = -std::numeric_limits < float >::max();
    this->bestOptionProductionUnits = 0.0;
     
        //for each option
        for (vector < ProductionOption >::iterator itr =
             this->options.begin(); itr != this->options.end(); ++itr) {
        if ((*itr).sectorsize > 0.0 && (*itr).sectormin > 0.0) {
            
                //try to find a maximum with up to 4 steps for when lower output gives better profit
                //TODO: need better algorithm
            double loproductionsize = (*itr).sectormin;
            cerr << "analysing[" << loproductionsize << "] lo" << endl;
            double loprofit =
                calculate_profit(*itr, loproductionsize, capitalavailable,
                                 true);
            if (loprofit >= 0.0 && (*itr).sectorsize > (*itr).sectormin) {
                double hiproductionsize = (*itr).sectorsize;
                cerr << "analysing[" << hiproductionsize << "] hi" <<
                    endl;
                double hiprofit =
                    calculate_profit(*itr, hiproductionsize,
                                     capitalavailable, false);
                 int n = 4;
                while (--n > 0) {
                    cerr << "analysing[" << loproductionsize << "," <<
                        hiproductionsize << "] #" << n << endl;
                    
                        //arithmetic mean
                    double middleproductionsize =
                        sqrt(loproductionsize * hiproductionsize);
                    double middleprofit =
                        calculate_profit(*itr, middleproductionsize,
                                         capitalavailable, false);
                     bool hicondition = middleprofit > hiprofit
                        && loprofit > hiprofit;
                    bool locondition = middleprofit > loprofit
                        && hiprofit > loprofit;
                     if (hicondition && locondition) {
                        
                            //in between is better - assume the graph is convex
                            //maybe things are better near the middle
                            loproductionsize =
                            sqrt(loproductionsize * middleproductionsize);
                        loprofit =
                            calculate_profit(*itr, loproductionsize,
                                             capitalavailable, false);
                        hiproductionsize =
                            sqrt(middleproductionsize * hiproductionsize);
                        hiprofit =
                            calculate_profit(*itr, hiproductionsize,
                                             capitalavailable, false);
                    } else if (hicondition) {
                        
                            //discard the worst value
                            hiproductionsize = middleproductionsize;
                        hiprofit = middleprofit;
                    } else if (locondition) {
                        
                            //discard the worst value
                            loproductionsize = middleproductionsize;
                        loprofit = middleprofit;
                    } else {
                        
                            //in between is worse - assume the graph is concave
                            break;
                    }
                     if (hiproductionsize - loproductionsize <= 0.0) {
                        break;
                    }
                }
            }
        }
    }
 }

 
//calculate profit; side-effect: set the best Option as the better option
double Factory::calculate_profit(ProductionOption & po,
                                 double productionsize,
                                 double capitalavailable, bool makeitwork)
{
     double moneyneeded = calculate_moneyneeded(po, productionsize);
     double production_base =
        calculate_production_base(po, productionsize);
     
        //cap the capital needed at the available capital and estimate how many production units this will activate.
    double production_units;
    if (moneyneeded <= 0.0 || capitalavailable <= 0.0) {
        production_units = production_base;
        cerr << name << ":" << "production option production_base(pus=" <<
            production_units << ")!" << endl;
    } else {
        
            //factor = this->capital / moneyneeded
            production_units =
            production_base +
            ((productionsize -
              production_base) * capitalavailable) / moneyneeded;
        cerr << name << ":" << "production option interpolated(pus=" <<
            production_units << ")!" << endl;
    }
     
        //special rule: there must be enough resources and capital to produce with at least 1.0 sectorsize
        if (production_units < 1.0) {
        production_units = 0.0;
    }
     if (production_units > productionsize) {
        production_units = productionsize;
    } else {
        
            //moneyneeded = capitalavailable;//HACK
    }
    cerr << name << ":" << "production option final(pus=" <<
        production_units << ")!" << endl;
     double moneyresulting =
        calculate_moneyresulting(po, production_units);
     cerr << name << ":" << "moneyresulting:" << moneyresulting << endl;
    cerr << name << ":" << "moneyneeded:" << moneyneeded << endl;
    double profit = moneyresulting - moneyneeded;
     
        //HACK - produce a little bit if we can't produce
        //TODO This needs some more restrictions
    double multiplier;
    if (profit <= 0.0 && makeitwork && moneyresulting > 0.0
         && this->capital > 0.5 * this->initialcapital) {
        multiplier =
            moneyneeded * (1.0 + this->rateofreturn) / moneyresulting;
        profit = multiplier * moneyresulting - moneyneeded;
        cerr << name << ":" << "multiplier=" << multiplier << endl;
    } else {
        multiplier = 1.0;
    }
     if (profit > this->bestOptionProfit) {
        cerr << name << ":" << "better option(pus=" << production_units <<
            ")!" << endl;
        this->bestOptionPtr = &po;
        this->bestOptionProfit = profit;
        this->bestOptionProductionUnits = production_units;
        this->bestOptionInvestment = moneyneeded;
        this->bestOptionPriceMultiplier = multiplier;
    }
     return profit;
}

 
//calculate the sum of capital needed for buying the inputs from the markets
double Factory::calculate_moneyneeded(ProductionOption & po,
                                      double productionsize)
{
    double moneyneeded = 0.0;
    for (Products::const_iterator pitr = po.inputs.begin();
          pitr != po.inputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aneed = (*pitr).second * productionsize; //- amount * sectorsize
        double totalreserves = this->reserve[aname].getReserve();   //should be >= 0.0
        cerr << name << ":" << "reserve of " << aname << "=" <<
            totalreserves << endl;
        double amoneyneed;
        double reservesneeded;
        if (aneed > totalreserves) {
            
                //buy from market?
            int amount = (int) ceil(aneed - totalreserves);
            cerr << name << ":" << "amount " << aname << "=" << amount <<
                endl;
            Market * pmarket = this->economy->markets[aname];
            double marketprice =
                pmarket->max_market_price_when_buying_n(amount,
                                                        amoneyneed);
            if (marketprice == 0.0
                 || marketprice >= std::numeric_limits < float >::max()) {
                
                    //HACK
                    marketprice =
                    this->economy->markets[aname]->highest_buy_offer() *
                    (1.0 + this->rateofreturn);
                amoneyneed = amount * marketprice;
                 
                    //WIP return std::numeric_limits<float>::max();
                    //break;
            }
            cerr << name << ":" << "market price " << aname << "=" <<
                marketprice << " needed=" << amoneyneed << endl;
            reservesneeded = totalreserves;
        } else {
            amoneyneed = 0.0;
            reservesneeded = aneed;
        }
        cerr << name << ":" << "amoneyneed=" << amoneyneed << endl;
        if (reservesneeded > 0.0) {
            double delta =
                amoneyneed +
                this->reserve[aname].getPrice() * reservesneeded;
            cerr << name << ":" << "delta=" << delta << endl;
            moneyneeded += delta;
        } else {
            moneyneeded += amoneyneed;
        }
    }
    return moneyneeded;
}

 
//calculate how much can be produced with no resources being bought
double Factory::calculate_production_base(ProductionOption & po,
                                          double productionsize)
{
     double production_base = productionsize;
    for (Products::const_iterator pitr = po.inputs.begin();
          pitr != po.inputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aneed = (*pitr).second * productionsize; //- amount * sectorsize
        double totalreserves = this->reserve[aname].getReserve();   //should be >= 0.0
        double production_factor = totalreserves / aneed;
        if (production_factor < production_base) {
            production_base = production_factor;
        }
    }
    return production_base;
}

 
//calculate the profit expected
double Factory::calculate_moneyresulting(ProductionOption & po,
                                         double production_units)
{
    double moneyresulting = 0.0;
    for (Products::const_iterator pitr = po.outputs.begin();
          pitr != po.outputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aresulting = (*pitr).second * production_units;  //amount * sectorsize
        double amoneyresulting;
        
            //sell to market
        double marketprice =
            this->economy->markets[aname]->
            min_market_price_when_selling_n((int) aresulting,
                                            amoneyresulting);
        if (marketprice >= std::numeric_limits < float >::max()) {
            
                // if there is no market price set, choose a lower price
                marketprice =
                this->economy->markets[aname]->last_deal_price() / (1.0 +
                                                                    this->
                                                                    rateofreturn);
            amoneyresulting = aresulting * marketprice;
        } else if (marketprice <= 0.0) {
            amoneyresulting = 0.0;
        }
        cerr << name << ":" << "market price " << aname << "=" <<
            marketprice << " amoneyresulting=" << amoneyresulting << endl;
        moneyresulting += amoneyresulting;
    }
    return moneyresulting;
}

 
//try to execute the option last estimated as having best profit and return the number of production units active
double Factory::executeBestProductionOption()
{
    cerr << name << ":" << "executeBestProductionOption " << name <<
        " profit=" << this->bestOptionProfit << endl;
    if (this->bestOptionProfit < 0.0) {
        this->maxProfit(this->capital);
    }
    if (NULL == this->bestOptionPtr) {
        return 0.0;
    }
    if (this->bestOptionProfit <= 0.0) {
        return 0.0;
    }
     
        //if we don't meet our profit margins, try to buy cheaply and sell dearly (50:50)
    double profitfactor;
    double profitrate;
    if (this->bestOptionInvestment <= 0.0) {
        profitrate = 100.0;
    } else {
        profitrate = this->bestOptionProfit / this->bestOptionInvestment;
    }
    if (profitrate < 1.0 + this->rateofreturn) {
        profitfactor = (1.0 + (this->rateofreturn - profitrate) / 2);
    } else {
        
            //WIP
            if (profitrate > 4.0) {
            profitfactor = 1.0 / 2.0;
        } else {
            profitfactor = 1.0 / sqrt(profitrate);
        }
    }
     
        //buy stuff; if we don't meet rateofreturn targets, place buy orders that are below market prices
        for (Products::const_iterator pitr =
             (*this->bestOptionPtr).inputs.begin();
             pitr != (*this->bestOptionPtr).inputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aneed = (*pitr).second * this->bestOptionProductionUnits;    //- amount * production
        double totalreserves = this->reserve[aname].getReserve();   //should be >= 0.0
        cerr << name << ":" << " aneed= " << aneed << " totalreserves=" <<
            totalreserves << endl;
        if (aneed > totalreserves) {
            
                //buy from market
            int amount = (int) ceil(aneed - totalreserves);
            double amoneyneed;
            double marketprice =
                this->economy->markets[aname]->
                max_market_price_when_buying_n(amount, amoneyneed);
            if (marketprice == 0.0
                 || marketprice >= std::numeric_limits < float >::max()) {
                marketprice = this->economy->markets[aname]->highest_buy_offer() * (1.0 + this->rateofreturn); //HACK
                cerr << name << ":" << " selecting higher prices for " <<
                    aname << " amount=" << amount << "@" << marketprice;
            }
            cerr << name << ":" << " adding buy order to " << aname <<
                " amount=" << amount << " @" << (int) floor(marketprice /
                                                            profitfactor)
                << " /profitfactor=" << profitfactor << endl;
            this->economy->markets[aname]->addBuyOrder(marketprice /
                                                        profitfactor,
                                                        amount,
                                                        this->name);
            
                //pay ahead of execution
            double total = marketprice / profitfactor * amount;
            this->addResources(this->economy->currencyName, -total,
                                -total);
        }
    }  
        //economy::check markets for open transaction
        (void) this->economy->executeTransactions();
     cerr << name << ":" << "check whether we got enough resources" <<
        endl;
    
        //check whether we got enough resources
    double production = this->bestOptionProductionUnits;
    for (Products::const_iterator pitr =
          (*this->bestOptionPtr).inputs.begin();
          pitr != (*this->bestOptionPtr).inputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aneed = (*pitr).second * (*this->bestOptionPtr).sectorsize;  //- amount * sectorsize
        double totalreserves = this->reserve[aname].getReserve();   //should be >= 0.0
        cerr << name << ":" << "checking " << aname << " amount=" << aneed
            << " against reserves=" << totalreserves << endl;
        if (aneed < totalreserves) {
            totalreserves = aneed;
        }
        cerr << name << ":" << "amount/1ss=" << (*pitr).second << endl;
        double factor = totalreserves / (*pitr).second;
        if (factor < production) {
            production = factor;
        }
        cerr << name << ":" << "production set to " << production << endl;
    }
     
        //special rule: at least 1.0 production
        if (production < 1.0) {
        cerr << name << ":" << "no production!" << endl;
        production = 0.0;
        this->reset();
        return production;
    }
     if (production > (*this->bestOptionPtr).sectorsize) {
        production = (*this->bestOptionPtr).sectorsize;
    }
    cerr << name << ":" << "production set to(final) " << production <<
        endl;
     cerr << name << ":" << "consume:" << endl;
    
        //consume
        for (Products::const_iterator pitr =
             (*this->bestOptionPtr).inputs.begin();
             pitr != (*this->bestOptionPtr).inputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aneed = (*pitr).second * production; //- amount * sectorsize
        this->reserve[aname].subtractReserve(aneed,
                                             name + ":consuming " + aname);
    }  
        //produce and sell stuff
        for (Products::const_iterator pitr =
             (*this->bestOptionPtr).outputs.begin();
             pitr != (*this->bestOptionPtr).outputs.end(); ++pitr) {
        string aname = (*pitr).first;  //name
        double aamount = (*pitr).second * production;   //- amount * sectorsize
        
            //get price
        double amoneyreceived;
        double marketprice =
            this->economy->markets[aname]->
            min_market_price_when_selling_n((int) floor(aamount),
                                            amoneyreceived);
        if (marketprice == 0.0
             || marketprice >= std::numeric_limits < float >::max()) {
            marketprice =
                this->economy->markets[aname]->lowest_sell_offer() / (1.0 +
                                                                      this->
                                                                      rateofreturn);
        }
         
            //only sell integer part of production
        double price =
            marketprice * profitfactor * this->bestOptionPriceMultiplier;
        this->reserve[aname].addReserve(aamount, aamount * price,
                                         name + ": producing " + aname);
        int amount = (int) floor(this->reserve[aname].getReserve());
         
            //sell
            if (amount > 0) {
            this->reserve[aname].subtractReserve(aamount,
                                                  name + ": selling " +
                                                  aname);
            this->economy->markets[aname]->addSellOrder(price, amount,
                                                         this->name);
        }
    }
     growSector(production);
     this->totalproduction += production;
     return production;
}

 
//build another factory of this type, if possible
void Factory::growSector(double production)
{
    if (this->bestOptionProductionUnits <= 0.0)
        return;
     if (production >= this->bestOptionPtr->sectorsize) {
        cerr << name << " trying to grow!" << endl;
        double amoneyneed = 0.0;
        std::map < string, double >marketprices;
        for (Products::const_iterator pitr =
              (*this->bestOptionPtr).costofanother.begin();
              pitr != (*this->bestOptionPtr).costofanother.end(); ++pitr) {
            string aname = (*pitr).first;  //name
            double amount =
                (*pitr).second - this->reserve[aname].getReserve();
            double marketprice = 0.0;
            if (amount > 0.0) {
                marketprice =
                    this->economy->markets[aname]->
                    max_market_price_when_buying_n((int) ceil(amount),
                                                   amoneyneed);
                cerr << name << ":" << "market price " << aname << "=" <<
                    marketprice << " needed=" << amoneyneed << endl;
            }
            marketprices[aname] = marketprice;
        }   double profitOfOne =
            this->bestOptionProfit / this->bestOptionProductionUnits;
        double factorp1 = profitOfOne / (amoneyneed * this->rateofreturn);
        if (factorp1 > 1.1)
            factorp1 = 1.1;
        if (amoneyneed < this->capital && factorp1 > 0.5) {
            for (Products::const_iterator pitr =
                  (*this->bestOptionPtr).costofanother.begin();
                  pitr != (*this->bestOptionPtr).costofanother.end();
                  ++pitr) {
                string aname = (*pitr).first;  //name
                double amount =
                    (*pitr).second - this->reserve[aname].getReserve();
                if (amount > 0.0) {    //This condition is not true when the reserves have been filled for production, that is when production uses same resources as growth
                    double marketprice = marketprices[aname] * factorp1;
                    this->economy->markets[aname]->
                        addBuyOrder(marketprice, (int) ceil(amount),
                                    this->name);
                    
                        //pay ahead of execution
                    double total = marketprice * amount;
                    this->addResources(this->economy->currencyName,
                                        -total, -total);
                    
                        //force bid execution
                        //distribute successful market transactions
                        this->economy->executeTransactions();
                }
            }  
                //we now should have enough resources to grow
            double factor = 1.0;
            for (Products::const_iterator pitr =
                  (*this->bestOptionPtr).costofanother.begin();
                  pitr != (*this->bestOptionPtr).costofanother.end();
                  ++pitr) {
                string aname = (*pitr).first;  //name
                double amount = (*pitr).second;
                double f = this->reserve[aname].getReserve() / amount;
                if (f < factor) {
                    factor = f;
                }
            }
            if (factor > 0.0) {
                cerr << name << " growing by " << factor << endl;
                for (Products::const_iterator pitr =
                      (*this->bestOptionPtr).costofanother.begin();
                      pitr != (*this->bestOptionPtr).costofanother.end();
                      ++pitr) {
                    string aname = (*pitr).first;  //name
                    double amount = (*pitr).second * factor;
                    this->reserve[aname].subtractReserve(amount,
                                                          name +
                                                          ":investing " +
                                                          aname);
                } this->bestOptionPtr->sectorsize += factor;
            }
        }
    }
}  

//receive or remove resources from the reserve
void Factory::addResources(string what, double amount, double totalprice)
{
    if (what == this->economy->currencyName) {
        this->capital += amount;
    } else {
        
            //modify resources
            this->reserve[what].addReserve(amount, totalprice,
                                           name + ":addResources " + what);
    }
}

 
//dump factory status report for development
void Factory::dump()
{
    cerr.setf(ios_base::fixed, ios_base::floatfield);
    cerr.precision(2);
     cerr << "capital:" << this->capital << " ";
    if (this->bestOptionPtr != NULL) {
        for (Products::const_iterator pitr =
              (*this->bestOptionPtr).outputs.begin();
              pitr != (*this->bestOptionPtr).outputs.end(); ++pitr) {
            string aname = (*pitr).first;  //name
            double marketprice =
                this->economy->markets[aname]->last_deal_price();
            if (marketprice >= std::numeric_limits < float >::max()) {
                marketprice = std::numeric_limits < float >::max();
            } else if (marketprice <= 0.0) {
                marketprice = 0.0;
            }
            cerr.precision(6);
            cerr << " output " << aname << " price=" << marketprice <<
                " ";
            cerr.precision(2);
        }
    }
    cerr << "activity[sss]:" << totalproduction << " ";
    cerr << "dividends:" << dividends << " ";
    cerr << endl;
    
        //cerr.setf(ios_base::scientific, ios_base::floatfield);
        //cerr.precision(8);
        //TODO
}

 
//destructor
    Factory::~Factory()
{
}

  void Factory::addElement(scew_element * root) const const
{
    scew_element * element = NULL;
    scew_element * sub_element = NULL;
     element = scew_element_add(root, "name");
    scew_element_set_contents(element, name.c_str());
     element = scew_element_add(root, "totalproduction");
    scew_element_set_contents(element, toCString(totalproduction));
     element = scew_element_add(root, "options");
    
        //for each option
        for (vector < ProductionOption >::const_iterator itr =
             options.begin(); itr != options.end(); ++itr) {
        sub_element = scew_element_add(element, "option");
        (*itr).addElement(sub_element);
    }
     element = scew_element_add(root, "initialcapital");
    scew_element_set_contents(element, toCString(initialcapital));
     element = scew_element_add(root, "capital");
    scew_element_set_contents(element, toCString(capital));
     element = scew_element_add(root, "dividends");
    scew_element_set_contents(element, toCString(dividends));
     element = scew_element_add(root, "rateofreturn");
    scew_element_set_contents(element, toCString(rateofreturn));
     element = scew_element_add(root, "reserves");
    
        //for each reserve
        for (map < string, Reserve >::const_iterator itr = reserve.begin();
             itr != reserve.end(); ++itr) {
        sub_element = scew_element_add(element, "reserve");
        scew_element_add_attr_pair(sub_element, "name",
                                    (*itr).first.c_str());
        (*itr).second.addElement(sub_element);
    }
}

  Factory * Factory::factoryFromElement(scew_element * element,
                                           Economy * economy)
{
    Factory * pf = NULL;
    XML_Char const *contents = NULL;
     pf = new Factory();
    pf->economy = economy;
     string name;
    double totalproduction = 0.0;
    double initialcapital = 1000000.0;
    double capital = 1000000.0;
    double dividends = 0.0;
    double rateofreturn = 0.01;
     for (scew_element * sub_element = scew_element_next(element, NULL);
            NULL != sub_element;
            sub_element = scew_element_next(element, sub_element)) {
        if (0 == strcmp(scew_element_name(sub_element), "name")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                name = string(contents);
            }
        } else if (0 ==
                    strcmp(scew_element_name(sub_element),
                           "totalproduction")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                totalproduction =
                    doubleFromCString(contents, totalproduction);
            }
        } else if (0 == strcmp(scew_element_name(sub_element), "options")) {
            for (scew_element * sub_sub_element =
                  scew_element_next(sub_element, NULL);
                  NULL != sub_sub_element;
                  sub_sub_element =
                  scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                     strcmp(scew_element_name(sub_sub_element),
                            "option")) {
                    ProductionOption * ppo =
                        ProductionOption::
                        productionOptionFromElement(sub_sub_element);
                    if (NULL != ppo) {
                        pf->addProductionOption(*ppo);
                        delete ppo;
                    }
                }
            }
        } else if (0 ==
                    strcmp(scew_element_name(sub_element),
                           "initialcapital")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                initialcapital =
                    doubleFromCString(contents, initialcapital);
            }
        } else if (0 == strcmp(scew_element_name(sub_element), "capital")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                capital = doubleFromCString(contents, capital);
            }
        } else if (0 ==
                    strcmp(scew_element_name(sub_element), "dividends")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                dividends = doubleFromCString(contents, dividends);
            }
        } else if (0 ==
                    strcmp(scew_element_name(sub_element),
                           "rateofreturn")) {
            contents = scew_element_contents(sub_element);
            if (NULL != contents) {
                rateofreturn = doubleFromCString(contents, rateofreturn);
            }
        } else if (0 ==
                    strcmp(scew_element_name(sub_element), "reserves")) {
            for (scew_element * sub_sub_element =
                  scew_element_next(sub_element, NULL);
                  NULL != sub_sub_element;
                  sub_sub_element =
                  scew_element_next(sub_element, sub_sub_element)) {
                if (0 ==
                     strcmp(scew_element_name(sub_sub_element),
                            "reserve")) {
                    XML_Char const *what = NULL;
                    scew_attribute * attribute = NULL;
                    attribute =
                        scew_attribute_by_name(sub_sub_element, "name");
                    if (NULL != attribute) {
                        what = scew_attribute_value(attribute);
                    }
                    if (NULL != what) {
                        Reserve * pr =
                            Reserve::reserveFromElement(sub_sub_element);
                        if (NULL != pr) {
                            pf->addResources(string(what),
                                              pr->getReserve(),
                                              pr->getReserveValue());
                            delete pr;
                        }
                    }
                }
            }
        }
    }
     pf->name = name;
    if (totalproduction > 0.0)
        pf->totalproduction = totalproduction;
     if (initialcapital > 0.0)
        pf->initialcapital = initialcapital;
     if (capital > 0.0)
        pf->capital = capital;
     if (dividends > 0.0)
        pf->dividends = dividends;
     if (rateofreturn > 0.0)
        pf->rateofreturn = rateofreturn;
     return pf;
}

 
