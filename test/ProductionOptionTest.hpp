#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>
#include "ProductionOption.hpp"

class ProductionOptionTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	static CppUnit::Test* suite();
	void smokeTest();
	void CanProduceTest();
	void ProduceTest();
private:
	CargoType *input;
	CargoType *output;
	CargoHold stuff1;
        CargoHold stuff2;
        CargoHold *stuff3;
	ProductionOption* o1;
	ProductionOption* o10;
};

