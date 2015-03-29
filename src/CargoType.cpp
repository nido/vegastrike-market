#include <sstream>

#include "CargoType.hpp"

CargoType::CargoType()
    : name("Debug"), category("Debug"), description(""), mass(1.0), volume(1.0),
      basePrice(1.0) {
  // TODO: fix description
}

CargoType::CargoType(std::string name, std::string category, float mass,
                     float volume, float price)
    : name(name), category(category), description(""), mass(mass),
      volume(volume), basePrice(price) {
  // TODO: fix description
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

const std::string &CargoType::getCategory() const { return this->category; }

float CargoType::getMass() const { return this->mass; }

float CargoType::getVolume() const { return this->volume; }

float CargoType::getBasePrice() const { return this->basePrice; }

std::string CargoType::getXML(bool endTag) const {
  std::string endtag = "";
  if (endTag) {
    endtag = "/";
  }
  std::stringstream xmlstream;
  xmlstream << "<CargoType name=\"" << this->name << "\" category=\""
            << this->category << "\" mass=\"" << this->mass << "\" volume=\""
            << this->volume << "\" price=\"" << this->basePrice << "\" "
            << endtag << ">";

  return xmlstream.str();
}
