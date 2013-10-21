#include <sstream>

#include "CargoType.hpp"

CargoType::CargoType()
    : name("Debug"), category("Debug"), description(""), mass(1.0), volume(1.0), basePrice(1.0) {
//TODO: fix description
}

CargoType::CargoType(std::string name, std::string category, float mass,
                     float volume, float price) :
	name(name),
	category(category),
	description(""),
	mass(mass),
	volume(volume),
	basePrice(price)
{
//TODO: fix description
}

std::string CargoType::getName() const { return this->name; }

bool CargoType::operator==(const CargoType &that) const {
  return ((this->name.compare(that.name) == 0) &&
          (this->category.compare(that.category) == 0));
}

bool CargoType::operator<(const CargoType &that) const {
  return ((this->category == that.category) ? (this->name < that.name)
                                            : (this->category < that.category));
}

float CargoType::getBasePrice() const { return this->basePrice; }

std::string CargoType::getXML() const {
  std::stringstream xmlstream;
  xmlstream << "<CargoType name=\"" << this->name << "\" category=\""
            << this->category << "\" mass=\"" << this->mass << "\" volume=\""
            << this->volume << "\" price=\"" << this->basePrice << "\" />";

  return xmlstream.str();
}
