#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "EconomyTest.hpp"

void EconomyTest::setUp()
{
	this->e = new Economy();
	this->b = new Base();
}

void EconomyTest::tearDown()
{
	delete this->e;
	delete this->b;
}


void EconomyTest::testaddBase()
{
	this->e->addBase(*this->b);
	CPPUNIT_ASSERT(false);
}

void EconomyTest::testdelBase()
{
	//TODO: Implement test
	this->e->addBase(*this->b);
	this->e->delBase(*this->b);
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
