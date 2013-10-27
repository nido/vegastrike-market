#ifndef H_BASE
#define H_BASE

#include <vector>

#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Factory.hpp"

class Base;

/** A single factory with its own cargo reserve and (several) ProductionOptions
 *
 */
class Base
{
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

        /** return a reference to this Base cargo
         * @return this Base Cargo
         */
        const Cargo& getCargo() const;

        /** Process all activities on this base
         */
        void Process();

        /** Compare this base to another
         * @param that the Base to compare to
         * @return true when equal, false otherwise
         */
        bool operator==(const Base& that) const;

    private:
        /** The Factories on this Base */
        std::vector<Factory> factories;

        /** The Cargo on this Base */
        Cargo cargoStore;
};
#endif                                            //H_BASE
