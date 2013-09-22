#include <algorithm>
#include <iostream>

#include <assert.h>

#include "CargoHold.hpp"

void addCargo(CargoType type, unsigned int quantity);

void CargoHold::addCargo(CargoType* type, unsigned int quantity){
	Cargo* pile = this->findCargo(type);
	if (pile == NULL){
		this->cargo.push_back(Cargo(type, quantity));
		std::sort(this->cargo.begin(), this->cargo.end());
	} else {
		pile->addCargo(quantity);
	}
}
void CargoHold::addCargo(Cargo newCargo){
	Cargo* pile = this->findCargo(newCargo.type);
	if (pile == NULL){
		this->cargo.push_back(newCargo);
		std::sort(this->cargo.begin(), this->cargo.end());
	} else {
		pile->addCargo(newCargo.getCount());
		
	}
}
void CargoHold::addCargo(CargoHold newCargo){
	for(size_t i = 0; i< newCargo.cargo.size(); i++){
		this->addCargo(newCargo.cargo[i]);
	}
}
bool CargoHold::delCargo(CargoType* type, unsigned int quantity){
	Cargo* pile = this->findCargo(type);
	if (pile == NULL){
		return false;
	}
	if (pile->getCount() >= quantity){
		pile->delCargo(quantity);
		return true;
	} else {
		return false;
	}
}

bool CargoHold::delCargo(Cargo newCargo){
	Cargo* pile = this->findCargo(newCargo.type);
	if (pile->getCount() >= newCargo.getCount() ){
		pile->delCargo(newCargo.getCount());
		return true;
	} else {
		return false;
	}
}

bool CargoHold::delCargo(CargoHold newCargo){
	Cargo* pile;
	// check if all can be subtracted
	for(size_t i=0; i<newCargo.cargo.size(); i++){
		pile = this->findCargo(newCargo.cargo[i].type);
		if (pile == NULL){
			return false;
		}
		if (pile->getCount() < newCargo.cargo[i].getCount()){
			return false;
		}
	}
	// subtract actual stuff
	for(size_t i=0; i<newCargo.cargo.size(); i++){
		assert(this->delCargo(newCargo.cargo[i]) == true);
	}
	return true;
}

Cargo* CargoHold::findCargo(CargoType* type){
	for(size_t i = 0; i < this->cargo.size(); i++){
		if ((type == this->cargo[i].type) && (this->cargo[i].getCount() > 0)){
			return &cargo[i];
		}
	}
	return NULL;
};

/*void CargoHold::printOut(){
	std::cout<<"Cargo hold printout:"<<std::endl;
	for(unsigned int i=0; i<this->cargo.size(); i++){
		this->cargo[i].printOut();
	}
}*/
