#include <assert.h>
#include <iostream>

#include "Cargo.hpp"

void Cargo::addCargo(unsigned int quantity){
	this->quantity += quantity;
}
void Cargo::delCargo(unsigned int quantity){
	assert (this->quantity >= quantity);
	this->quantity -= quantity;
}

/*void Cargo::printOut(){
	std::cout<<quantity<<" count of "<<this->type->name<<std::endl;
}*/
