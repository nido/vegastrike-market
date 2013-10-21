#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoType.hpp"
#include "Cargo.hpp"

class xmlTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	void testCargoType();
	void testCargo();
	static CppUnit::Test* suite();
private:
	CargoType t;
	CargoType t2;
	Cargo c;
};
