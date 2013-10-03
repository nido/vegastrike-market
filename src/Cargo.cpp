#include <algorithm>
#include <iostream>

#include <assert.h>
#include <stdbool.h>

#include "Cargo.hpp"

Cargo::Cargo()
{
}

void Cargo::addCargo(CargoType type, unsigned int quantity)
{
	assert( quantity != 0);
	Cargo::iterator current = this->cargo.find(type);
	if (current != this->end()){
		quantity += current->second;
	}
	this->cargo[type] = quantity;
}

void Cargo::addCargo(Cargo newCargo)
{
	Cargo::iterator newStock;
	for (newStock = newCargo.begin();
		newStock != newCargo.end();
		++newStock)
	{
		this->addCargo(newStock->first, newStock->second);
	}
}

unsigned int Cargo::getCount(CargoType type)
{
	return this->cargo[type];
}

bool Cargo::contains(Cargo newCargo)
{
	Cargo::iterator newStock;
	for (newStock = newCargo.begin();
		newStock != newCargo.end();
		++newStock
	{
		if (this->cargo[newStock->first] < newStock->second)
		{
			return false;
		}
	}
	return true;
}

bool Cargo::delCargo(Cargo newCargo)
{
	Cargo::iterator newStock;
	if (this->contains(newCargo) == false){
		return false;
	}
	for (newStock = newCargo.begin();
		newStock != newCargo.end();
		++newStock
	{
		this->cargo[newStock->first] -= newStock->second;
		if (this->cargo[newStock->first] == 0) {
			this->cargo.erase(newStock->first);
		}
	}
	return true;
}

bool Cargo::operator==(const Cargo &that) const
{
	return this->cargo == that.cargo;
}

Cargo::iterator Cargo::begin()
{
	return this->cargo.begin();
}

Cargo::iterator Cargo::end(){
	return this->cargo.end();
}


