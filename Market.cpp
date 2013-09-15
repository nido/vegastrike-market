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
 * Market for trading goods, version 0.1.3
 * Market first version: 17th of january 2009 by peter.schaefer@gmail.com
 * Market current version: 27th of february 2009 by peter.schaefer@gmail.com
 *
 */  
#include <limits>
    
#include "Market.hpp"
    
#include <math.h>
    
//create an empty market
    Market::Market()
{
    last_deal = 0.0;
    reset_statistics();
     Node * root_ptr_sell = new Node(trackerSell);
    trackerSell.set_root(null_ptr, root_ptr_sell);
     Node * root_ptr_buy = new Node(trackerBuy);
    trackerBuy.set_root(null_ptr, root_ptr_buy);
     timer = 0;
     decayrate = 1.0;
}

 void Market::setLastDeal(double price, int amount)
{
    last_deal = price;
    if (last_deal > highest_price)
        highest_price = last_deal;
    if (last_deal < lowest_price)
        lowest_price = last_deal;
    number_of_trades += amount;
    value_of_trades += price * amount;
}

 
//flush the statistics
void Market::reset_statistics()
{
    lowest_price = std::numeric_limits < float >::max();   //using float, because cerr cannot display std::numeric_limits<double>::max
    highest_price = 0.0;
    number_of_trades = 0.0;
    value_of_trades = 0.0;
}   

//average value of trades
double Market::avg_value_of_trades()
{
    if (number_of_trades <= 0.0) {
        return 0.0;
    } else {
        return value_of_trades / number_of_trades;
    }
}

   
//adds a sell order
void Market::addSellOrder(double price, int amount, string id,
                          long precedence)
{
    long time;
    time = precedence > 0 ? precedence : ++timer;
     Elem sell_order_elem = Elem();
    Elem * sell_order = &sell_order_elem;
     sell_order->m_key = price;
    sell_order->m_secondkey = time;
     sell_order->m_payload.first = amount;
    sell_order->m_payload.second = id;
     int buy_first_index =
        static_cast < int >(executedSellOrders.size());
    Elem * buy_order;
    BTree_Iterator buy_orders = getBuyOrders();
    while ((buy_order = buy_orders.prev()) != NULL 
            &&sell_order->m_payload.first > 0 
            &&sell_order->m_key <= buy_order->m_key ) {
        
            //cerr << " sell_order->price: " << sell_order->m_key << " buy_order->price " << buy_order->m_key << " sell_order->amount: " <<sell_order->m_payload.first << endl;
            Elem * executed_buy_order = new Elem();
         executed_buy_order->m_key = last_deal;
        executed_buy_order->m_secondkey = buy_order->m_secondkey;
        executed_buy_order->m_payload.second =
            buy_order->m_payload.second;
         Elem * executed_sell_order = new Elem();
         executed_sell_order->m_key = last_deal;
        executed_sell_order->m_secondkey = sell_order->m_secondkey;
        executed_sell_order->m_payload.second =
            sell_order->m_payload.second;
         if (buy_order->m_payload.first < sell_order->m_payload.first) {
            executed_sell_order->m_payload.first =
                buy_order->m_payload.first;
            executed_buy_order->m_payload.first =
                buy_order->m_payload.first;
        } else if (buy_order->m_payload.first >
                    sell_order->m_payload.first) {
            executed_sell_order->m_payload.first =
                sell_order->m_payload.first;
            executed_buy_order->m_payload.first =
                sell_order->m_payload.first;
        } else {
            executed_sell_order->m_payload.first =
                sell_order->m_payload.first;
            executed_buy_order->m_payload.first =
                buy_order->m_payload.first;
        }
         setLastDeal(buy_order->m_key,
                       executed_buy_order->m_payload.first);
         
            //store difference of price(=first) in a structure for paying back sums paid in ahead
            Payback * payback = new Payback();
        payback->first =
            (buy_order->m_key -
             sell_order->m_key) * executed_buy_order->m_payload.first;
        payback->second = buy_order->m_payload.second;
        this->paybacks.push_back(payback);
         executedSellOrders.push_back(executed_sell_order);
        executedBuyOrders.push_back(executed_buy_order);
         sell_order->m_payload.first -=
            executed_sell_order->m_payload.first;
        buy_order->m_payload.first -= executed_buy_order->m_payload.first;
     }
     if (sell_order->m_payload.first == 0) {
        
            //don't insert
    } else {
        trackerSell.get_root()->tree_insert(*sell_order);
    }
     for (int i = buy_first_index;
            i < static_cast < int >(executedBuyOrders.size()); ++i) {
        Node * last;
        buy_order = executedBuyOrders[i];
        buy_order = &trackerBuy.get_root()->search(*buy_order, last);
        if (buy_order->m_payload.first == 0) {
            trackerBuy.get_root()->delete_element(*buy_order);
        } else {
            break;
        }
    }
 }

 
