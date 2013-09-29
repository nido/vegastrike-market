#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "FactoryTest.hpp"

void FactoryTest::setUp()
{
        this->intype = CargoType("in", "test", 1,1,1);
        this->outtype = CargoType("out", "test", 1, 1,1);

        this->input = Cargo();
        this->output = Cargo();
        this->cargo = Cargo();

        this->input.addCargo(intype, 1);
        this->output.addCargo(outtype, 1);
        this->cargo.addCargo(intype, 2);

        this->po = ProductionOption(input, output);
        this->bigpo = ProductionOption(cargo, output);

	this->factory = Factory();
}

void FactoryTest::tearDown()
{
}


void FactoryTest::testcanProduce()
{
	// empty factory cannot produce
	CPPUNIT_ASSERT(this->factory.canProduce(&cargo) == false);

	this->factory.addProductionOption(bigpo);
	// cannot produce with not enough goods
	CPPUNIT_ASSERT(this->factory.canProduce(&input) == false);
	// cannot produce without the right goods
	CPPUNIT_ASSERT(this->factory.canProduce(&output) == false);

	this->factory.addProductionOption(po);
	// can produce with just enough input goods
	CPPUNIT_ASSERT(this->factory.canProduce(&input) == true);
	// can produce with enough input goods
	CPPUNIT_ASSERT(this->factory.canProduce(&cargo) == true);
}

void FactoryTest::testProduce()
{
	this->factory.addProductionOption(po);
	// produce with enough goods
	this->factory.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 1);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 1);
	// produce with just enough goods
	this->factory.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);
	// Production does nothing when impossible
	this->factory.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);
}

CppUnit::Test* FactoryTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "FactoryTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
//			"testFunction",
//			&FactoryTest::testFunction));

	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
			"testcanProduce", &FactoryTest::testcanProduce));

	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
			"testProduce", &FactoryTest::testProduce));

	return suiteOfTests;
}
