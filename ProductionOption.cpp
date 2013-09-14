#include "ProductionOption.hpp"

#include "math.h"

ProductionOption::ProductionOption(Products outputs, Products inputs, double sectorsize, double sectormin, Products costofanother){
	this->outputs= outputs;
	this->inputs= inputs;
	this->sectorsize = sectorsize;
	this->sectormin= sectormin;
	this->costofanother = costofanother;
}


ProductionOption::ProductionOption(Products outputs, Products inputs, double sectorsize, Products costofanother){
	this->outputs= outputs;
	this->inputs= inputs;
	this->sectorsize = sectorsize;
	this->sectormin= sqrt(sectorsize);
	this->costofanother = costofanother;
}
