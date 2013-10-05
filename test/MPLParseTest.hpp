#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

class MPLParseTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testParse();
	void testParseFile();
	void testParseLine();
	static CppUnit::Test* suite();
};
