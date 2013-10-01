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

std::vector<Factory> Base::getFactories()
{
	return this->factories;
}

void Base::addCargo(Cargo cargo)
{
	this->cargoStore.addCargo(cargo);
}

void Base::delCargo(Cargo cargo)
{
	this->cargoStore.delCargo(cargo);
}

Cargo* Base::getCargo(){
	return &this->cargoStore;
}

void Base::Process()
{
	for (std::vector<Factory>::iterator iter = this->factories.begin();
		iter != this->factories.end();
		iter++
	){
		iter->Produce(&this->cargoStore);
	}
}
