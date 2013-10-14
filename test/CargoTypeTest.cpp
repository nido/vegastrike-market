#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTypeTest.hpp"

void CargoTypeTest::setUp()
{
}

void CargoTypeTest::tearDown()
{
}


void CargoTypeTest::testgetBasePrice()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void CargoTypeTest::testgetName()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void CargoTypeTest::testgetRandomCargoType()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void CargoTypeTest::testgetXML()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void CargoTypeTest::testoperatorEquals()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void CargoTypeTest::testoperatorLessThen()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}


CppUnit::Test* CargoTypeTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoTypeTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
//			"testFunction",
//			&CargoTypeTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testgetBasePrice", &CargoTypeTest::testgetBasePrice));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testgetName", &CargoTypeTest::testgetName));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testgetRandomCargoType", &CargoTypeTest::testgetRandomCargoType));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testgetXML", &CargoTypeTest::testgetXML));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testoperatorEquals", &CargoTypeTest::testoperatorEquals));

	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
			"testoperatorLessThen", &CargoTypeTest::testoperatorLessThen));

	return suiteOfTests;
}
