#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoType.hpp"

class CargoTypeTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testoperatorEquals();
	void testoperatorLessThen();
	static CppUnit::Test* suite();
private:
	CargoType one;
	CargoType two;
	CargoType three;
};
