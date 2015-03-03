#include <cassert>
#include <sstream>

#include "Cargo.hpp"

Cargo::Cargo() : cargo(std::map<CargoType, unsigned int>()) {}

Cargo::~Cargo()
{
}

std::string Cargo::getName() const
{
   if (this->cargo.begin() == this->cargo.end())
   {
      return (this->cargo.begin())->first.getName();
   } else {
      return "stuff";
   }
}

void Cargo::addCargo(const CargoType& type, unsigned int quantity)
{
    assert(quantity != 0);
    Cargo::iterator current = this->cargo.find(type);
    if (current != this->cargo.end()) {
        quantity += current->second;
    }
    this->cargo[type] = quantity;
}


void Cargo::addCargo(const Cargo& newCargo)
{
    if(newCargo.cargo.empty()) {
        return;
    }
    Cargo::const_iterator newStock;
    for (newStock = newCargo.cargo.begin(); newStock != newCargo.cargo.end(); ++newStock) {
        this->addCargo(newStock->first, newStock->second);
    }
}


bool Cargo::delCargo(const Cargo& newCargo)
{
    if (this == &newCargo) {
        this->cargo.clear();
        return true;
    }
    if(newCargo.cargo.empty()) {
        return true;
    }

    if (this->contains(newCargo) == false) {
        return false;
    }

    for (Cargo::const_iterator newStock = newCargo.cargo.begin(); newStock != newCargo.cargo.end(); ++newStock) {
        this->cargo[newStock->first] -= newStock->second;
        if (this->cargo[newStock->first] == 0) {
            this->cargo.erase(newStock->first);
        }
    }
    return true;
}


unsigned int Cargo::getCount(const CargoType& type) const
{
    unsigned int result = 0;
    std::map<CargoType, unsigned int>::const_iterator thing =  this->cargo.find(type);
    if (thing != this->cargo.end()) {
        result = thing->second;
    }
    return result;
}


bool Cargo::contains(const Cargo& newCargo) const
{
    if (newCargo.cargo.empty()) {
        return true;
    }
    if (this->cargo.empty()) {
        return false;
    }
    Cargo::const_iterator newStock;
    for (newStock = newCargo.cargo.begin(); newStock != newCargo.cargo.end(); ++newStock) {
        if (this->cargo.find(newStock->first) == this->cargo.end()) {
            return false;
        }
        if (this->cargo.at(newStock->first) < newStock->second) {
            return false;
        }
    }
    return true;
}


bool Cargo::operator==(const Cargo &that) const
{
    return this->cargo == that.cargo;
}


std::string Cargo::getXML() const
{
    std::stringstream xmlstream;
    xmlstream<<"<Cargo>";

    for(Cargo::const_iterator i = this->cargo.begin();
    i != this->cargo.end(); ++i) {
        xmlstream<<"<entry>"<<i->first.getXML()<<i->second<<"</entry>";
    }
    xmlstream<<"</Cargo>";
    return xmlstream.str();
}
