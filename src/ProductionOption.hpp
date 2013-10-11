#ifndef H_PRODUCTIONOPTION
#define H_PRODUCTIONOPTION
/*
 * ProductionOption for producing goods, v 0.0.4
 * @author peter.schaefer@gmail.com
 */

#include <stdbool.h>

#include "Cargo.hpp"

class ProductionOption;

/** One of the possibilities for a factory to produce.
 *
 * Factories are sometimes able to make different quantities of products
 * depending on available inputs. A ProductionOption 
 */
class ProductionOption {

public:
	ProductionOption();
	/** Create a new ProductionOption which turns consumes Cargo into
	 * produces Cargo. consumes and produces becomes owned by the
	 * ProductionOption. */
	ProductionOption(Cargo* consumes, Cargo* produces);

	/** Delete the ProductionOption and its consumes and produces.
	 */
	~ProductionOption();

	/** (if possible) Do produce */
	void Produce(Cargo *cargoStore);

	/** determine whether production is possible */
	bool canProduce(const Cargo *cargoStore) const;
	/** check equality of two ProductionOptions */
	bool operator==( const ProductionOption &that ) const;
private:
	/** Cargo consumed by production. */
	Cargo* consumes;

	/** Cargo produced by production. */
	Cargo* produces;
};
#endif // H_PRODUCTIONOPTION
