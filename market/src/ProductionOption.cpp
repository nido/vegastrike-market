/*
 * Copyright(c) 2009: peter.schaefer@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * ProductionOption for producing goods, v 0.1.3
 * @author peter.schaefer@gmail.com
 */
#include <limits>
#include <algorithm>
#include <string>
#include <vector>

#include "ProductionOption.hpp"

#include <assert.h>

/** Empty constructor for cpptest */
ProductionOption::ProductionOption() : consumes(new Cargo()), produces(new Cargo()) {}

ProductionOption::ProductionOption(const ProductionOption& that) :
	consumes(new Cargo(*that.consumes)),
	produces(new Cargo(*that.produces))
{
}


/** TODO: Make sure it has its own stores of Cargo to draw from. Cargo is sorted
 */
ProductionOption::ProductionOption(Cargo *consumes, Cargo *produces)
    : consumes(consumes), produces(produces) {}

ProductionOption::~ProductionOption() {
	delete consumes;
	delete produces;
}

/** Determines whether the factory is able to produce (at all).
 *
 * Production can commence when the cargoStore provided has at least
 * the Cargo defined in the 'consumes' vector.
 */
bool ProductionOption::canProduce(const Cargo *cargoStore) const {
  return cargoStore->contains(this->consumes);
}

void ProductionOption::Produce(Cargo *cargoStore) {
  if (this->canProduce(cargoStore) == false) {
    return;
  }
#ifndef NDEBUG
  bool result =
#endif //NDEBUG result is only used when NDEBUG is defined
      cargoStore->delCargo(consumes);
  // make sure this actually happened
  assert(result != false);

  cargoStore->addCargo(produces);
}

bool ProductionOption::operator==(const ProductionOption &that) const {
  if ((*(this->consumes) == *(that.consumes)) &&
      (*(this->produces) == *(that.produces))) {
    return true;
  }
  return false;
}

ProductionOption& ProductionOption::operator=(const ProductionOption& that)
{
	this->consumes = new Cargo(*that.consumes);
	this->produces = new Cargo(*that.produces);
	return *this;
}
