#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

#include "CargoHoldTest.hpp"
#include "CargoHold.hpp"

void CargoHoldTest::setUp()
{
	this->stuff1 = new CargoType("stuff1","",0,0);
	this->stuff2 = new CargoType("stuff2","",0,0);
	this->stuff3 = new CargoType("stuff3","",0,0);
	this->in1 = Cargo(this->stuff1, 100);
	this->in2 = Cargo(this->stuff2, 100);
	this->in3 = Cargo(this->stuff3, 100);
	std::vector<Cargo> cargo2;
	std::vector<Cargo> cargo3;
	cargo2.push_back(this->in1);
	cargo2.push_back(this->in2);
	cargo3.push_back(this->in1);
	cargo3.push_back(this->in3);

	this->hold1 = CargoHold();
	this->hold2 = CargoHold(cargo2);
	this->hold3 = CargoHold(cargo3);
}

void CargoHoldTest::tearDown(){
	delete stuff1;
	delete stuff2;
	delete stuff3;
}

void CargoHoldTest::testAddCargo()
{
	// hold 1 is empty
	this->hold1.addCargo(stuff1, 5);
	// hold 1 has 5 stuff1
	this->hold1.addCargo(stuff1, 5);
	// hold 1 has 10 stuff1
	this->hold1.addCargo(in1);
	// hold 1 has 110 stuff1
	// hold 2 has 100 stuff1, 100 stuff2
	this->hold1.addCargo(hold2);
	// hold 1 has 210 stuff1, 100 stuff2
	Cargo* result1 = hold1.findCargo(stuff1);
	Cargo* result2 = hold1.findCargo(stuff2);
	Cargo* result3 = hold1.findCargo(stuff3);
	CPPUNIT_ASSERT(result1->quantity == 210);
	CPPUNIT_ASSERT(result2->quantity == 100);
	CPPUNIT_ASSERT(result3 == NULL);
}

void CargoHoldTest::testDelCargo()
{
	bool result;
	// hold 1 is empty.
	// hold 2 has 100 stuff1, 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(stuff1, 150);
	CPPUNIT_ASSERT(result == false);

	result = hold2.delCargo(stuff1, 50);
	CPPUNIT_ASSERT(result == true);

	// hold 1 is empty.
	// hold 2 has 50 stuff1, 100 stuff2
	CPPUNIT_ASSERT(hold2.findCargo(stuff1)->quantity == 50);
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(in1);
	CPPUNIT_ASSERT(result == false);

	// hold 1 is empty.
	// hold 2 has 50 stuff1, 100 stuff2
	CPPUNIT_ASSERT(hold2.findCargo(stuff1)->quantity == 50);
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(stuff1, 50);
	CPPUNIT_ASSERT(result == true);

	// hold 1 is empty.
	// hold 2 has 100 stuff2
	CPPUNIT_ASSERT(hold2.findCargo(stuff1) == NULL);
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(stuff1, 50);
	CPPUNIT_ASSERT(result == false);

	// hold 1 is empty.
	// hold 2 has 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(hold3);
	CPPUNIT_ASSERT(result == false);

	// hold 1 is empty.
	// hold 2 has 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	hold2.addCargo(hold3);

	// hold 1 is empty.
	// hold 2 has 100 stuff1, 100 stuff2, 100 stuff3
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(hold3);
	CPPUNIT_ASSERT(result == true);

	// hold 1 is empty.
	// hold 2 has 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold2.delCargo(hold3);
	CPPUNIT_ASSERT(result == false);

	// hold 1 is empty.
	// hold 2 has 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	hold1.addCargo(hold3);
	// hold 1 has 100 stuff1, 100 stuff3
	// hold 2 has 50 stuff1, 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	hold1.addCargo(hold3);
	// hold 1 has 200 stuff1, 200 stuff3
	// hold 2 has 50 stuff1, 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
	result = hold3.delCargo(hold1);
	CPPUNIT_ASSERT(result == false);
	// hold 1 has 200 stuff1, 200 stuff3
	// hold 2 has 50 stuff1, 100 stuff2
	// hold 3 has 100 stuff1, 100 stuff3
}
	

CppUnit::Test* CargoHoldTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoHoldTest" );

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoHoldTest>(
			"testAddCargo", 
			&CargoHoldTest::testAddCargo) );
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoHoldTest>(
			"testDelCargo", 
			&CargoHoldTest::testDelCargo) );
	return suiteOfTests;
}
