#include <algorithm>
#include <vector>
#include <iostream>
#include "Base.hpp"

Base::Base() : factories(std::vector<Factory>()), cargoStore(Cargo()) {}

Base::~Base() {}

void Base::addFactory(Factory *factory) { this->factories.push_back(*factory); }

void Base::delFactory(Factory* factory) {
  std::vector<Factory>::iterator iter =
      std::find(this->factories.begin(), this->factories.end(), *factory);
  this->factories.erase(iter);
}

std::vector<Factory> Base::getFactories() { return this->factories; }

void Base::addCargo(const Cargo *cargo) { this->cargoStore.addCargo(cargo); }

void Base::delCargo(const Cargo *cargo) { this->cargoStore.delCargo(cargo); }

const Cargo *Base::getCargo() const { return &this->cargoStore; }

bool Base::operator==(const Base &that) const {
  return (this->factories == that.factories &&
          this->cargoStore == that.cargoStore);
}

void Base::Process() {
  //	std::cout<<"Processing base "<<this<<" ";
  for (std::vector<Factory>::iterator iter = this->factories.begin();
       iter != this->factories.end(); ++iter) {
    //		std::cout<<".";
    iter->Produce(&this->cargoStore);
  }
  //	std::cout<<std::endl;
}
