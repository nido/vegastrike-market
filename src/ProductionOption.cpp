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
	for(size_t i = 0; i < this->consumes.cargo.size(); i++){
		for(size_t j = 0; j < cargoStore->cargo.size(); j++){
			Cargo* temp = cargoStore->findCargo(consumes.cargo[i].type);

			if (temp == NULL){
				// cargo not found, cannot produce.
				return false;
			}
			if(temp->getCount() < consumes.cargo[i].getCount() ) {
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
	for(size_t i = 0; i < this->consumes.cargo.size(); i++){
		temp = cargoStore->findCargo(consumes.cargo[i].type);
		assert(temp != NULL);
		temp->delCargo(consumes.cargo[i].getCount());
	}
	for(size_t i = 0; i < this->produces.cargo.size(); i++){
		// TODO: add output cargo to cargolist if nonexistent
		temp = cargoStore->findCargo(produces.cargo[i].type);
		if (temp == NULL){
			cargoStore->cargo.push_back(Cargo(produces.cargo[i].type, produces.cargo[i].getCount()));
		} else {
			temp->addCargo(produces.cargo[i].getCount());
		}
	}
}

Cargo* findCargo(CargoType* type, CargoHold *cargoStore){
       for(size_t i = 0; i < cargoStore->cargo.size(); i++){
               if (type == cargoStore->cargo[i].type){
                       return &cargoStore->cargo[i];
               }
       }
       return NULL;
}

Cargo* findCargo(CargoType* type, std::vector<Cargo> *cargoStore){
       for(size_t i = 0; i < cargoStore->size(); i++){
               if (type == cargoStore[0][i].type){
                       return &cargoStore[0][i];
               }
       }
       return NULL;
}
