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
	if (this->options.size() == 0){
		return false;
	}
	if (this->productionPlan->canProduce(cargoStore)){
		return true;
	}
	return false;
}

void Factory::Produce(Cargo* cargoStore){
	if (! this->canProduce(cargoStore)){
		return;
	}
	this->productionPlan->Produce(cargoStore);
}

void Factory::addProductionOption(ProductionOption option)
{
	this->options.push_back(option);
	// set the first production option available as default
	if (this->options.size() == 1){
		this->setProductionOption(option);
	}
}

void Factory::setProductionOption(ProductionOption option)
{
	for (std::vector<ProductionOption>::iterator i = this->options.begin();
		i != this->options.end();
		i++)
	{
		if(*i == option)
		{
			this->productionPlan = i;
		}
	}
}
