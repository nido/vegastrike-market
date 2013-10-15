#include <algorithm>
#include <iostream>
#include <stdexcept>

#include <assert.h>
#include <stdbool.h>

#include "Cargo.hpp"

Cargo::Cargo() : cargo(std::map<CargoType, unsigned int>()) {}

Cargo::Cargo(const Cargo& that) : cargo(that.cargo)
{
}

Cargo::~Cargo()
{
}


void Cargo::addCargo(const CargoType& type, unsigned int quantity) {
  assert(quantity != 0);
  Cargo::iterator current = this->cargo.find(type);
  if (current != this->end()) {
    quantity += current->second;
  }
  this->cargo[type] = quantity;
}

void Cargo::addCargo(const Cargo *newCargo) {
  assert(newCargo != NULL);
  assert(newCargo->begin() != newCargo->end());

  Cargo::const_iterator newStock;
  for (newStock = newCargo->begin(); newStock != newCargo->end(); ++newStock) {
    this->addCargo(newStock->first, newStock->second);
  }
}

unsigned int Cargo::getCount(CargoType type) const {
  unsigned int result = 0;
  std::map<CargoType, unsigned int>::const_iterator thing =  this->cargo.find(type);
  if (thing != this->cargo.end()){
    result = thing->second;
  }
  return result;
}

bool Cargo::contains(const Cargo *newCargo) const {
  assert(newCargo != NULL);
  if (newCargo->begin() == newCargo->end()) {
    return true;
  }
  if (this->cargo.empty()) {
    return false;
  }
  Cargo::const_iterator newStock;
  for (newStock = newCargo->begin(); newStock != newCargo->end(); ++newStock) {
    if (this->cargo.find(newStock->first) == this->cargo.end()) {
      return false;
    }
    if (this->cargo.at(newStock->first) < newStock->second) {
      return false;
    }
  }
  return true;
}

bool Cargo::delCargo(const Cargo *newCargo) {
  if (this == newCargo) {
    this->cargo.clear();
    return true;
  }
  Cargo::const_iterator newStock;
  if (this->contains(newCargo) == false) {
    return false;
  }
  for (newStock = newCargo->begin(); newStock != newCargo->end(); ++newStock) {
    this->cargo[newStock->first] -= newStock->second;
    if (this->cargo[newStock->first] == 0) {
      this->cargo.erase(newStock->first);
    }
  }
  return true;
}

bool Cargo::operator==(const Cargo &that) const {
  return this->cargo == that.cargo;
}

Cargo::const_iterator Cargo::begin() const { return this->cargo.begin(); }

Cargo::iterator Cargo::begin() { return this->cargo.begin(); }

Cargo::const_iterator Cargo::end() const { return this->cargo.end(); }

Cargo::iterator Cargo::end() { return this->cargo.end(); }
