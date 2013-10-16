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
class Base {
public:
  /** Create an empty Base */
  Base();

  /** delete a factory */
  ~Base();

  /** iterator access */
  typedef std::vector<Factory>::iterator iterator;
  typedef std::vector<Factory>::const_iterator const_iterator;

  /** add a factory for production to the base */
  void addFactory(Factory& factory);
  void delFactory(Factory& factory);

  /** Add cargo to the base */
  void addCargo(const Cargo *cargo);

  /** delete cargo from the base */
  void delCargo(const Cargo *cargo);

  std::vector<Factory> getFactories();
  const Cargo *getCargo() const;

  void Process();

  bool operator==(const Base &that) const;

private:
  std::vector<Factory> factories;
  Cargo cargoStore;
};

#endif //H_BASE
