#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class @template@Test : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	static CppUnit::Test* suite();
};
