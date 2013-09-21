#ifndef H_CARGO
#define H_CARGO

#include <string>
#include <vector>

class Cargo;
class CargoType;

/** A pile of a certain type of cargo.
 * For example, if the player has 4 middles, 2 Iron Ores, and 300
 * LaserDrills, of which 200 are in another ship, this would make 4
 * different Cargo(piles).
 */
class Cargo
{
public:
	CargoType* type;
	unsigned int quantity;

	/** Stupid experiment */
	Cargo() : type(NULL), quantity(1){};

	/** Create a new pile of Cargo */
	Cargo(CargoType* type, unsigned int quantity) :
		type(type), quantity(quantity){};

	/** Cargo is sorted in relation to its CargoType and quantity
	 * Whilst these two Cargo's of the same type should be combined
	 * into a single cargo and not sorted as such, assertions which
	 * pile of cargo is bigger may be useful in other ways.
	 */
	bool operator<( const Cargo &that ) const
	{
		if(this->type == that.type){
			return this->quantity < that.quantity;
		} else {
			return this->type < that.type;
		}		
	}

	void addCargo(unsigned int quantity);
	void delCargo(unsigned int quantity);
};

/** Types of Cargo available. 
 * It doesn't matter whether a piece of cargo is on the players ship,
 * his target he just fired a missle at, some random planet, or in the
 * middle of a transaction, like name, mass and volume are constant.
 * Also, being able to compare _types_ of cargo rather then two
 * different cargo piles in order to easily add and remove cargo from
 * eachother.
 */
class CargoType
{
public:
	/** Name of the cargo, for example "Iron Ore" */
	std::string name;
	/** Cargo catagory. Part of vegastrike's core thoug it is packed in
	 * a different sort of string container.
	 * TODO: At the moment, I assume the difference between "Raw
	 * Materials" and "Ores" is done with a sort of separator like "Raw
	 * Materials/Ores" and consider this a problem for interation later.
	 */
	std::string catagory;
	/** Long description of the cargo. */
	std::string description;
	/** Mass of one cargo. Weight, more or less. */
	float mass;
	/* space taken up by one unit of this type of cargo */
	float volume;

	/** Create a new CargoType
 	 */
	CargoType( std::string name, std::string catagory, float mass, float volume) :
        	name(name), catagory(catagory), mass(mass), volume(volume){}

	/** Compare cargotypes.
	 * Returns true when both the name and catagory of the cargo are
	 * the same. Note you can have two different CargoType's and still
	 * have it be the same CargoType in an equastion, though,
	 * preferably, one would have all Cargo of the same type point to
	 * the same CargoType.
	 */ 
	bool operator==( const CargoType &that ) const
	{
		return ((this->name.compare(that.name) == 0)
			&& (this->catagory.compare(that.catagory) == 0));
	}

	/** Comparator to have a way to order (types of) cargo */
    bool operator<( const CargoType &that ) const
    {
		return((this->catagory == that.catagory) ?
			(this->name < that.name) :
			(this->catagory < that.catagory));
    }
};
#endif // H_CARGO
