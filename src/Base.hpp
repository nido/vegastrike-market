#ifndef H_BASE
#define H_BASE

#include <vector>

#include "Factory.hpp"

class Base;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Base {
public:
  /** Create an empty Base */
  Base();

  /** delete a factory */
  ~Base();

  /** iterator access */
  typedef std::vector<Factory>::iterator iterator;

  /** iterator access */
  typedef std::vector<Factory>::const_iterator const_iterator;

  /** add a factory for production to the base
   * @param factory the Factory to add
   */
  void addFactory(const Factory& factory);

  /** delete a factory from the base
   * @param factory the Factory to remove
   */
  void delFactory(const Factory& factory);

  /** Add cargo to the base
   * @param cargo the Cargo to add
   */
  void addCargo(const Cargo& cargo);

  /** delete cargo from the base 
   * @param cargo the Cargo to delete
   */
  void delCargo(const Cargo& cargo);

  /** return the Factories in this Base
   * @return vector of factories
   */
  const std::vector<Factory>& getFactories();

  const Cargo& getCargo() const;

  void Process();

  bool operator==(const Base& that) const;

private:
  std::vector<Factory> factories;
  Cargo cargoStore;
};

#endif //H_BASE
