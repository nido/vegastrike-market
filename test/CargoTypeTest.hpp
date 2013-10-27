#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoType.hpp"

class CargoTypeTest : public CppUnit::TestFixture
{
    public:
        void setUp();
        void tearDown();

        void testoperatorEquals();
        void testoperatorLessThen();
        void testgetBasePrice();
        void testgetName();
        void testgetXML();
        static CppUnit::Test *suite();

    private:
        CargoType one;
        CargoType two;
        CargoType three;
};
