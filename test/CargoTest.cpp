#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTest.hpp"

#include "Cargo.hpp"

void CargoTest::setUp(){
	this->type = new CargoType("type", "category", 1.0, 2.0);
	this->cargop = new Cargo(type, 1);
	this->cargoi = Cargo();
}
void CargoTest::tearDown(){
	delete this->cargop;
	delete this->type;
}

void CargoTest::testCompare(){
	CargoType* type1 = new CargoType("cargotype2", "category2", 2.0, 3.0);
	CargoType* type2 = new CargoType("cargotype3", "category2", 2.0, 3.0);
	CargoType* type3 = new CargoType("cargotype2", "category3", 2.0, 3.0);

	Cargo one = Cargo(type1, 1);
	Cargo two = Cargo(type1, 2);
	// check the same cargo type
	bool result = one < two;
	CPPUNIT_ASSERT(result == true);
	result = two < one;
	CPPUNIT_ASSERT(result == false);
	// check different cargo names
	two = Cargo(type2, 1);
	result = one < two;
	CPPUNIT_ASSERT(result == true);
	result = two < one;
	CPPUNIT_ASSERT(result == false);
	// check different cargo types
	two = Cargo(type3, 1);
	result = one < two;
	CPPUNIT_ASSERT(result == true);
	result = two < one;
	CPPUNIT_ASSERT(result == false);
	delete type1;
	delete type2;
	delete type3;
}

void CargoTest::testEqual(){
	CargoType* type1 = new CargoType("cargotype2", "category2", 2.0, 3.0);
	CargoType* type2 = new CargoType("cargotype3", "category2", 2.0, 3.0);
	CargoType* type3 = new CargoType("cargotype2", "category3", 2.0, 3.0);

	Cargo one = Cargo(type1, 1);
	Cargo two = Cargo(type1, 2);

	bool result = one == two;
	CPPUNIT_ASSERT(result == true);

	two = Cargo(type2, 1);
	result = one == two;
	CPPUNIT_ASSERT(result == false);

	two = Cargo(type3, 1);
	result = one == two;
	CPPUNIT_ASSERT(result == false);
	delete type1;
	delete type2;
	delete type3;
}

void CargoTest::testAddCargo(){
	this->cargop->addCargo(1);
	CPPUNIT_ASSERT(this->cargop->getCount() == 2);
}
void CargoTest::testDelCargo(){
	this->cargop->delCargo(1);
	CPPUNIT_ASSERT(this->cargop->getCount() == 0);
}
void CargoTest::testGetCount(){
	CPPUNIT_ASSERT(this->cargop->getCount() == 1);
}

CppUnit::Test* CargoTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testCompare",
			&CargoTest::testCompare));
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testEqual",
			&CargoTest::testEqual));
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testAddCargo",
			&CargoTest::testAddCargo));
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testDelCargo",
			&CargoTest::testDelCargo));
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testGetCount",
			&CargoTest::testGetCount));
	return suiteOfTests;
}
