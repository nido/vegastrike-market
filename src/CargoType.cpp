#include <assert.h>
#include <iostream>

#include "CargoType.hpp"

CargoType::CargoType():
	name("Debug"), catagory("Debug"), mass(1.0), volume(1.0),
	basePrice(1.0)
{
}

CargoType::CargoType( std::string name, std::string catagory,
	float mass, float volume, float price) :
        name(name), catagory(catagory), mass(mass), volume(volume),
	basePrice(price)
{
}

std::string CargoType::getName()
{
	return this->name;
}

bool CargoType::operator==( const CargoType &that ) const
{
	return ((this->name.compare(that.name) == 0)
		&& (this->catagory.compare(that.catagory) == 0));
}

bool CargoType::operator<( const CargoType &that ) const
{
	return((this->catagory == that.catagory) ?
		(this->name < that.name) :
		(this->catagory < that.catagory));
}

float CargoType::getBasePrice()
{
	return this->basePrice;
}
