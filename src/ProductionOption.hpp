#ifndef H_PRODUCTIONOPTION
#define H_PRODUCTIONOPTION

#include "Cargo.hpp"

class ProductionOption;

/** One of the possibilities for a factory to produce.
 *
 * Factories are sometimes able to make different quantities of products
 * depending on available inputs. A ProductionOption
 */
class ProductionOption {

public:
  /** Ability to turn nothing into nothing */
  ProductionOption();

  /** constructor for turning consumes into produces
   * @param consumes what is consumes by production
   * @param produces resulting Cargo from this transaction
   */
  ProductionOption(const Cargo& consumes, const Cargo& produces);

  /** Delete the ProductionOption and its consumes and produces.
 	 */
  ~ProductionOption();

  /** (if possible) Do produce.
   * @param cargoStore Cargo to draw from and store to */
  void Produce(Cargo& cargoStore) const;

  /** determine whether production is possible
   * @param cargoStore the Cargo on which to base this decision
   * @return true when production is possible, false otherwise
  */
  bool canProduce(const Cargo& cargoStore) const;

  /** check equality of two ProductionOptions
   * @param that the ProductionOption to compare to
   * @return true when equal, false otherwise
  */
  bool operator==(const ProductionOption& that) const;

private:

  /** Cargo consumed by production. */
  Cargo consumes;

  /** Cargo produced by production. */
  Cargo produces;
};
#endif // H_PRODUCTIONOPTION