//adds a buy order
void Market::addBuyOrder(double price, int amount, string id,
                         long precedence)
{
    long time;
    time = precedence > 0 ? precedence : ++timer;
     Elem buy_order_elem = Elem();
    Elem * buy_order = &buy_order_elem;
     buy_order->m_key = price;
    buy_order->m_secondkey = -time;
     buy_order->m_payload.first = amount;
    buy_order->m_payload.second = id;
     int sell_first_index =
        static_cast < int >(executedBuyOrders.size());
    Elem * sell_order;
    BTree_Iterator sell_orders = getSellOrders();
    while ((sell_order = sell_orders.next()) != NULL 
            &&buy_order->m_payload.first > 0 
            &&buy_order->m_key >= sell_order->m_key ) {
        
            //cerr << " buy_order->price: " << buy_order->m_key << " sell_order->price: " << sell_order->m_key << " sell_order->amount: " <<sell_order->m_payload.first << endl;
            Elem * executed_sell_order = new Elem();
         executed_sell_order->m_key = last_deal;
        executed_sell_order->m_secondkey = sell_order->m_secondkey;
        executed_sell_order->m_payload.second =
            sell_order->m_payload.second;
         Elem * executed_buy_order = new Elem();
         executed_buy_order->m_key = last_deal;
        executed_buy_order->m_secondkey = buy_order->m_secondkey;
        executed_buy_order->m_payload.second =
            buy_order->m_payload.second;
         if (buy_order->m_payload.first < sell_order->m_payload.first) {
            executed_sell_order->m_payload.first =
                buy_order->m_payload.first;
            executed_buy_order->m_payload.first =
                buy_order->m_payload.first;
        } else if (buy_order->m_payload.first >
                    sell_order->m_payload.first) {
            executed_sell_order->m_payload.first =
                sell_order->m_payload.first;
            executed_buy_order->m_payload.first =
                sell_order->m_payload.first;
        } else {
            executed_sell_order->m_payload.first =
                sell_order->m_payload.first;
            executed_buy_order->m_payload.first =
                buy_order->m_payload.first;
        }
         setLastDeal(sell_order->m_key,
                       executed_buy_order->m_payload.first);
         
            //store difference of price(=first) in a structure for paying back sums paid in ahead
            Payback * payback = new Payback();
        payback->first =
            (buy_order->m_key -
             sell_order->m_key) * executed_buy_order->m_payload.first;
        payback->second = buy_order->m_payload.second;
        this->paybacks.push_back(payback);
         executedSellOrders.push_back(executed_sell_order);
        executedBuyOrders.push_back(executed_buy_order);
         sell_order->m_payload.first -=
            executed_sell_order->m_payload.first;
        buy_order->m_payload.first -= executed_buy_order->m_payload.first;
    }
     if (buy_order->m_payload.first == 0) {
        
            //don't insert
    } else {
        trackerBuy.get_root()->tree_insert(*buy_order);
    }
     for (int i = sell_first_index;
            i < static_cast < int >(executedSellOrders.size()); ++i) {
        Node * last;
        sell_order = executedSellOrders[i];
        sell_order = &trackerSell.get_root()->search(*sell_order, last);
        if (sell_order->m_payload.first == 0) {
            trackerSell.get_root()->delete_element(*sell_order);
        } else {
            break;
        }
    }
}

 
//gets the orders in ascending order
    BTree_Iterator Market::getSellOrders() constconst
{
    return BTree_Iterator(trackerSell.get_root(), true);
}

 
//gets the orders descending order
    BTree_Iterator Market::getBuyOrders() constconst
{
    return BTree_Iterator(trackerBuy.get_root(), false);
}

 
//gets the orders
    vector < Elem * >Market::getExecutedSellOrders()
{
    return executedSellOrders;
}

 
//gets the orders
    vector < Elem * >Market::getExecutedBuyOrders()
{
    return executedBuyOrders;
}

 
//gets the payback, if there is a deposit higher than the deal price
    vector < Payback * >Market::getPaybacks()
{
    return paybacks;
}

 
//reset the executed sell/buy order vectors and elements
void Market::resetExecutedOrders()
{
    for (int i = 0; i < static_cast < int >(executedBuyOrders.size());
          ++i) {
        Elem * buy_order = executedBuyOrders[i];
        delete buy_order;
    } executedBuyOrders.clear();
     for (int i = 0; i < static_cast < int >(executedSellOrders.size());
            ++i) {
        Elem * sell_order = executedSellOrders[i];
        delete sell_order;
    } executedSellOrders.clear();
     for (int i = 0; i < static_cast < int >(paybacks.size()); ++i) {
        Payback * payback = paybacks[i];
        delete payback;
    } paybacks.clear();
}  

