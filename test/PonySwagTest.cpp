#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "PonySwagTest.hpp"

void PonySwagTest::setUp()
{
}

void PonySwagTest::tearDown()
{
}



CppUnit::Test* PonySwagTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "PonySwagTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<PonySwagTest>(
//			"testFunction",
//			&PonySwagTest::testFunction));

	
	return suiteOfTests;
}
