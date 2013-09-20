/*
 * ProductionOption for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */
#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <vector>
#include <stdbool.h>

#include "images.h"

class ProductionOption;

/** One of the possibilities for a factory to produce.
 *
 * Factories are sometimes able to make different quantities of products
 * depending on available inputs. A ProductionOption 
 */
class ProductionOption {

public:
	ProductionOption(std::vector<Cargo> consumes, std::vector<Cargo> produces);
	~ProductionOption();
	/** (if possible) Do producuce */
	void Produce(std::vector<Cargo> *cargoStore);
	/** determine whether production is possible */
	bool CanProduce(std::vector<Cargo> *cargoStore);
private:
	/** Cargo consumed by production. */
	std::vector<Cargo> consumes;
	/** Cargo produced by production. */
	std::vector<Cargo> produces;
};

Cargo* findCargo(std::string name, std::vector<Cargo> *cargoStore);
#endif
