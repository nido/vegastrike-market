#ifndef H_CARGO
#define H_CARGO

#include <map>

#include "CargoType.hpp"


/** Cargo represents a collection of individual amounts of different types of cargo.
 */
class Cargo
{
public:
	/** empty one */
	Cargo();

	/**  Add quantity cargo of type to the cargohold */
	void addCargo(CargoType type, unsigned int quantity);

	/** Add newCargo to the cargohold */
	void addCargo(Cargo newCargo);

	/** Removes cargo from this cargohold
	 * returns a boolean saying whether the action succeded */
	bool delCargo(Cargo newCargo);

	unsigned int getCount(CargoType type);

	/** check whether the content of newCargo is in the cargohold */
	bool contains(Cargo newCargo);

	bool operator==(const Cargo &that) const;

private:
	/** iterator access */
	typedef std::map<CargoType, unsigned int>::iterator iterator;
	typedef std::map<CargoType, unsigned int>::const_iterator const_iterator;
        iterator begin();
        iterator end();

	/** The actual cargo(s) itself. */
	std::map<CargoType, unsigned int> cargo;
};

#endif //H_CARGO
