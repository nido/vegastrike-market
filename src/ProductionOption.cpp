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
#include "CargoHold.hpp"

#include <assert.h>

/** TODO: Make sure it has its own stores of Cargo to draw from. Cargo is sorted  */
ProductionOption::ProductionOption(CargoHold consumes, CargoHold produces){
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
bool ProductionOption::CanProduce(CargoHold *cargoStore){
	for(CargoHold::iterator i = this->consumes.begin();
			i != this->consumes.end(); i++){
		for(CargoHold::iterator j = cargoStore->begin();
				j != cargoStore->end(); j++){
			Cargo* temp = cargoStore->findCargo(j->type);
			if (temp == NULL){
				// cargo not found, cannot produce.
				return false;
			}
			if(temp->getCount() < i->getCount() ) {
				// Not enough of a certain input
				// is available, cannot produce.
				return false;
			}
		}
	}
	return true;
}

void ProductionOption::Produce(CargoHold *cargoStore){
	Cargo* temp;
	if (this->CanProduce(cargoStore) == false){
		return;
	}
	for(CargoHold::iterator i = this->consumes.begin();
			i != this->consumes.end(); i++){
		temp = cargoStore->findCargo(i->type);
		assert(temp != NULL);
		temp->delCargo(i->getCount());
	}
	for(CargoHold::iterator i = this->produces.begin();
			i != this->produces.end(); i++){
		// TODO: add output cargo to cargolist if nonexistent
		temp = cargoStore->findCargo(i->type);
		if (temp == NULL){
			cargoStore->addCargo(Cargo(i->type, i->getCount()));
		} else {
			temp->addCargo(i->getCount());
		}
	}
}
