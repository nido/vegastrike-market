#ifndef H_FACTORY
#define H_FACTORY

#include "ProductionOption.hpp"

class Factory;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 */
class Factory {
public:
  /** Create an empty Factory */
  Factory();

  /** delete a factory */
  ~Factory();

  /** (if possible) Do producuce */
  void Produce(Cargo& cargoStore) const;

  /** Check if production is possible */
  bool canProduce(const Cargo& cargoStore) const;

  /** Add another production option */
  void addProductionOption(const ProductionOption& option);

  /** Set the active production option.
 	 * Note this one needs to be part of the Factory's own ProductionOptions
 	 */
  void setProductionOption(const ProductionOption& option);

  /** Compare factories to eachother. Factories are equal if the
 	 * have exactly the same ProductionOptions.
 	 */
  bool operator==(const Factory &that) const;

private:
  std::vector<ProductionOption> options;
  std::vector<ProductionOption>::iterator productionPlan;
};

#endif //H_FACTORY
