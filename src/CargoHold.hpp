#ifndef H_CARGOHOLD
#define H_CARGOHOLD

#include <vector>

#include "Cargo.hpp"

typedef std::vector<Cargo> CargoPile;

/** A bunch of different cargos together */
class CargoHold
{
public:
	/** The actual cargo(s) itself. */
	std::vector<Cargo> cargo;

	/** empty one */
	CargoHold() : cargo(std::vector<Cargo>()){}

	/** Generate an actual cargo */
	CargoHold(std::vector<Cargo> cargo) : cargo(cargo){}

	/**  Add quantity cargo of type to the cargohold */
	void addCargo(CargoType* type, unsigned int quantity);
	/** Add newCargo to the cargohold */
	void addCargo(Cargo newCargo);
	/** Add various cargo to the cargohold */
	void addCargo(CargoHold newCargo);
	/** Remove quantity cargo of type from the hold.
	 * returns a boolean saying whether the action succeded */
	bool delCargo(CargoType* type, unsigned int quantity);
	/** Remove cargo from the hold
	 * returns a boolean saying whether the action succeded */
	bool delCargo(Cargo newCargo);
	/** Remove a bunch of cargo from the hold
	 * returns a boolean saying whether the action succeded */
	bool delCargo(CargoHold newCargo);
	/** Finds a specific cargo type in a random cargo vector.
	 *
	 * returns NULL when the cargo is not present in the list.
	 */
	Cargo* findCargo(CargoType* type);
	/** Print this particular cargohold */
	void printOut();
};

#endif //H_CARGOHOLD
