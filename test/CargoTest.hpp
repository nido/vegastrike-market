#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Cargo.hpp"

class CargoTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	void testCompare();
	void testEqual();
	void testAddCargo();
	void testDelCargo();
	void testGetCount();
	static CppUnit::Test* suite();
private:
	Cargo* cargop;
	Cargo cargoi;
	CargoType* type;
};
