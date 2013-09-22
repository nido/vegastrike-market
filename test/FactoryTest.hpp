#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class FactoryTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	void smokeTest();
	static CppUnit::Test* suite();
};
