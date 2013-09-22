#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTest.hpp"
void CargoTest::setUp(){}
void CargoTest::tearDown(){}

CppUnit::Test* CargoTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
//			"testFunction",
//			&CargoTest::testFunction));
	return suiteOfTests;
}
