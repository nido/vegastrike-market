#ifndef H_FACTORY
#define H_FACTORY

#include <vector>

#include "ProductionOption.hpp"

class Factory;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 */
class Factory {
public:
  /** Create an empty Factory */
  Factory();

  /** copy constructor
   * @param that the Factory to copy
   */
  Factory(const Factory& that);

  /** delete a factory */
  ~Factory();

  /** (if possible) Do producuce 
   * @param cargoStore Cargo to take cargo from and put cargo in
   */
  void Produce(Cargo& cargoStore) const;

  /** Check if production is possible
   * @param cargoStore Cargo from which to make this assessment
   * @return true when Production is possible, false otherwise.
   */
  bool canProduce(const Cargo& cargoStore) const;

  /** Add another production option
   * @param option the ProductionOption to add to the factory
   */
  void addProductionOption(const ProductionOption& option);

  /** Set the active production option.
 	 * Note this one needs to be part of the Factory's own ProductionOptions
 	 * @param option the Option to use in Production
 	 */
  void setProductionOption(const ProductionOption& option);

  /** Compare factories to eachother. Factories are equal if the
   * have exactly the same ProductionOptions.
   * @param that Factory to compare to
   * @return true when the factories are equal, false otherwise
   */
  bool operator==(const Factory &that) const;

  /** Assign a Factory to this one
   * @param that Factory to copy
   * @return pointer to this factory
   */
  Factory& operator=(const Factory& that);

private:
  /** list of possible ProductionOptions */
  std::vector<ProductionOption> options;

  /** ProductionOption used on Production */
  std::vector<ProductionOption>::iterator productionPlan;
};

#endif //H_FACTORY
