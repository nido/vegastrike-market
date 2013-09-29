#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class @template@ : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
@headercode@
	static CppUnit::Test* suite();
};
