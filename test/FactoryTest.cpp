#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <vector>
#include <assert.h>

#include "FactoryTest.hpp"
#include "Factory.hpp"

#include "Cargo.hpp"
#include "CargoHold.hpp"

void FactoryTest::setUp(){
	this->inputType = new CargoType("input", "test/test", 1.0, 2.0);
	this->outputType = new CargoType("output", "test/test", 1.0, 2.0);
	this->in1 = Cargo(inputType, 1);
	this->out1 = Cargo(outputType, 1);
	this->in10 = Cargo(inputType, 10);
	this->out10 = Cargo(outputType, 10);
	this->input1 = CargoHold();
	this->output1 = CargoHold();
	this->input10 = CargoHold();
	this->output10 = CargoHold();
	this->hold = CargoHold();
	this->input1.addCargo(in1);
	this->output1.addCargo(out1);
	this->input10.addCargo(in10);
	this->output10.addCargo(out10);
	this->produce1 = ProductionOption(input1, output1);
	this->produce10 = ProductionOption(input10, output10);
	std::vector<ProductionOption> pos = std::vector<ProductionOption>();
	pos.push_back(this->produce1);
	pos.push_back(this->produce10);
	this->factory = Factory(pos);
}

void FactoryTest::tearDown(){
	delete this->inputType;
	delete this->outputType;
}

void FactoryTest::testCanProduce(){
	CPPUNIT_ASSERT(this->factory.CanProduce(&this->hold) == false);
	assert(this->factory.CanProduce(&this->hold) == false);
	this->hold.addCargo(in1);
	CPPUNIT_ASSERT(this->factory.CanProduce(&this->hold) == true);
	this->hold.delCargo(in1);
	CPPUNIT_ASSERT(this->factory.CanProduce(&this->hold) == false);
}

void FactoryTest::testProduce(){
	Cargo* found;
	this->hold.addCargo(in1);
	found = this->hold.findCargo(inputType);
	assert(found != NULL);
	// produce cargo
	this->factory.Produce(&this->hold);
	found = this->hold.findCargo(inputType);
	CPPUNIT_ASSERT(found == NULL);
	found = this->hold.findCargo(outputType);
	CPPUNIT_ASSERT(found->getCount() == 1);
}


void FactoryTest::smokeTest(){
	CargoType *input = new CargoType( "input", "test/test", 0.0, 0.0);
	CargoType *output = new CargoType( "output", "test/test", 0.0, 0.0);

	std::vector<Cargo> stuff1 = std::vector<Cargo>();
	std::vector<Cargo> stuff2 = std::vector<Cargo>();
	CargoHold *stuff3 = new CargoHold(std::vector<Cargo>());
	std::vector<Cargo> stuff4 = std::vector<Cargo>();
	std::vector<Cargo> stuff5 = std::vector<Cargo>();
	std::vector<ProductionOption> options = std::vector<ProductionOption>();

	stuff1.push_back(Cargo(input, 1));
	stuff2.push_back(Cargo(output, 1));
	stuff3->addCargo(input, 20);
	stuff4.push_back(Cargo(input, 100));
	stuff5.push_back(Cargo(output, 100));

	ProductionOption o1 = ProductionOption(stuff1, stuff2);
	ProductionOption o2 = ProductionOption(stuff4, stuff5);
	options.push_back(o1);
//	options.push_back(o2);

	Factory *f = new Factory(options);

	for(unsigned int i=1; i < 20; i++) {
		f->Produce(stuff3);
		Cargo* in = stuff3->findCargo(input);
		Cargo* out = stuff3->findCargo(output);
		CPPUNIT_ASSERT(in->getCount() == (20 - i));
		CPPUNIT_ASSERT(out->getCount() == i);
	}
	f->Produce(stuff3);
	CPPUNIT_ASSERT(stuff3->findCargo(input) == NULL);	

	delete stuff3;
	delete f;
	delete input;
	delete output;
}

CppUnit::Test* FactoryTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "FactoryTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
			"smokeTest",
			&FactoryTest::smokeTest));
	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
			"testCanProduce",
			&FactoryTest::testCanProduce));
	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
			"testProduce",
			&FactoryTest::testProduce));
	return suiteOfTests;
}
