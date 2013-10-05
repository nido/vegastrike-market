#include <algorithm>
#include <vector>
#include <iostream>
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

void Base::addCargo(Cargo* cargo)
{
	this->cargoStore.addCargo(cargo);
}

void Base::delCargo(Cargo* cargo)
{
	this->cargoStore.delCargo(cargo);
}

Cargo* Base::getCargo(){
	return &this->cargoStore;
}

void Base::Process()
{
//	std::cout<<"Processing base "<<this<<" ";
	for (std::vector<Factory>::iterator iter = this->factories.begin();
		iter != this->factories.end();
		++iter
	){
//		std::cout<<".";
		iter->Produce(&this->cargoStore);
	}
//	std::cout<<std::endl;
}
