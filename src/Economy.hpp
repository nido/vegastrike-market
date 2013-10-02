#ifndef H_ECONOMY
#define H_ECONOMY

#include <string>
#include <vector>
#include <stdbool.h>

#include "Base.hpp"
#include "Cargo.hpp"

class Economy;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Economy{
public:
	/** Create an empty Economy */
	Economy();

	/** delete a factory */
	~Economy();

	/** add a factory for production to the base */
	void addBase(Base factory);
	void delBase(Base factory);

	std::vector<Base> getFactories();
	void tick();
private:
	std::vector<Base> bases;
};

#endif //H_ECONOMY
