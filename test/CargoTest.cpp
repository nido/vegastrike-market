#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTest.hpp"

#include "Cargo.hpp"

void CargoTest::setUp(){
}
void CargoTest::tearDown(){
}

void CargoTest::testCompare(){
	CargoType* type = new CargoType("cargotype", "category", 2.0, 3.0);
	Cargo one = Cargo(type, 1);
	Cargo two = Cargo(type, 2);
	bool result = one < two;
	CPPUNIT_ASSERT(result);
	delete type;
}

CppUnit::Test* CargoTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "CargoTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
			"testCompare",
			&CargoTest::testCompare));
	return suiteOfTests;
}
