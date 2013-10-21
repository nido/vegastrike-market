#ifndef H_CARGOTYPE
#define H_CARGOTYPE

#include <string>

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
    * @param category Cargo Category (mainly for the buy interface)
    * @param mass affects the weight of the Cargo and in extension what
    * the Cargo is loaded in.
    * @param volume size of one of this CargoType
    * @param price the base proce for this kind of CargoType
  	*/
  CargoType(std::string name, std::string category, float mass, float volume,
            float price);

  /** Compare cargotypes.
   * @param that  a CargoType to compare it to
   * @returns true when both the name and category of the cargo are
   * the same. Note you can have two different CargoType's and still
   * have it be the same CargoType in an equastion, though,
   * preferably, one would have all Cargo of the same type point to
   * the same CargoType.
   */
  bool operator==(const CargoType &that) const;

  /** Comparator to have a way to order (types of) cargo
   * @param that the CargoType to compare to
   * @return true when this is smaller then that; false otherwise
   */
  bool operator<(const CargoType &that) const;

  /** get base price
   * @return Base price of the CargoType in credits
   */
  float getBasePrice() const;

  /** get the cargo name
   * @return Name of this CargoType
   */
  std::string getName() const ;

  /** gives an XML representation of the CargoType
   * @return XML representation of this CargoType
   */
  std::string getXML() const;

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

  /** space taken up by one unit of this type of cargo */
  float volume;

  /** Base price */
  float basePrice;
};
#endif // H_CARGOTYPE
