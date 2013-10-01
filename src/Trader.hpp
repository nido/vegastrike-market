#ifndef H_TRADER
#define H_TRADER

#include "CargoHold.hpp"

class Trader;

/** A base class which implements a trading capability.
 * This class will implement the 'trade' function to help insure trade
 * is done in a consistent matter
 */
Class Trader
{
public:
	CargoHold cargo;
	unsigned int credits;
	void addTradeCargo(CargoHold new_cargo);
	CargoHold getTradeCargo();
}
private:
	CargoHold tradeCargo;
	
};

bool Trade(Trader* from, Trader* to, CargoHold cargo);
#endif //H_TRADER
