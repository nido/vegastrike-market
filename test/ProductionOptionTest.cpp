
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ProductionOptionTest.hpp"

void ProductionOptionTest::setUp()
{
	this->intype = CargoType("in", "test", 1,1,1).getIterator();
	this->outtype = CargoType("out", "test", 1, 1,1).getIterator();

	this->input = Cargo();
	this->output = Cargo();
	this->cargo = Cargo();

	this->input.addCargo(intype, 1);
	this->output.addCargo(outtype, 1);
	this->cargo.addCargo(intype, 2);

	Cargo* in1 = new Cargo();
	Cargo* in2 = new Cargo();
	Cargo* out1 = new Cargo();
	Cargo* out2 = new Cargo();

	in1->addCargo(intype, 1);
	out1->addCargo(outtype, 1);
	in2->addCargo(intype, 2);
	out2->addCargo(outtype, 1);

	this->po = ProductionOption(in1, out1);
	this->bigpo = ProductionOption(in2, out2);
}

void ProductionOptionTest::tearDown()
{
}


void ProductionOptionTest::testCanProduce()
{
	CPPUNIT_ASSERT(po.canProduce(&cargo) == true);
	CPPUNIT_ASSERT(bigpo.canProduce(&input) == false);
	CPPUNIT_ASSERT(po.canProduce(&output) == false);
}

void ProductionOptionTest::testProduce()
{
	// impossible production test
	bigpo.Produce(&input);
	po.Produce(&output);
	CPPUNIT_ASSERT(input.getCount(intype) == 1);
	CPPUNIT_ASSERT(output.getCount(outtype) == 1);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 2);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 0);
	

	po.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 1);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 1);

	po.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);

	po.Produce(&cargo);
	CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
	CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);


}

void ProductionOptionTest::testoperatorEquals()
{
	CPPUNIT_ASSERT(bigpo == bigpo);
	CPPUNIT_ASSERT((po == bigpo) == false);
}

CppUnit::Test* ProductionOptionTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ProductionOptionTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
//			"testFunction",
//			&ProductionOptionTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"testCanProduce", &ProductionOptionTest::testCanProduce));

	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"testProduce", &ProductionOptionTest::testProduce));

	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"testoperatorEquals", &ProductionOptionTest::testoperatorEquals));

	return suiteOfTests;
}
