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
private:
	CargoType *input;
	CargoType *output;
	std::vector<Cargo> stuff1;
        std::vector<Cargo> stuff2;
        std::vector<Cargo> *stuff3;
	ProductionOption* o;
};

