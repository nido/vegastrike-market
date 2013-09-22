#include <vector>
#include <assert.h>

//TODO: make this vegastrike's version. This file contains the Cargo
//      class; and use of vegacargo in the economy would make it a lot
//      easier to integrate the two at a later date. Still, that leaves
//      us with requiring a vegastrike_dir variable of sorts and getting
//      people to check out all of vegastrike for this, or an altered
//      version for here for the moment to make it work with sortof
//      vegacargo
#include "ProductionOptionTest.hpp"
#include "ProductionOption.hpp"

#define TURNS 10

void ProductionOptionTest::setUp()
{
        this->input = new CargoType( "input", "test/test", 0.0, 0.0);
        this->output = new CargoType( "output", "test/test", 0.0, 0.0);

	this->stuff1 = std::vector<Cargo>();
	this->stuff2 = std::vector<Cargo>();
	this->stuff3 = new std::vector<Cargo>();

	this->stuff1.push_back(Cargo(input, 1));
	this->stuff2.push_back(Cargo(output, 1));
	this->stuff3->push_back(Cargo(input, TURNS));

	this->o = new ProductionOption(stuff1, stuff2);
}

void ProductionOptionTest::tearDown(){
	delete stuff3;
	delete o;
	delete input;
	delete output;
}

void ProductionOptionTest::smokeTest(){
	for(unsigned int i=1; i <= TURNS; i++) {
		o->Produce(stuff3);
		Cargo* in = findCargo(this->input, this->stuff3);
		Cargo* out = findCargo(this->output, this->stuff3);
		assert(in->quantity == (TURNS - i));
		assert(out->quantity == i);
	}
	return;
}

CppUnit::Test* ProductionOptionTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ProductionOptionTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"smokeTest", &ProductionOptionTest::smokeTest) );
	return suiteOfTests;
}
