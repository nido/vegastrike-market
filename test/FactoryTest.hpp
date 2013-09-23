#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Cargo.hpp"
#include "CargoHold.hpp"
#include "ProductionOption.hpp"
#include "Factory.hpp"

class FactoryTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();
	void testCanProduce();
	void testProduce();
	void smokeTest();
	static CppUnit::Test* suite();
private:
	CargoType* inputType;
	CargoType* outputType;
	Cargo in1;
	Cargo out1;
	Cargo in10;
	Cargo out10;
	CargoHold input1;
	CargoHold output1;
	CargoHold input10;
	CargoHold output10;
	CargoHold hold;
	ProductionOption produce1;
	ProductionOption produce10;
	Factory factory;
};
