#include <cassert>

#include "ProductionOption.hpp"

/** Empty constructor for cpptest */
ProductionOption::ProductionOption() : consumes(Cargo()), produces(Cargo()) {}

/** Create a ProductionOption with a set input/output
 * @param consumes what is needed to produce
 * @param produces what is produces out of consumes
 */
ProductionOption::ProductionOption(const Cargo &consumes, const Cargo &produces)
    : consumes(consumes), produces(produces) {}

ProductionOption::~ProductionOption() {}

bool ProductionOption::canProduce(const Cargo &cargoStore) const {
  return cargoStore.contains(this->consumes);
}

void ProductionOption::Produce(Cargo &cargoStore) const {
  if (this->canProduce(cargoStore) == false) {
    return;
  }
  bool result = cargoStore.delCargo(consumes);
  assert(result != false);
  cargoStore.addCargo(produces);
}

bool ProductionOption::operator==(const ProductionOption &that) const {
  if ((this->consumes == that.consumes) && (this->produces == that.produces)) {
    return true;
  }
  return false;
}

const Cargo ProductionOption::input() const { return this->consumes; }
const Cargo ProductionOption::output() const { return this->produces; }
