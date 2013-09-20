#include <vector>

#include "images.h"
#include "ProductionOption.hpp"

#define TURNS 200000

int main(void){
	std::vector<Cargo> *stuff1 = new std::vector<Cargo>();
	std::vector<Cargo> *stuff2 = new std::vector<Cargo>();
	std::vector<Cargo> *stuff3 = new std::vector<Cargo>();

	stuff1->push_back(Cargo("input", "", 0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff2->push_back(Cargo("output", "",0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff3->push_back(Cargo("input", "",0.0, TURNS, 0.0, 0.0, 0.0, 0.0));

	ProductionOption* o = new ProductionOption(*stuff1, *stuff2);

	for(int i=0; i<TURNS; i++) {
		o->Produce(stuff3);
	}

	delete stuff1;
	delete stuff2;
	delete stuff3;
	delete o;

	return 0;
}
