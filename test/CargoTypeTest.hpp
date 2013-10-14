#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class CargoTypeTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testgetBasePrice();
	void testgetName();
	void testgetRandomCargoType();
	void testgetXML();
	void testoperatorEquals();
	void testoperatorLessThen();
	static CppUnit::Test* suite();
};
