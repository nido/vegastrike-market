#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Base.hpp"

class BaseTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testaddCargo();
	void testaddFactory();
	void testdelCargo();
	void testdelFactory();
	void testgetFactories();
	void testProcess();
	void testgetCargo();
	static CppUnit::Test* suite();
private:
	Base base;
	Cargo cargo;
	Factory factory1;
	Factory factory2;
};
