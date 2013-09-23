#ifndef H_PRODUCTIONOPTION
#define H_PRODUCTIONOPTION
/*
 * ProductionOption for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */

#include <vector>

#include <stdbool.h>

#include "Cargo.hpp"
#include "CargoHold.hpp"

class ProductionOption;

/** One of the possibilities for a factory to produce.
 *
 * Factories are sometimes able to make different quantities of products
 * depending on available inputs. A ProductionOption 
 */
class ProductionOption {

public:
	ProductionOption();
	ProductionOption(CargoHold consumes, CargoHold produces);
	~ProductionOption();
	/** (if possible) Do producuce */
	void Produce(CargoHold *cargoStore);
	/** determine whether production is possible */
	bool CanProduce(CargoHold *cargoStore);
private:
	/** Cargo consumed by production. */
	CargoHold consumes;
	/** Cargo produced by production. */
	CargoHold produces;
};
#endif // H_PRODUCTIONOPTION
