#include <algorithm>
#include <vector>

#include "Economy.hpp"

Economy::Economy() :
	 bases(std::vector<Base>())
{
}

Economy::~Economy()
{
}

void Economy::addBase(Base base)
{
	this->bases.push_back(base);
}

void Economy::delBase(Base base)
{
	//TODO
}

std::vector<Base> Economy::getFactories()
{
	return this->bases;
}

void Economy::tick()
{
	for (std::vector<Base>::iterator iter = this->bases.begin();
		iter != this->bases.end();
		++iter
	){
		iter->Process();
	}
}
