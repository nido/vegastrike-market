#ifndef H_FACTORY
#define H_FACTORY
/*
 * ProductionOption for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */

#include <string>
#include <vector>
#include <stdbool.h>

#include "ProductionOption.hpp"

class Factory;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Factory{
public:
	/** Create an empty Factory for cppunit */
	Factory();
	/** Create a Factory */
	Factory(std::vector<ProductionOption> options);
	/** delete a factory */
	~Factory();

	/** (if possible) Do producuce */
	void Produce(CargoHold* cargoStore);
	bool CanProduce(CargoHold* cargoStore);
	/** describes extra requiested input cargo */
private:
	std::vector<ProductionOption> options;
};

#endif //H_FACTORY