//dump the orders
void Market::dump_summary()
{
    cerr << "Last deal price:" << last_deal << " ";
    cerr << "[" << lowest_price << "," << avg_value_of_trades() << "," <<
        highest_price << "]" << endl;
}  

//dump the orders
void Market::dump()
{
    Elem * current;
    cerr << "Sell orders:" << endl;
    BTree_Iterator iters = getSellOrders();
    while ((current = iters.next()) != NULL) {
        cerr << "key=" << current->m_key << " second key=" << current->
            m_secondkey << " amount=" << current->m_payload.
            first << " bidder=" << current->m_payload.second << " ";
        iters.dump();
    }
    cerr << "Buy orders:" << endl;
    BTree_Iterator iterb = getBuyOrders();
    while ((current = iterb.prev()) != NULL) {
        cerr << "key=" << current->m_key << " second key=" << current->
            m_secondkey << " amount=" << current->m_payload.
            first << " bidder=" << current->m_payload.second << " ";
        iterb.dump();
    }
    cerr << "Decay rate:" << this->decayrate << endl;
}

 
//dump the executed sell/buy order vectors and elements
void Market::dumpExecutedOrders()
{
    Elem * current;
    cerr << "market ====================" << endl;
    cerr << "executed buy orders:" << endl;
    for (int i = 0; i < static_cast < int >(executedBuyOrders.size());
          ++i) {
        current = executedBuyOrders[i];
        cerr << "price=" << current->m_key << " time=" << -current->
            m_secondkey << " amount=" << current->m_payload.
            first << " bidder=" << current->m_payload.
            second << " " << endl;
    }  cerr << "executed sell orders:" << endl;
    for (int i = 0; i < static_cast < int >(executedSellOrders.size());
          ++i) {
        current = executedSellOrders[i];
        cerr << "price=" << current->m_key << " time=" << current->
            m_secondkey << " amount=" << current->m_payload.
            first << " bidder=" << current->m_payload.
            second << " " << endl;
    } cerr << endl;
}  

