/*
 */

#include <limits>
#include <string>
#include <vector>

#include "Factory.hpp"
#include "Cargo.hpp"

#include <assert.h>
#include <math.h>


Factory::Factory() :
	options(std::vector<ProductionOption>()),
	productionPlan(this->options.end())
{
}

Factory::~Factory()
{
}

/** Determines whether the factory is able to produce (at all). */
bool Factory::canProduce(const Cargo* cargoStore) const {
	if (this->options.empty()){
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

void Factory::addProductionOption(ProductionOption* option)
{
	this->options.push_back(*option);
	// set the first production option available as default
	if (this->options.size() == 1){
		this->setProductionOption(*option);
	}
}

void Factory::setProductionOption(const ProductionOption option)
{
	for (std::vector<ProductionOption>::iterator i = this->options.begin();
		i != this->options.end();
		++i)
	{
		if(*i == option)
		{
			this->productionPlan = i;
		}
	}
}

bool Factory::operator==(const Factory &that) const
{
	return this->options == that.options;
}
