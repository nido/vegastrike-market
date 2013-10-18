#ifndef H_CARGO
#define H_CARGO

#include <map>

#include "CargoType.hpp"

/** A collection of individual amounts of different CargoType's.
 * This class should represent any random pile of stuff an entity
 * (player, ship, base) happens to have. 
 */
class Cargo {
public:
  /** Create an empty Cargo container */
  Cargo();

  /** deconstructor */
  ~Cargo();

  /**  Add quantity cargo of type to this Cargo
   * @param type reference to the CargoType to add
   * @param quantity the amount of cargo to add
   */
  void addCargo(const CargoType& type, const unsigned int quantity);

  /** Add newCargo to the cargohold 
   * @param newCargo reference to another cargo to add.
   */
  void addCargo(const Cargo& newCargo);

  /** Removes cargo from this Cargo
   * TODO: replace return with exceptions
   * @param newCargo reference to the Cargo to remove.
   * @return true when successfull, false on failure
   */
  bool delCargo(const Cargo& newCargo);

  /** Counts the amount of Caargo::const_iterator 
   * @param type reference to the CargoType to find
   * @return the amount of CargoType in this Cargo
   */
  unsigned int getCount(const CargoType& type) const;

  /** check if the content of newCargo is in this Cargo
   * @param newCargo Cargo that we wish to check for
   * @return true if newCargo is in this Cargo, false on failure
   */
  bool contains(const Cargo& newCargo) const;

  /** Compare one cargo to another
   * @param that reference to the other cargo
   * @return true when this and that are equal, false otherwise
   */
  bool operator==(const Cargo& that) const;

private:
  /** Iterator datastructure iterator */
  typedef std::map<CargoType, unsigned int>::iterator iterator;

  /** Iterator datastructure const iterator */
  typedef std::map<CargoType, unsigned int>::const_iterator
      const_iterator;

  /** const Begin of the Cargo datastructure
   * @return const iterator to the begin of cargo */
  const_iterator begin() const;

  /** const End of the Cargo datastructure
   * @return const iterator to the end of cargo */
  const_iterator end() const;

  /** Begin of the Cargo datastructure
   * @return iterator to the begin of cargo */
  iterator begin();

  /** End of the Cargo datastructure
   * @return iterator to the end of cargo */
  iterator end();

  /** The datastructure holding the actual cargo itself. */
  std::map<CargoType, unsigned int> cargo;
};

#endif //H_CARGO
