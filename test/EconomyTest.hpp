#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

#include "Economy.hpp"

class EconomyTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testaddBase();
	void testdelBase();
	void testgetFactories();
	void testtick();
	static CppUnit::Test* suite();
private:
	Economy* e;
	Base* b;
};
