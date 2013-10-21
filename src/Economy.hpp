#ifndef H_ECONOMY
#define H_ECONOMY

#include "Base.hpp"

class Economy;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Economy {
public:
  /** Create an empty Economy */
  Economy();

  /** delete a factory */
  ~Economy();

  /** add a Base to the Economy
   * @param base the Base to add
   */
  void addBase(const Base& base);

  /** Removes a base from the economy
   * @param base the Base to delete
   */
  void delBase(const Base& base);

  /** Get all bases
   * @return a vector of all Base in this Economy
   */
  const std::vector<Base>& getBases();

  /** Process an economic turn */
  void tick();

private:
  /** All Bases in this Economy */
  std::vector<Base> bases;
};

#endif //H_ECONOMY
