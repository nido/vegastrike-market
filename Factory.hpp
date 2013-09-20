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
	Factory(std::vector<ProductionOption> options);
	~Factory();

	/** (if possible) Do producuce */
	void Produce(Cargo cargoStore);
	/** describes extra requiested input cargo */
	std::vector<Cargo> ProductionOrder();
};

#endif //H_FACTORY
