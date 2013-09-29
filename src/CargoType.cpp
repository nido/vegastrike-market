#include <assert.h>
#include <iostream>

#include "CargoType.hpp"

CargoType::CargoType():
	name("DebugCargo"), catagory("DebugCargo"), mass(1000.0), volume(1000.0)
{
}

CargoType::CargoType( std::string name, std::string catagory, float mass, float volume) :
        	name(name), catagory(catagory), mass(mass), volume(volume)
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
