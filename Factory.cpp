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
 * Factory for producing goods, v 0.1.3
 * @author peter.schaefer@gmail.com
 */
#include <limits>

#include <string>

#include <vector>

#include "images.h"

#include "roottracker.hpp"

#include "btree_iterator.hpp"

#include "Market.hpp"
#include "Factory.hpp"

#include <assert.h>

#include <math.h>


/** TODO: Make sure it has its own stores of Cargo to draw from */
Factory::Factory(Cargo* consumes, uint consumeCount, Cargo* produces, uint produceCount, Cargo* inputs, Cargo* outputs){
	this->inputs = inputs;
	this->outputs = outputs;
	this->produceCount = produceCount;
	this->consumeCount = consumeCount;
	this->consumes = consumes;
	this->produces = produces;

}

Factory::~Factory(){
}

/** Determines whether the factory is able to produce (at all). */
bool Factory::CanProduce(void){
	for(int i = 0; i < consumeCount; i++){
		if (this->consumes[i].quantity > this->inputs[i].quantity) {
			return false;
		}
	}
	return true;
}

void Factory::Produce(){
	if (this->CanProduce()){
		for(uint i = 0; i < consumeCount; i++){
			this->inputs[i].quantity -= this->consumes[i].quantity;
		}
		for(uint i = 0; i < this->produceCount; i++){
			this->outputs[i].quantity += this->produces[i].quantity;
		}
	}
}
