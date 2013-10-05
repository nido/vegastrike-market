#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

#include <assert.h>

#include "CargoType.hpp"


std::vector<CargoType> CargoType::allCargoTypes = std::vector<CargoType>();

void CargoType::addToVector()
{
	this->i = std::find(this->allCargoTypes.begin(), this->allCargoTypes.end(), *this);
	if (this->i ==  this->allCargoTypes.end()){
		this->allCargoTypes.push_back(*this);
		this->i = std::find(this->allCargoTypes.begin(), this->allCargoTypes.end(), *this);
	}
}

CargoType::iterator CargoType::getRandomCargoType(){
	size_t number = CargoType::allCargoTypes.size();
	assert(number != 0);
	number = rand() % number;
	return CargoType::allCargoTypes.begin() + number;
}

CargoType::CargoType():
	name("Debug"), catagory("Debug"), mass(1.0), volume(1.0),
	basePrice(1.0)
{
	this->addToVector();
}

CargoType::CargoType( std::string name, std::string catagory,
	float mass, float volume, float price) :
        name(name), catagory(catagory), mass(mass), volume(volume),
	basePrice(price)
{
	this->addToVector();
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

CargoType::iterator CargoType::getIterator()
{
	return this->i;
}

std::vector<CargoType> getCargoTypeVector()
{
	return std::vector<CargoType>();
}
