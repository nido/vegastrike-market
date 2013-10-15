#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "EconomyTest.hpp"

void EconomyTest::setUp()
{
}

void EconomyTest::tearDown()
{
}


void EconomyTest::testaddBase()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void EconomyTest::testdelBase()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void EconomyTest::testgetFactories()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}

void EconomyTest::testtick()
{
	//TODO: Implement test
	CPPUNIT_ASSERT(false);
}


CppUnit::Test* EconomyTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "EconomyTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
//			"testFunction",
//			&EconomyTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
			"testaddBase", &EconomyTest::testaddBase));

	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
			"testdelBase", &EconomyTest::testdelBase));

	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
			"testgetFactories", &EconomyTest::testgetFactories));

	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
			"testtick", &EconomyTest::testtick));

	return suiteOfTests;
}
