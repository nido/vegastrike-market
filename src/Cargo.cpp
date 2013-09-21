#include <assert.h>

#include "Cargo.hpp"

void Cargo::addCargo(unsigned int quantity){
	this->quantity += quantity;
}
void Cargo::delCargo(unsigned int quantity){
	assert (this->quantity >= quantity);
	this->quantity -= quantity;
}
