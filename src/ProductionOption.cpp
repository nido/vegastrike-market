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

#include <string>

#include <vector>
#include "ProductionOption.hpp"

#include <assert.h>

/** TODO: Make sure it has its own stores of Cargo to draw from */
ProductionOption::ProductionOption(std::vector<Cargo> consumes, std::vector<Cargo> produces){
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
bool ProductionOption::CanProduce(std::vector<Cargo> *cargoStore){
	for(size_t i = 0; i < this->consumes.size(); i++){
		for(size_t j = 0; j < cargoStore->size(); j++){
			Cargo* temp = findCargo(consumes[i].type, cargoStore);

			if (temp == NULL){
				// cargo not found, cannot produce.
				return false;
			}
			if(temp->quantity < consumes[i].quantity) {
				// Not enough of a certain input
				// is available, cannot produce.
				return false;
			}
		}
	}
	return true;
}

void ProductionOption::Produce(std::vector<Cargo> *cargoStore){
	Cargo* temp;
	if (this->CanProduce(cargoStore) == false){
		return;
	}
	for(size_t i = 0; i < this->consumes.size(); i++){
		temp = findCargo(consumes[i].type, cargoStore);
		assert (temp != NULL);
		temp->quantity -= consumes[i].quantity;
	}
	for(size_t i = 0; i < this->produces.size(); i++){
		// TODO: add output cargo to cargolist if nonexistent
		temp = findCargo(produces[i].type, cargoStore);
		if (temp == NULL){
			cargoStore->push_back(Cargo(produces[i].type, 0));
//			delete temp; // it is stored in th
			temp = findCargo(produces[i].type, cargoStore);
		}
		assert (temp != NULL);
		temp->quantity += produces[i].quantity;
		
	}
}

/** Finds a specific cargo type in a random cargo vector.
 *
 * returns NULL when the cargo is not present in the list.
 */
Cargo* findCargo(const CargoType* type, std::vector<Cargo> *cargoStore){
	for(size_t i = 0; i < cargoStore->size(); i++){
		if (type == cargoStore[0][i].type){
			return &cargoStore[0][i];
		}
	}
	return NULL;
}
