/*
This is free software.
License: GNU GPL 2 or later.
Copyright 2009: peter.schaefer@gmail.com

XML Factory Main current version: 19th of february 2009 by peter.schaefer@gmail.com
*/
#ifdef _USE_VLD
#include <vld.h>
#endif

#define USE_SCEW 1

#include "node.hpp"

#include "btree_iterator.hpp"

#include "Market.hpp"

#include "Factory.hpp"

#include "xmleconomy.hpp"

// for the high-resolution timer
//#define _WIN32
#ifdef _WIN32
#include <windows.h>
#endif

//caveat: function uses always the same buffer, so you can't use two strings at the same time
const char *getName(const char *format,int i){
    static char buffer[99];
    sprintf(buffer,format,i);
    return buffer;
}

int main(int argc, char* argv[])

{
    int turns = 20;
    const char* startfile= NULL;
    if(argc>1){
        sscanf(argv[1],"%d",&turns);
    }
    if(argc>2){
        startfile= argv[2];
    }
#ifdef _WIN32
// the main function is just some code to test the factories.

    __int64 frequency, start, end, total;

    QueryPerformanceFrequency( (LARGE_INTEGER *)&frequency );

    QueryPerformanceCounter( (LARGE_INTEGER *)&start );
#endif

//begin test

	XMLEconomy *economy;
    if(NULL != startfile){
        economy= XMLEconomy::readFromFile(startfile);
        if(NULL== economy){
            cerr<<"Error reading file "<<startfile<<endl;
            return 1;
        }
    }else{
        //construct economy programmatically
        economy= new XMLEconomy();
        economy->setCurrency("euro");
        economy->setPopulace("population");
        double standard_profitrate= 0.02;

        //==========================
            Factory* populace= new Factory(1000000,economy,0.001,"population");
        //==========================
        Products populace_outputs;
        Products populace_inputs;
        populace_outputs.push_back(Stack("population",10.0));
        Products populace_costofanother;
        populace_costofanother.push_back(Stack("lands",1.0));
        ProductionOption poPopulace(populace_outputs,populace_inputs, 1000.0, populace_costofanother);
        populace->addProductionOption(poPopulace);
        //==========================
        economy->addFactory(populace);

        //==========================
            Factory* lands= new Factory(1000000,economy,0.001,"lands");
        //==========================
        Products lands_outputs;
        Products lands_inputs;
        lands_outputs.push_back(Stack("lands",10.0));
        lands_inputs.push_back(Stack("workforce",1.0));
        Products lands_costofanother;
        lands_costofanother.push_back(Stack("unused lands",1.0));
        ProductionOption poLands(lands_outputs,lands_inputs, 50.0, lands_costofanother);
        lands->addProductionOption(poLands);
        //==========================
        economy->addFactory(lands);
        economy->setDecayRate("lands", 0.9);

        //==========================
        Factory* brewery = new Factory(1000000,economy,standard_profitrate,"brewery");
        //==========================
        Products beer_outputs;
        Products beer_inputs;
        beer_outputs.push_back(Stack("beer",10.0));
        beer_inputs.push_back(Stack("hop",2.0));
        beer_inputs.push_back(Stack("barrel",1.0));
        Products beer_costofanother;
        beer_costofanother.push_back(Stack("machinery",5.0));
        beer_costofanother.push_back(Stack("pipes",5.0));
        ProductionOption beer(beer_outputs, beer_inputs, 10.0, beer_costofanother);
        brewery->addProductionOption(beer);
        //==========================
        Products wine_outputs;
        Products wine_inputs;
        wine_outputs.push_back(Stack("wine",10.0));
        wine_inputs.push_back(Stack("grapes",3.0));
        wine_inputs.push_back(Stack("bottles",1.0));
        Products wine_costofanother;
        wine_costofanother.push_back(Stack("machinery",5.0));
        wine_costofanother.push_back(Stack("pipes",5.0));
        ProductionOption wine(wine_outputs, wine_inputs, 10.0, wine_costofanother);
        brewery->addProductionOption(wine);
        //==========================
        economy->addFactory(brewery);

        //==========================
            Factory* farm = new Factory(1000000,economy,standard_profitrate,"farm");
        //==========================
        Products hop_outputs;
        Products hop_inputs;
        hop_outputs.push_back(Stack("hop",10.0));
        hop_inputs.push_back(Stack("lands",2.0));
        hop_inputs.push_back(Stack("workforce",1.0));
        Products hop_costofanother;
        hop_costofanother.push_back(Stack("tractors",1.0));
        hop_costofanother.push_back(Stack("seeds",1.0));
        ProductionOption hop(hop_outputs,hop_inputs, 10.0, hop_costofanother);
        farm->addProductionOption(hop);
        //==========================
        Products seeds_outputs;
        Products seeds_inputs;
        seeds_outputs.push_back(Stack("seeds",10.0));
        seeds_inputs.push_back(Stack("lands",4.0));
        seeds_inputs.push_back(Stack("workforce",2.0));
        Products seeds_costofanother;
        seeds_costofanother.push_back(Stack("tractors",1.0));
        ProductionOption seeds(seeds_outputs, seeds_inputs, 10.0, seeds_costofanother);
        farm->addProductionOption(seeds);
        //==========================
        Products grapes_outputs;
        Products grapes_inputs;
        grapes_outputs.push_back(Stack("grapes",10.0));
        grapes_inputs.push_back(Stack("lands",3.0));
        grapes_inputs.push_back(Stack("workforce",5.0));
        Products grapes_costofanother;
        grapes_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption grapes(grapes_outputs, grapes_inputs, 10.0, grapes_costofanother);
        farm->addProductionOption(grapes);
        //==========================
        economy->addFactory(farm);

        //==========================
            Factory* factory= new Factory(1000000,economy,standard_profitrate,"factory");
        //==========================
        Products machinery_outputs;
        Products machinery_inputs;
        machinery_outputs.push_back(Stack("machinery",10.0));
        machinery_inputs.push_back(Stack("steel",5.0));
        machinery_inputs.push_back(Stack("workforce",1.0));
        Products machinery_costofanother;
        machinery_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption machinery(machinery_outputs,machinery_inputs, 10.0, machinery_costofanother);
        factory->addProductionOption(machinery);
        //==========================
        Products pipes_outputs;
        Products pipes_inputs;
        pipes_outputs.push_back(Stack("pipes",10.0));
        pipes_inputs.push_back(Stack("steel",5.0));
        pipes_inputs.push_back(Stack("workforce",1.0));
        Products pipes_costofanother;
        pipes_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption pipes(pipes_outputs,pipes_inputs, 1.0, pipes_costofanother);
        factory->addProductionOption(pipes);
        //==========================
        Products bottles_outputs;
        Products bottles_inputs;
        bottles_outputs.push_back(Stack("bottles",10.0));
        bottles_inputs.push_back(Stack("steel",3.0));
        bottles_inputs.push_back(Stack("workforce",3.0));
        Products bottles_costofanother;
        bottles_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption bottles(bottles_outputs,bottles_inputs, 100.0,bottles_costofanother);
        factory->addProductionOption(bottles);
        //==========================
        Products barrel_outputs;
        Products barrel_inputs;
        barrel_outputs.push_back(Stack("barrel",10.0));
        barrel_inputs.push_back(Stack("steel",2.0));
        barrel_inputs.push_back(Stack("workforce",2.0));
        Products barrel_costofanother;
        barrel_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption barrel(barrel_outputs, barrel_inputs, 100.0,barrel_costofanother);
        factory->addProductionOption(barrel);
        //==========================
        economy->addFactory(factory);

        //==========================
            Factory* assemblyline= new Factory(1000000,economy,standard_profitrate,"assembly line");
        //==========================
        Products tractors_outputs;
        Products tractors_inputs;
        tractors_outputs.push_back(Stack("tractors",1.0));
        tractors_inputs.push_back(Stack("steel",3.0));
        tractors_inputs.push_back(Stack("workforce",3.0));
        Products tractors_costofanother;
        tractors_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption tractors(tractors_outputs,tractors_inputs, 10.0, tractors_costofanother);
        assemblyline->addProductionOption(tractors);
        //==========================
        Products cars_outputs;
        Products cars_inputs;
        cars_outputs.push_back(Stack("cars",1.0));
        cars_inputs.push_back(Stack("steel",3.0));
        cars_inputs.push_back(Stack("workforce",3.0));
        Products cars_costofanother;
        cars_costofanother.push_back(Stack("workforce",3.0));
        ProductionOption cars(cars_outputs,cars_inputs, 10.0,cars_costofanother);
        assemblyline->addProductionOption(cars);
        //==========================
        economy->addFactory(assemblyline);

        //==========================
            Factory* workers= new Factory(1000000,economy,standard_profitrate,"workers");
        //==========================
        Products workforce_outputs;
        Products workforce_inputs;
        workforce_outputs.push_back(Stack("workforce",10.0));
        workforce_inputs.push_back(Stack("beer",1.0));
        Products workforce_costofanother;
        workforce_costofanother.push_back(Stack("population",1.0));
        ProductionOption workforce(workforce_outputs,workforce_inputs, 50.0, workforce_costofanother);
        workers->addProductionOption(workforce);
        //==========================
        economy->addFactory(workers);

        //==========================
            Factory* workers2= new Factory(1000000,economy,standard_profitrate,"workers2");
        //==========================
        Products workforce1_outputs;
        Products workforce1_inputs;
        workforce1_outputs.push_back(Stack("workforce",10.0));
        workforce1_inputs.push_back(Stack("wine",1.0));
        workforce1_inputs.push_back(Stack("grapes",1.0));
        Products workforce1_costofanother;
        workforce1_costofanother.push_back(Stack("population",1.0));
        ProductionOption workforce1(workforce1_outputs,workforce1_inputs, 50.0, workforce1_costofanother);
        workers2->addProductionOption(workforce1);
        //==========================
        Products workforce2_outputs;
        Products workforce2_inputs;
        workforce2_outputs.push_back(Stack("workforce",10.0));
        workforce2_inputs.push_back(Stack("cars",1.0));
        Products workforce2_costofanother;
        workforce2_costofanother.push_back(Stack("population",1.0));
        ProductionOption workforce2(workforce2_outputs,workforce2_inputs, 50.0, workforce2_costofanother);
        workers2->addProductionOption(workforce2);
        //==========================
        economy->addFactory(workers2);
        economy->setDecayRate("workforce", 0.9);


        //==========================
        Factory* mine= new Factory(1000000,economy,0.001,"iron mine");
        //==========================
        Products mine_outputs;
        Products mine_inputs;
        mine_outputs.push_back(Stack("steel",10.0));//9.50
        mine_inputs.push_back(Stack("workforce",2.0));//46.48
        Products mine_costofanother;
        mine_costofanother.push_back(Stack("tractors",1.0));
        ProductionOption poMine(mine_outputs,mine_inputs, 10.0, mine_costofanother);
        mine->addProductionOption(poMine);
        //==========================
        economy->addFactory(mine);

        Products consumption1;
        consumption1.push_back(Stack("beer",90.0));
        consumption1.push_back(Stack("wine",90.0));
        consumption1.push_back(Stack("grapes",50.0));
        consumption1.push_back(Stack("cars",5.0));
        Consumer *p1c= new Consumer(0.0, economy, consumption1, "the working class",standard_profitrate);
        economy->addConsumer(p1c);

        Products consumption2;
        consumption2.push_back(Stack("cars",10.0));
        consumption2.push_back(Stack("grapes",25.0));
        consumption2.push_back(Stack("wine",45.0));
        consumption2.push_back(Stack("beer",45.0));
        Consumer *p2c= new Consumer(0.0, economy, consumption2, "the middle class",standard_profitrate);
        economy->addConsumer(p2c);

        economy->addConsumerMap("population","the working class");
        economy->addConsumerMap("lands","the middle class");
        economy->addConsumerMap("brewery","the middle class");
        economy->addConsumerMap("farm","the working class");
        economy->addConsumerMap("factory","the working class");
        economy->addConsumerMap("assembly line","the middle class");
        economy->addConsumerMap("workers","the working class");
        economy->addConsumerMap("workers2","the middle class");
        economy->addConsumerMap("iron mine","the working class");

        string what;
        what="barrel";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="beer";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="population";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="lands";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="workforce";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="unused lands";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="wine";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="hop";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="machinery";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="pipes";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="grapes";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="bottles";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="hop";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="tractors";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,1000.0, 10,1300.0, 20, 9);
        economy->placeBuyOrders(what,700.0, 20,1000.0,10, 9);

        what="seeds";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="steel";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,100.0, 100,130.0, 200, 9);
        economy->placeBuyOrders(what,70.0, 200,100.0,100, 9);

        what="cars";
        cerr<<"placing orders: "<<what<<endl;
        economy->placeSellOrders(what,1000.0, 10,1300.0, 20, 9);
        economy->placeBuyOrders(what,700.0, 20,1000.0,10, 9);

        economy->executeTransactions();
    }

    economy->writeToFile("economy_start.xml");
    XMLEconomy *xe2= XMLEconomy::readFromFile("economy_start.xml");
    xe2->writeToFile("economy_start_2.xml");

    int i;

    //pre-heat economy
	for(i=0;3*i<turns;++i){
		economy->tick();
        xe2->tick();
        if(turns<=20){
            //study details
            economy->writeToFile(getName("economy_turn_%d.xml",i));
        }
	}

    economy->writeToFile("economy_middle.xml");
    XMLEconomy *xe3= XMLEconomy::readFromFile("economy_middle.xml");
    xe3->writeToFile("economy_middle_2.xml");

    economy->reset_statistics();
    xe2->reset_statistics();

	for(i=0;i<turns;++i){
		economy->tick();
        xe2->tick();
        if(turns<=20){
            //study details
            economy->writeToFile(getName("economy_turn_%d.xml",i));
        }
	}
    economy->writeToFile("economy_end.xml");
    xe2->writeToFile("economy_end_2.xml");

    economy->dump();
	cerr<<turns;
//end test

#ifdef _WIN32
    QueryPerformanceCounter ( (LARGE_INTEGER *)&end);

    total = (end-start)/(frequency/1000);

    cerr << "total millisec for all operations: " << (int)total << endl;

#endif

    //getchar();

    return 0;

}




