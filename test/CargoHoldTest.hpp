#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

#include "CargoHold.hpp"
#include "Cargo.hpp"


class CargoHoldTest : public CppUnit::TestFixture  {
public:
	CargoType* stuff1;
	CargoType* stuff2;
	CargoType* stuff3;
	Cargo in1;
	Cargo in2;
	Cargo in3;
	CargoHold hold1;
	CargoHold hold2;
	CargoHold hold3;
	void setUp();
	void tearDown();
	void testAddCargo();
	void testDelCargo();
	static CppUnit::Test* suite();
};
