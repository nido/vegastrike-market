#include <algorithm>

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
		pile->addCargo(newCargo.quantity);
		
	}
}
void CargoHold::addCargo(CargoHold newCargo){
	for(size_t i = 0; i< newCargo.cargo.size(); i++){
		this->addCargo(newCargo.cargo[i]);
	}
}
bool CargoHold::delCargo(CargoType* type, unsigned int quantity){
	Cargo* pile = this->findCargo(type);
	if (pile->quantity >= quantity){
		pile->quantity -= quantity;
		return true;
	} else {
		return false;
	}
}
/**
bool CargoHold::delCargo(Cargo newCargo);
	Cargo* pile = this->findCargo(newCargo.type);

bool CargoHold::delCargo(CargoHold newCargo);
	Cargo* pile = this->findCargo(newCargo.type);
*/
Cargo* CargoHold::findCargo(CargoType* type){
	for(size_t i = 0; i < this->cargo.size(); i++){
		if (type == this->cargo[i].type){
			return &cargo[i];
		}
	}
	return NULL;
};
