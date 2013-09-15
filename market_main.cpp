/*
This is free software.
License: GNU GPL 2 or later.
Copyright 2009: peter.schaefer@gmail.com

Market Main current version: 19th of january 2009 by peter.schaefer@gmail.com
*/

/*
compile with:
g++ -Wall market_main.cpp -o market.exe
Run with:
market.exe
*/

#include "node.hpp"

#include "btree_iterator.hpp"

#include "Market.hpp"


// for the high-resolution timer
#ifdef _WIN32
#include <windows.h>
#endif



int main(int argc, char* argv[])

{

// the main function is just some code to test the btree and the market.



#ifdef _WIN32
    __int64 frequency, start, end, total;

    QueryPerformanceFrequency( (LARGE_INTEGER *)&frequency );

    QueryPerformanceCounter( (LARGE_INTEGER *)&start );
#endif

    Elem elem;



    RootTracker tracker;  // maintains a pointer to the current root of the b-tree

    Node* root_ptr = new Node(tracker);

    tracker.set_root (null_ptr, root_ptr);

    Elem * current;

    tracker.get_root()->dump();

    cerr<< "empty tree dumped" << endl;

    //test traversing an empty tree
    BTree_Iterator itere(tracker.get_root(),true);
    while( (current=itere.next())!= NULL ){
    	cerr << "key=" << current->m_key << " second key=" << current->m_secondkey << " amount=" << current->m_payload.first << " bidder=" << current->m_payload.second << " ";
	itere.dump();
    }

    cerr << "empty tree traversed" << endl;

    //run a test
    const int n = 1000;
    for (int i=0; i<n; i++) {
	    //An element contains: +-price,+-time,<+-amount,bidderid>
	    elem.m_key = 1.0*i;
	    elem.m_secondkey = i;

	    elem.m_payload.first = (int)i;
	    elem.m_payload.second = "some bidder id";

	    tracker.get_root()->tree_insert(elem);
    }

    cerr << "tree built" << endl;

    /*
    tracker.get_root()->dump();

    cerr<< "tree dumped" << endl;
    */

    cerr << "tree traverse forwards =================" << endl;
    int count = 0;
    BTree_Iterator iter(tracker.get_root(),true);
    while( (current=iter.next())!= NULL ){
    	cerr << (count!=current->m_key?"!":" ") << "key=" << current->m_key << " second key=" << current->m_secondkey << " amount=" << current->m_payload.first << " bidder=" << current->m_payload.second << " ";
	iter.dump();
	count += 1;
    }

    cerr << "tree traversed, " << count << " elements" << endl;

    cerr << "tree traverse backwards =================" << endl;
    int countb = 0;
    BTree_Iterator iterb(tracker.get_root(),false);
    while( (current=iterb.prev())!= NULL ){
    	cerr << ((n-1-countb)!=current->m_key?"!":" ")  << "key=" << current->m_key << " second key=" << current->m_secondkey << " amount=" << current->m_payload.first << " bidder=" << current->m_payload.second << " ";
	iterb.dump();
	countb += 1;
    }

    cerr << "tree traversed backwards, " << countb << " elements" << endl;

    /*
    cerr << "after finishing" << endl;

    tracker.get_root()->dump();
     */

    cerr << "testing market" << endl;

    Market market;

    cerr<<"Market dump(empty):"<<endl;
    market.dump();

    for (int i=1; i<=100; i++) {
	    if( i<=50 ){
		market.addBuyOrder(i*0.01,100-i,"Buyer 1");
	    }else{
		market.addSellOrder(i*0.01,i,"Seller 1");
	    }
    }

    for (int i=1; i<=100; i++) {
	    if( i<=50 ){
		market.addBuyOrder(i*0.01,100-i,"Buyer 2");
	    }else{
		market.addSellOrder(i*0.01,i,"Seller 2");
	    }
    }

    cerr<<"Market dump:"<<endl;
    market.dump();

    double accumulated;
    double market_price;

    cerr << "buy order===" << endl;
    market_price= market.max_market_price_when_buying_n(88,accumulated);
    cerr << "max market price buying 88: " << market_price << " total: "  << accumulated << endl;

    market.addBuyOrder(0.80,88,"Buyer A");
    market.dumpExecutedOrders();

    cerr << "emptying===============" << endl;
    market.resetExecutedOrders();
    market.dumpExecutedOrders();

    cerr << "sell order===" << endl;
    market_price= market.min_market_price_when_selling_n(222,accumulated);
    cerr << "min market price selling 222: " << market_price << " total: "  << accumulated << endl;

    market.addSellOrder(0.20,222,"Seller A");
    market.dumpExecutedOrders();

    cerr << "emptying===============" << endl;
    market.resetExecutedOrders();
    market.dumpExecutedOrders();

    cerr << "3nd dump, sell order===" << endl;
    market.addSellOrder(0.20,222,"Seller A");
    market.dumpExecutedOrders();

#ifdef _WIN32
    QueryPerformanceCounter ( (LARGE_INTEGER *)&end);

    total = (end-start)/(frequency/1000);

    cerr << "total millisec for all operations: " << (int)total << endl;
#endif
    //getchar();

    return 0;

}





