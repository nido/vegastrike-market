#include <assert.h>
#include <iostream>

#include "CargoType.hpp"

CargoType::CargoType():
	name("Debug"), catagory("Debug"), mass(1.0), volume(1.0), basePrice(1.0)
{
}

CargoType::CargoType( std::string name, std::string catagory, float mass, float volume, float price) :
        	name(name), catagory(catagory), mass(mass), volume(volume), basePrice(price)
{
}

bool CargoType::operator==( const CargoType &that ) const
{
#ifndef NDEBUG
	std::cout<<"Coparing CargoTypes: "<<this->name<<", "<<this->catagory<<", "<<that.name<<", "<<that.catagory<<std::endl;
#endif
	return ((this->name.compare(that.name) == 0)
		&& (this->catagory.compare(that.catagory) == 0));
}

bool CargoType::operator<( const CargoType &that ) const
{
	return((this->catagory == that.catagory) ?
		(this->name < that.name) :
		(this->catagory < that.catagory));
}
