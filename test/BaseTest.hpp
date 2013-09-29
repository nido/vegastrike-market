#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class BaseTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testaddCargo();
	void testaddFactory();
	void testdelCargo();
	static CppUnit::Test* suite();
};
