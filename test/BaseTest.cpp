#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <algorithm>
#include <vector>

#include "BaseTest.hpp"

void BaseTest::setUp()
{
        CargoType::iterator intype1 = CargoType("in1", "test", 1,1,1).getIterator();
        CargoType::iterator intype2 = CargoType("in2", "test", 1,1,1).getIterator();
        CargoType::iterator outtype = CargoType("out", "test", 1, 1,1).getIterator();


        Cargo input1 = Cargo();
        Cargo input2 = Cargo();
        Cargo output = Cargo();
        this->cargo = Cargo();
        input1.addCargo(intype1, 1);
        input2.addCargo(intype2, 1);
        output.addCargo(outtype, 1);
        this->cargo.addCargo(intype2, 1);
        this->cargo.addCargo(intype1, 5);
        ProductionOption po1 = ProductionOption(input1, output);
        ProductionOption po2 = ProductionOption(input2, output);
	this->factory1 = Factory();
	this->factory1.addProductionOption(po1);
	this->factory2 = Factory();
	this->factory2.addProductionOption(po2);
	this->base = Base();
}

void BaseTest::tearDown()
{
}

void BaseTest::testaddCargo()
{
	this->base.addCargo(this->cargo);
	CPPUNIT_ASSERT(*(this->base.getCargo()) == this->cargo);
}

void BaseTest::testaddFactory()
{
	this->base.addFactory(factory1);
	std::vector<Factory> list = this->base.getFactories();
	std::vector<Factory>::iterator iter = std::find(list.begin(), list.end(), factory1);
	CPPUNIT_ASSERT(iter != list.end());
	CPPUNIT_ASSERT(*iter == factory1);
}

void BaseTest::testdelCargo()
{
	this->base.addCargo(this->cargo);
	this->base.delCargo(this->cargo);
	//empty now
	CPPUNIT_ASSERT(*(this->base.getCargo()) == Cargo());
}

void BaseTest::testdelFactory()
{
	this->base.addFactory(factory1);
	this->base.delFactory(factory1);
	std::vector<Factory> list = this->base.getFactories();
	std::vector<Factory>::iterator iter = std::find(list.begin(), list.end(), factory1);
	// factory cannot be found
	CPPUNIT_ASSERT(iter == list.end());
}

void BaseTest::testgetFactories()
{
        std::vector<Factory> list = this->base.getFactories();
	// empty
	CPPUNIT_ASSERT(list == std::vector<Factory>());
	this->base.addFactory(factory1);
	list = this->base.getFactories();
	CPPUNIT_ASSERT(list.size() == 1);
	this->base.addFactory(factory1);
	list = this->base.getFactories();
	CPPUNIT_ASSERT(list.size() == 2);
	this->base.addFactory(factory2);
	list = this->base.getFactories();
	CPPUNIT_ASSERT(list.size() == 3);

}

void BaseTest::testProcess()
{
        CargoType::iterator intype1 = CargoType("in1", "test", 1,1,1).getIterator();
	this->base.addFactory(factory1);
	this->base.addCargo(cargo);
	Cargo* basecargo = this->base.getCargo();
	CPPUNIT_ASSERT(basecargo->getCount(intype1) == 5);
	this->base.Process();
	CPPUNIT_ASSERT(basecargo->getCount(intype1) == 4);
	this->base.addFactory(factory1);
	this->base.Process();
	CPPUNIT_ASSERT(basecargo->getCount(intype1) == 2);
}

void BaseTest::testgetCargo()
{
	this->base.addCargo(this->cargo);
	CPPUNIT_ASSERT(*(this->base.getCargo()) == this->cargo);
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

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testdelFactory", &BaseTest::testdelFactory));

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testgetFactories", &BaseTest::testgetFactories));

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testProcess", &BaseTest::testProcess));

	suiteOfTests->addTest( new CppUnit::TestCaller<BaseTest>(
			"testgetCargo", &BaseTest::testgetCargo));

	return suiteOfTests;
}
