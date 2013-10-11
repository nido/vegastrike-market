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
	void addCargo(const CargoType::iterator type, const unsigned int quantity);

	/** Add newCargo to the cargohold */
	void addCargo(const Cargo* newCargo);

	/** Removes cargo from this cargohold
	 * returns a boolean saying whether the action succeded */
	bool delCargo(Cargo* newCargo);

	unsigned int getCount(CargoType::iterator type);

	/** check whether the content of newCargo is in the cargohold */
	bool contains(Cargo* newCargo);

	bool operator==(const Cargo &that) const;

private:
	/** iterator access */
	typedef std::map<CargoType::iterator, unsigned int>::iterator iterator;
	typedef std::map<CargoType::iterator, unsigned int>::const_iterator const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();

	/** The actual cargo(s) itself. */
	std::map<CargoType::iterator, unsigned int> cargo;
};

#endif //H_CARGO