//get market price and accumulated cost of a buy order of count n
double Market::max_market_price_when_buying_n(int n, double &accumulated)
{
    double max_market_price = 0.0;
    accumulated = 0.0;
    Elem * sell_order;
    BTree_Iterator sell_orders = getSellOrders();
    while ((sell_order = sell_orders.next()) != NULL  &&n > 0 ) {
        if (n > sell_order->m_payload.first) {
            accumulated +=
                sell_order->m_payload.first * sell_order->m_key;
        } else {
            accumulated += n * sell_order->m_key;
        }
        max_market_price = sell_order->m_key;
        n -= sell_order->m_payload.first;
    }
    return max_market_price;
}

 
//get market price and accumulated cost of a sell order of count n
double Market::min_market_price_when_selling_n(int n, double &accumulated)
{
    double min_market_price = std::numeric_limits < float >::max();    //using float, because cerr cannot display std::numeric_limits<double>::max
    accumulated = 0.0;
    Elem * buy_order;
    BTree_Iterator buy_orders = getBuyOrders();
    while ((buy_order = buy_orders.prev()) != NULL  &&n > 0 ) {
         if (n > buy_order->m_payload.first) {
            accumulated += buy_order->m_payload.first * buy_order->m_key;
        } else {
            accumulated += n * buy_order->m_key;
        }
        min_market_price = buy_order->m_key;
        n -= buy_order->m_payload.first;
    }
    return min_market_price;
}

   
//last deal price
double Market::last_deal_price()
{
    return last_deal;
}

 
//highest_buy_offer
double Market::highest_buy_offer()
{
    double amoneyres;
    double marketprice = min_market_price_when_selling_n(1, amoneyres);
    if (marketprice == 0.0
         || marketprice >= std::numeric_limits < float >::max()) {
        marketprice = last_deal;
    }
    return marketprice;
}

 
//lowest_sell_offer
double Market::lowest_sell_offer()
{
    double amoneyneed;
    double marketprice = max_market_price_when_buying_n(1, amoneyneed);
    if (marketprice == 0.0
         || marketprice >= std::numeric_limits < float >::max()) {
        marketprice = last_deal;
    }
    return marketprice;
}

 
//set a decay rate of goods sold on the market.
//0.0<=decay<=1.0 the amount of goods is multiplied by the decay rate
//this is meant for tracking limited resources like population and lands, not for general use
void Market::setDecayRate(double decayrate)
{
    this->decayrate = decayrate;
}  

//a time tick (which triggers decay)
void Market::tick()
{
    if (this->decayrate < 1.0) {
        vector < Elem * >remove_orders;
        Elem * sell_order;
        BTree_Iterator sell_orders = getSellOrders();
        while ((sell_order = sell_orders.next()) != NULL) {
            sell_order->m_payload.first =
                (int) floor(sell_order->m_payload.first * this->decayrate);
            if (sell_order->m_payload.first <= 0) {
                remove_orders.push_back(sell_order);
            }
        }
         
            //remove
            for (vector < Elem * >::const_iterator ritr =
                 remove_orders.begin(); ritr != remove_orders.end();
                 ++ritr) {
            trackerBuy.get_root()->delete_element(**ritr);
        }
    }
}

 
//destructor
    Market::~Market()
{
    resetExecutedOrders();
}

 
//#include <sstream>
#include <cstdio>
const char *toCString(double d) 
{
    
        /*
           std::ostringstream s ;
           s.precision( precision ) ;
           s << d ;
           return s.str() ;
         */ 
#define BUF_SIZE 99
    static char buffer[BUF_SIZE];
    sprintf(buffer, "%f", d);
    return buffer;
}

 const char *toCString(long l) 
{
    
        /*
           std::ostringstream s ;
           s << l ;
           return s.str() ;
         */ 
#define BUF_SIZE 99
    static char buffer[BUF_SIZE];
    sprintf(buffer, "%ld", l);
    return buffer;
}

 const char *toCString(int i) 
{
    
        /*
           std::ostringstream s ;
           s << l ;
           return s.str() ;
         */ 
#define BUF_SIZE 99
    static char buffer[BUF_SIZE];
    sprintf(buffer, "%d", i);
    return buffer;
}

 double doubleFromCString(const char *cstr, double defo)
{
    double d = defo;
    sscanf(cstr, "%lf", &d);
    return d;
}

 long longFromCString(const char *cstr, long defo)
{
    long l = defo;
    sscanf(cstr, "%ld", &l);
    return l;
}

