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
	/** Create an empty Factory */
	Factory();

	/** delete a factory */
	~Factory();

	/** (if possible) Do producuce */
	void Produce(Cargo* cargoStore);

	/** Check if production is possible */
	bool canProduce(Cargo* cargoStore);

	/** Add another production option */
	void addProductionOption(ProductionOption option);
private:
	std::vector<ProductionOption> options;
};

#endif //H_FACTORY
