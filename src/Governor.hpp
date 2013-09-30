#ifndef H_GOVERNOR
#define H_GOVERNOR

class Governor;

/** Dude running the station */
class Governor{
public:
	/** Create a (random) Governor */
	Governor();

	/** Delete a Governor */
	~Governor();

	/** Add a Governor to a base. Note this also changes his cargo 
	 */
	void setBase(Base* base);

	/** Do something with the state of the factories */
	void PrepareFactories();

private:
	/** Pointer to the base it is associated with */
	Base* base;
	/** Pointer to the cargo it is responsible for.
	 * Note that under initial circumstances, this should always be
	 * the cargo from the base.
	 */
	Cargo* cargo;
	/** Credits available to the Governor */
	float credits;
};
#endif //H_GOVERNOR
