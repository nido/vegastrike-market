#ifndef H_BASE
#define H_BASE

#include <string>
#include <vector>
#include <stdbool.h>

#include "Factory.hpp"
#include "Cargo.hpp"

class Base;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Base{
public:
	/** Create an empty Base */
	Base();

	/** delete a factory */
	~Base();

	/** iterator access */
	typedef std::vector<Factory>::iterator iterator;
	typedef std::vector<Factory>::const_iterator const_iterator;
        iterator begin();
        iterator end();

	/** add a factory for production to the base */
	void addFactory(Factory factory);

	/** Add cargo to the base */
	void addCargo(Cargo cargo);

	/** delete cargo from the base */
	void delCargo(Cargo cargo);

private:
	std::vector<Factory> factories;
	Cargo cargoStore;
};

#endif //H_BASE