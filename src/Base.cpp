#include <algorithm>
#include <vector>

#include "Base.hpp"

Base::Base() : 
	factories(std::vector<Factory>()), cargoStore(Cargo())
{
}

Base::~Base()
{
}

void Base::addFactory(Factory factory)
{
	this->factories.push_back(factory);
}

void Base::delFactory(Factory factory)
{
	std::vector<Factory>::iterator iter = std::find(this->factories.begin(),
		this->factories.end(), factory);
	this->factories.erase(iter);
}

void Base::addCargo(Cargo cargo)
{
	this->cargoStore.addCargo(cargo);
}

void Base::delCargo(Cargo cargo)
{
	this->cargoStore.delCargo(cargo);
}

