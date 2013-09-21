/*
 */

#include <limits>

#include <string>

#include <vector>

#include "Factory.hpp"

#include <assert.h>
#include <math.h>


/** TODO: Make sure it has its own stores of Cargo to draw from */
Factory::Factory(std::vector<ProductionOption> options){
	// TODO: sort according to output size.
	this->options = options;
}

Factory::~Factory(){
}

/** Determines whether the factory is able to produce (at all). */
bool Factory::CanProduce(std::vector<Cargo>* cargoStore){
	for(size_t i = 0; i < this->options.size(); i++){
		if (options[i].CanProduce(cargoStore)){
			return true;
		}
	}
	return false;
}

void Factory::Produce(std::vector<Cargo>* cargoStore){
	if (! this->CanProduce(cargoStore)){
		return;
	}
	for(size_t i = 0; i < this->options.size(); i++){
		// TODO: we assume an order here which may not exist.
		if (options[i].CanProduce(cargoStore)){
			options[i].Produce(cargoStore);
			// at most one option is used.
			return;
		}
	}
}