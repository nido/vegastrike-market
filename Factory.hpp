/*
 * Factory for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */
#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <string>
#include <vector>
#include <map>
#include <stdbool.h>

class Factory;

//#include "Reserve.hpp"
//#include "Economy.hpp"


/**An economical sector defined by what it can output given its input.
 *
 * Not a single factory. Rather every factory of that type put together,
 * all following the same strategy as all other factories created.
 */
class Factory {

public:
	Factory(Cargo* consumes, uint consumeCount, Cargo* produces, uint produceCount, Cargo* inputs, Cargo* outputs);
	~Factory();
	/** (if possible) Do producuce */
	void Produce();

private:
	Factory();
	/** determine whether production is possible */
	bool CanProduce(void);
	/** Points to a Cargo source where Cargo can be gotten. */
	Cargo* inputs;
	/** Points to where the result cargo needs to be saved. */
	Cargo* outputs;
	/** How much of which cargo is consumed in production. */
	Cargo* consumes;
	/** How much of each cargo is produced in production. */
	Cargo* produces;
	/** How much different input Cargo's there are. */
	uint consumeCount;
	/** How much Cargo outputs are produced. */
	uint produceCount;
};

#endif
