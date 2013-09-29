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
ProductionOption::ProductionOption()
{
}

/** TODO: Make sure it has its own stores of Cargo to draw from. Cargo is sorted  */
ProductionOption::ProductionOption(Cargo consumes, Cargo produces){
	this->consumes = consumes;
	this->produces = produces;
}

ProductionOption::~ProductionOption(){
}

/** Determines whether the factory is able to produce (at all).
 *
 * Production can commence when the cargoStore provided has at least
 * the Cargo defined in the 'consumes' vector.
 */
bool ProductionOption::canProduce(Cargo *cargoStore){
	return cargoStore->contains(this->consumes);
}

void ProductionOption::Produce(Cargo *cargoStore){
	bool result;
	Cargo* temp;
	if (this->canProduce(cargoStore) == false){
		return;
	}

	result = cargoStore->delCargo(consumes);
	// make sure this actually happened
	assert(result != flase);

	cargoStore->addCargo(produces);
}
