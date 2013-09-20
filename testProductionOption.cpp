#include <vector>
#include <assert.h>

#include "images.h"
#include "ProductionOption.hpp"

#define TURNS 200000

int main(void){
	std::vector<Cargo> stuff1 = std::vector<Cargo>();
	std::vector<Cargo> stuff2 = std::vector<Cargo>();
	std::vector<Cargo> *stuff3 = new std::vector<Cargo>();

	stuff1.push_back(Cargo("input", "", 0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff2.push_back(Cargo("output", "",0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff3->push_back(Cargo("input", "",0.0, TURNS, 0.0, 0.0, 0.0, 0.0));

	ProductionOption* o = new ProductionOption(stuff1, stuff2);


	for(int i=1; i <= TURNS; i++) {
		o->Produce(stuff3);
	Cargo* in = findCargo("input", stuff3);
	Cargo* out = findCargo("output", stuff3);
		assert(in->quantity == (TURNS - i));
		assert(out->quantity == i);
	}

	delete stuff3;
	delete o;

	return 0;
}
