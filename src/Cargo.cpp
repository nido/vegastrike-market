#include <assert.h>
#include <iostream>

#include "Cargo.hpp"

Cargo::Cargo() : type(NULL), quantity(1)
{
}

	/** Create a new pile of Cargo */
Cargo::Cargo(CargoType* type, unsigned int quantity) :
		type(type), quantity(quantity)
{
}

Cargo::~Cargo()
{
}

void Cargo::addCargo(unsigned int quantity)
{
	this->quantity += quantity;
}

void Cargo::delCargo(unsigned int quantity)
{
	assert (this->quantity >= quantity);
	this->quantity -= quantity;
}

bool Cargo::operator==( const Cargo &that ) const
{
#ifndef NDEBUG
	std::cout<<"Cargo=="<<this->type<<", "<<that.type<<std::endl;
#endif
	return this->type == that.type;
}

bool Cargo::operator<( const Cargo &that ) const
{
	if(this->type == that.type){
		return this->quantity < that.quantity;
	} else {
		return this->type < that.type;
	}		
}

unsigned int Cargo::getCount()
{
	return this->quantity;
}

CargoType::CargoType( std::string name, std::string catagory, float mass, float volume) :
        	name(name), catagory(catagory), mass(mass), volume(volume)
{
}
