#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTypeTest.hpp"

void CargoTypeTest::setUp()
{
	one = CargoType("1", "1", 0, 0,0);
	two = CargoType("2", "1", 0, 0,0);
	three = CargoType("1", "2", 0, 0,0);
	
}

void CargoTypeTest::tearDown()
{
}


void CargoTypeTest::testoperatorEquals()
{
	// positive case
	CPPUNIT_ASSERT(one == one);
	// negative case
	CPPUNIT_ASSERT((one == two) == false);
}

void CargoTypeTest::testoperatorLessThen()
{
	// positive case
	CPPUNIT_ASSERT(one < two);
	// negative case
	CPPUNIT_ASSERT((one < one) == false);
	// cargo catagory difference case
	CPPUNIT_ASSERT(one < three);
}

void CargoTypetestgetBasePrice()
{
	CargoType type = CargoType("yay", "cata/gory", 1, 2, 3);
	CPPUNIT_ASSERT(type.getBasePrice() == 3);
	type = CargoType("yay", "cata/gory", 1, 2, 0);
	CPPUNIT_ASSERT(type.getBasePrice() == 0);
}

CppUnit::Test* CargoTypeTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoTypeTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
//			"testFunction",
//			&CargoTypeTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testoperatorEquals", &CargoTypeTest::testoperatorEquals));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testoperatorLessThen", &CargoTypeTest::testoperatorLessThen));

	return suiteOfTests;
}
