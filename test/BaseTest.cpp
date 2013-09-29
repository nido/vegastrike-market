#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "BaseTest.hpp"

void BaseTest::setUp()
{
}

void BaseTest::tearDown()
{
}


void BaseTest::testaddCargo()
{
}

void BaseTest::testaddFactory()
{
}

void BaseTest::testdelCargo()
{
}


CppUnit::Test* BaseTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "BaseTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
//			"testFunction",
//			&BaseTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testaddCargo", &BaseTest::testaddCargo));

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testaddFactory", &BaseTest::testaddFactory));

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testdelCargo", &BaseTest::testdelCargo));

	return suiteOfTests;
}