int intFromCString(const char *cstr, int defo)
{
    int i = defo;
    sscanf(cstr, "%d", &i);
    return i;
}

 void Market::addElement(scew_element * root) const const
{
    scew_element * element = NULL;
    scew_element * sub_element = NULL;
    scew_element * sub_sub_element = NULL;
     element = scew_element_add(root, "timer");
    scew_element_set_contents(element, toCString(timer));
     element = scew_element_add(root, "last_deal");
    scew_element_set_contents(element, toCString(last_deal));
     element = scew_element_add(root, "lowest_price");
    scew_element_set_contents(element, toCString(lowest_price));
     element = scew_element_add(root, "highest_price");
    scew_element_set_contents(element, toCString(highest_price));
     element = scew_element_add(root, "number_of_trades");
    scew_element_set_contents(element, toCString(lowest_price));
     element = scew_element_add(root, "value_of_trades");
    scew_element_set_contents(element, toCString(highest_price));
     Elem * current;
     element = scew_element_add(root, "sell_orders");
    BTree_Iterator iters = getSellOrders();
    while ((current = iters.next()) != NULL) {
        sub_element = scew_element_add(element, "sell_order");
        scew_element_add_attr_pair(sub_element, "price",
                                    toCString(current->m_key));
        scew_element_add_attr_pair(sub_element, "priority",
                                    toCString(current->m_secondkey));
        sub_sub_element = scew_element_add(sub_element, "amount");
        scew_element_set_contents(sub_sub_element,
                                   toCString(current->m_payload.first));
        sub_sub_element = scew_element_add(sub_element, "bidder");
        scew_element_set_contents(sub_sub_element,
                                   current->m_payload.second.c_str());
    }
     element = scew_element_add(root, "buy_orders");
    BTree_Iterator iterb = getBuyOrders();
    while ((current = iterb.prev()) != NULL) {
        sub_element = scew_element_add(element, "buy_order");
        scew_element_add_attr_pair(sub_element, "price",
                                    toCString(current->m_key));
        scew_element_add_attr_pair(sub_element, "priority",
                                    toCString(-current->m_secondkey));
        sub_sub_element = scew_element_add(sub_element, "amount");
        scew_element_set_contents(sub_sub_element,
                                   toCString(current->m_payload.first));
        sub_sub_element = scew_element_add(sub_element, "bidder");
        scew_element_set_contents(sub_sub_element,
                                   current->m_payload.second.c_str());
    }
     element = scew_element_add(root, "decayrate");
    scew_element_set_contents(element, toCString(this->decayrate));
     element = scew_element_add(root, "timer");
    scew_element_set_contents(element, toCString(this->timer));
}

 Market * Market::marketFromElement(scew_element * root)
{
    Market * market = new Market();
     scew_element * element = NULL;
    scew_element * sub_element = NULL;
    
//   scew_element *sub_sub_element = NULL;
    XML_Char const *contents = NULL;
    
//    scew_attribute*attribute;
        
        //FIXME: this might cause the timer to wrap eventually
        element = scew_element_by_name(root, "timer");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->timer = longFromCString(contents, market->timer);
        }
    }
     element = scew_element_by_name(root, "last_deal");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->last_deal =
                doubleFromCString(contents, market->last_deal);
        }
    }
     element = scew_element_by_name(root, "lowest_price");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->lowest_price =
                doubleFromCString(contents, market->lowest_price);
        }
    }
     element = scew_element_by_name(root, "highest_price");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->highest_price =
                doubleFromCString(contents, market->highest_price);
        }
    }
     element = scew_element_by_name(root, "number_of_trades");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->number_of_trades =
                doubleFromCString(contents, market->number_of_trades);
        }
    }
     element = scew_element_by_name(root, "value_of_trades");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->value_of_trades =
                doubleFromCString(contents, market->value_of_trades);
        }
    }
     element = scew_element_by_name(root, "sell_orders");
    if (NULL != element) {
        for (scew_element * sub_element =
              scew_element_next(element, NULL); NULL != sub_element;
              sub_element = scew_element_next(element, sub_element)) {
            if (0 == strcmp(scew_element_name(sub_element), "sell_order")) {
                Elem * pelem = elemFrom(sub_element);
                if (NULL != pelem) {
                    
//pelem->dump();
                        //market->trackerSell.get_root()->tree_insert(*pelem);
                        market->addSellOrder(pelem->m_key,
                                             pelem->m_payload.first,
                                             pelem->m_payload.second,
                                             pelem->m_secondkey);
                    delete pelem;
                }
            }
        }
    }
     element = scew_element_by_name(root, "buy_orders");
    if (NULL != element) {
        for (scew_element * sub_element =
              scew_element_next(element, NULL); NULL != sub_element;
              sub_element = scew_element_next(element, sub_element)) {
            if (0 == strcmp(scew_element_name(sub_element), "buy_order")) {
                Elem * pelem = elemFrom(sub_element);
                if (NULL != pelem) {
                    
                        //market->trackerBuy.get_root()->tree_insert(*pelem);
                        market->addBuyOrder(pelem->m_key,
                                            pelem->m_payload.first,
                                            pelem->m_payload.second,
                                            pelem->m_secondkey);
                    
                        //TODO delete pelem;
                }
            }
        }
    }
     element = scew_element_by_name(root, "decayrate");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->decayrate =
                doubleFromCString(contents, market->decayrate);
        }
    }
     element = scew_element_by_name(root, "timer");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            market->timer = intFromCString(contents, market->timer);
        }
    }
     return market;
}

 static Elem *elemFrom(scew_element * sub_element)
{
    scew_element * sub_sub_element = NULL;
    XML_Char const *contents = NULL;
     double price = 0.0;
    long priority = 0;
    int amount = 0;
    string bidder = "None";
    for (scew_attribute * attribute =
          scew_attribute_next(sub_element, NULL); NULL != attribute;
          attribute = scew_attribute_next(sub_element, attribute)) {
        if (0 == strcmp(scew_attribute_name(attribute), "price")) {
            price = doubleFromCString(scew_attribute_value(attribute));
        } else if (0 ==
                    strcmp(scew_attribute_name(attribute), "priority")) {
            priority = longFromCString(scew_attribute_value(attribute));
        }
    }
    for (scew_element * sub_sub_element =
          scew_element_next(sub_element, NULL); NULL != sub_sub_element;
          sub_sub_element =
          scew_element_next(sub_element, sub_sub_element)) {
        if (0 == strcmp(scew_element_name(sub_sub_element), "amount")) {
            amount =
                intFromCString(scew_element_contents(sub_sub_element));
        } else if (0 ==
                    strcmp(scew_element_name(sub_sub_element), "bidder")) {
            bidder = string(scew_element_contents(sub_sub_element));
        }
    }
    if (amount > 0 && price > 0.0) {
        Elem * order = new Elem();
         order->m_key = price;
        order->m_secondkey = priority;
         order->m_payload.first = amount;
        order->m_payload.second = bidder;
         return order;
    } else {
        return NULL;
    }
}


