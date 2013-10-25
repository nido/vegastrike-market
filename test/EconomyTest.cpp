#include <algorithm>
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
	CPPUNIT_ASSERT(this->e->getBases().empty() == false);
}

void EconomyTest::testdelBase()
{
	//TODO: Implement test
	this->e->addBase(*this->b);
	CPPUNIT_ASSERT(this->e->getBases().empty() == false);
	this->e->delBase(*this->b);
	CPPUNIT_ASSERT(this->e->getBases().empty());
}

void EconomyTest::testgetBases()
{
	this->e->addBase(*this->b);
	CPPUNIT_ASSERT(std::find(this->e->getBases().begin(), this->e->getBases().end(), *this->b) != this->e->getBases().end());
}

void EconomyTest::testtick()
{
	// ready an entire economy
	Cargo c = Cargo();
	c.addCargo(CargoType(), 1);

	Cargo c2 = Cargo();
	c2.addCargo(CargoType("test2", "debug", 1,2,3), 2);

	ProductionOption o = ProductionOption(c, c2);
	Factory f=Factory();
	f.addProductionOption(o);
	Base ba = Base();
	ba.addFactory(f);

	ba.addCargo(c);

	e->addBase(ba);

	CPPUNIT_ASSERT(e->getBases().begin()->getCargo().getCount(CargoType()) == 1);
	e->tick();
	CPPUNIT_ASSERT(e->getBases().begin()->getCargo().getCount(CargoType()) == 0);
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
			"testgetBases", &EconomyTest::testgetBases));

	suiteOfTests->addTest( new CppUnit::TestCaller<EconomyTest>(
			"testtick", &EconomyTest::testtick));

	return suiteOfTests;
}
