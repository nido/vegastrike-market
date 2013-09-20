#include <vector>
#include <assert.h>

//TODO: make this vegastrike's version. This file contains the Cargo
//      class; and use of vegacargo in the economy would make it a lot
//      easier to integrate the two at a later date. Still, that leaves
//      us with requiring a vegastrike_dir variable of sorts and getting
//      people to check out all of vegastrike for this, or an altered
//      version for here for the moment to make it work with sortof
//      vegacargo
#include "../images.h"
#include "Factory.hpp"
#include "ProductionOption.hpp"

#define TURNS 300000

int main(void){
	std::vector<Cargo> stuff1 = std::vector<Cargo>();
	std::vector<Cargo> stuff2 = std::vector<Cargo>();
	std::vector<Cargo> *stuff3 = new std::vector<Cargo>();
	std::vector<Cargo> stuff4 = std::vector<Cargo>();
	std::vector<Cargo> stuff5 = std::vector<Cargo>();
	std::vector<ProductionOption> options = std::vector<ProductionOption>();

	stuff1.push_back(Cargo("input", "", 0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff2.push_back(Cargo("output", "",0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff3->push_back(Cargo("input", "",0.0, TURNS, 0.0, 0.0, 0.0, 0.0));
	stuff4.push_back(Cargo("input", "", 0.0, 100, 0.0, 0.0, 0.0, 0.0));
	stuff5.push_back(Cargo("output", "",0.0, 100, 0.0, 0.0, 0.0, 0.0));

	ProductionOption o1 = ProductionOption(stuff1, stuff2);
	ProductionOption o2 = ProductionOption(stuff4, stuff5);
	options.push_back(o1);
	options.push_back(o2);

	Factory *f = new Factory(options);

	for(int i=1; i <= TURNS; i++) {
		f->Produce(stuff3);
		Cargo* in = findCargo("input", stuff3);
		Cargo* out = findCargo("output", stuff3);
		assert(in->quantity == (TURNS - i));
		assert(out->quantity == i);
	}

	delete stuff3;
	delete f;

	return 0;
}
