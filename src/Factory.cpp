#include <vector>
#include <algorithm>
#include <cassert>

#include "Factory.hpp"

Factory::Factory()
    : options(std::vector<ProductionOption>()),
      productionPlan(this->options.end()) {}

Factory::~Factory() {
}

/** Determines whether the factory is able to produce (at all). */
bool Factory::canProduce(const Cargo& cargoStore) const {
  if (this->options.empty()) {
    return false;
  }
  assert((this->productionPlan == this->options.end()) == false);
  if (this->productionPlan->canProduce(cargoStore)) {
    return true;
  }
  return false;
}

void Factory::Produce(Cargo& cargoStore) const {
  if (!this->canProduce(cargoStore)) {
    return;
  }
  this->productionPlan->Produce(cargoStore);
}

void Factory::addProductionOption(const ProductionOption& option) {
  this->options.push_back(option);
  // set the first production option available as default
  if (this->options.size() == 1) {
    this->setProductionOption(*this->options.begin());
  }
}

void Factory::setProductionOption(const ProductionOption& option) {
  std::vector<ProductionOption>::iterator i = std::find(this->options.begin(), this->options.end(), option);
  //TODO: exceptions when not set
  this->productionPlan = i;
}

bool Factory::operator==(const Factory& that) const {
  return this->options == that.options;
}
