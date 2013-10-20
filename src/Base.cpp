#include <algorithm>

#include "Base.hpp"

Base::Base() : factories(std::vector<Factory>()), cargoStore(Cargo()) {}

Base::~Base() {}

void Base::addFactory(const Factory& factory) {
	this->factories.push_back(factory);
}

void Base::delFactory(const Factory& factory) {
  std::vector<Factory>::iterator iter =
      std::find(this->factories.begin(), this->factories.end(), factory);
  this->factories.erase(iter);
}

const std::vector<Factory>& Base::getFactories() {
  return this->factories;
}

void Base::addCargo(const Cargo& cargo) {
  this->cargoStore.addCargo(cargo);
}

void Base::delCargo(const Cargo& cargo) {
  this->cargoStore.delCargo(cargo);
}

const Cargo& Base::getCargo() const {
  return this->cargoStore;
}

bool Base::operator==(const Base &that) const {
  return (this->factories == that.factories &&
          this->cargoStore == that.cargoStore);
}

void Base::Process() {
  for (std::vector<Factory>::iterator iter = this->factories.begin();
       iter != this->factories.end(); ++iter) {
    iter->Produce(this->cargoStore);
  }
}
