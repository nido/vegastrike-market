/*
 */

#include <limits>

#include <string>

#include <vector>

#include "Factory.hpp"
#include "Cargo.hpp"

#include <assert.h>
#include <math.h>


Factory::Factory(){
}

Factory::~Factory(){
}

/** Determines whether the factory is able to produce (at all). */
bool Factory::canProduce(Cargo* cargoStore){
	for(std::vector<ProductionOption>::iterator option = this->options.begin();
		option != this->options.end();
		option++)
	{
		if (option->canProduce(cargoStore)){
			return true;
		}
	}
	return false;
}

void Factory::Produce(Cargo* cargoStore){
	if (! this->canProduce(cargoStore)){
		return;
	}
	for(std::vector<ProductionOption>::iterator option = this->options.begin();
		option != this->options.end();
		option++)
	{
		if (option->canProduce(cargoStore)){
			option->Produce(cargoStore);
			// at most one option is used.
			return;
		}
	}
}

void Factory::addProductionOption(ProductionOption option){
	this->options.push_back(option);
}
