#ifndef H_CARGOTYPE
#define H_CARGOTYPE

#include <iostream>
#include <string>
#include <vector>

class CargoType;

/** The properties of a piece of cargo.
 * It doesn't matter whether a piece of cargo is on the players ship,
 * his target he just fired a missle at, some random planet, or in the
 * middle of a transaction, like name, mass and volume are constant.
 * Also, being able to compare _types_ of cargo rather then two
 * different cargo piles in order to easily add and remove cargo from
 * eachother.
 */
class CargoType {
public:
  /** Create a default cargotype */
  CargoType();

  /** Create a new CargoType
    * @param name name of the cargo
  	*/
  CargoType(std::string name, std::string category, float mass, float volume,
            float price);

  /** Compare cargotypes.
 	 * Returns true when both the name and category of the cargo are
 	 * the same. Note you can have two different CargoType's and still
 	 * have it be the same CargoType in an equastion, though,
 	 * preferably, one would have all Cargo of the same type point to
 	 * the same CargoType.
 	 */
  bool operator==(const CargoType &that) const;

  /** Comparator to have a way to order (types of) cargo */
  bool operator<(const CargoType &that) const;

  /** get base price */
  float getBasePrice();

  /** get the cargo name */
  std::string getName();

  /** gives an XML representation of the CargoType */
  std::string getXML();

private:
  /** Name of the cargo, for example "Iron Ore" */
  std::string name;
  /** Cargo category.
 	 * Part of vegastrike's core thoug it is packed in a different
 	 * sort of string container.  The difference between "Raw
 	 * Materials" and "Ores" is done with a separator like "Raw
 	 * Materials/Ores" and is a problem already solved in the
 	 * vegastrike player trade interface.
 	 */
  std::string category;
  /** Long description of the cargo. */
  std::string description;
  /** Mass of one cargo. Weight, more or less. */
  float mass;
  /* space taken up by one unit of this type of cargo */
  float volume;
  /* Base price */
  float basePrice;
};
#endif // H_CARGOTYPE
