#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>

#include <assert.h>

#include "CargoType.hpp"


CargoType CargoType::getRandomCargoType() {
	return CargoType();
}

CargoType::CargoType()
    : name("Debug"), catagory("Debug"), description(""), mass(1.0), volume(1.0), basePrice(1.0) {
//TODO: fix description
std::cout<<"Constructor CargoType(): "<<this->name<<std::endl;
}

CargoType::CargoType(std::string name, std::string catagory, float mass,
                     float volume, float price) :
	name(name),
	catagory(catagory),
	description(""),
	mass(mass),
	volume(volume),
	basePrice(price)
{
//TODO: fix description
std::cout<<"Constructor CargoType(name, catagory, mass, volume, price): "<<this->name<<std::endl;
}

std::string CargoType::getName() { return this->name; }

bool CargoType::operator==(const CargoType &that) const {
  return ((this->name.compare(that.name) == 0) &&
          (this->catagory.compare(that.catagory) == 0));
}

bool CargoType::operator<(const CargoType &that) const {
  return ((this->catagory == that.catagory) ? (this->name < that.name)
                                            : (this->catagory < that.catagory));
}

float CargoType::getBasePrice() { return this->basePrice; }

std::string CargoType::getXML() {
  std::stringstream xmlstream;
  xmlstream << "<CargoType name=\"" << this->name << "\" catagory=\""
            << this->catagory << "\" mass=\"" << this->mass << "\" volume=\""
            << this->volume << "\" price=\"" << this->basePrice << "\">";

  return xmlstream.str();
}
