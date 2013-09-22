#include <vector>

//TODO: make this vegastrike's version. This file contains the Cargo
//      class; and use of vegacargo in the economy would make it a lot
//      easier to integrate the two at a later date. Still, that leaves
//      us with requiring a vegastrike_dir variable of sorts and getting
//      people to check out all of vegastrike for this, or an altered
//      version for here for the moment to make it work with sortof
//      vegacargo
#include "ProductionOptionTest.hpp"
#include "ProductionOption.hpp"

void ProductionOptionTest::setUp()
{
        this->input = new CargoType( "input", "test/test", 0.0, 0.0);
        this->output = new CargoType( "output", "test/test", 0.0, 0.0);

	std::vector<Cargo> vstuff1 = std::vector<Cargo>();
	std::vector<Cargo> vstuff2 = std::vector<Cargo>();
	std::vector<Cargo> vstuff3 = std::vector<Cargo>();

	vstuff1.push_back(Cargo(input, 1));
	vstuff2.push_back(Cargo(output, 1));
	vstuff3.push_back(Cargo(input, 10));

	this->stuff1 = CargoHold(vstuff1);
	this->stuff2 = CargoHold(vstuff2);
	this->stuff3 = new CargoHold(vstuff3);

	this->o1 = new ProductionOption(stuff1, stuff2);
	this->o10 = new ProductionOption(*stuff3, stuff2);

}

void ProductionOptionTest::tearDown(){
	delete stuff3;
	delete o1;
	delete o10;
	delete input;
	delete output;
}

void ProductionOptionTest::smokeTest(){
	for(unsigned int i=1; i < 10; i++) {
		this->o1->Produce(stuff3);
		Cargo* in = this->stuff3->findCargo(this->input);
		Cargo* out = this->stuff3->findCargo(this->output);
		CPPUNIT_ASSERT(in->getCount() == (10 - i));
		CPPUNIT_ASSERT(out->getCount() == i);
	}
	this->o1->Produce(stuff3);
	CPPUNIT_ASSERT(this->stuff3->findCargo(this->input) == NULL);
	return;
}

void ProductionOptionTest::CanProduceTest(){
	// stuff3 has 10 input, stuff1 has 1 input
	CPPUNIT_ASSERT(o1->CanProduce(stuff3) == true);
	CPPUNIT_ASSERT(o1->CanProduce(&stuff1) == true);
	CPPUNIT_ASSERT(o10->CanProduce(stuff3) == true);
	// can't produce, not enough goods
	CPPUNIT_ASSERT(o10->CanProduce(&stuff1) == false);
	// can't produce, no good available
	CPPUNIT_ASSERT(o10->CanProduce(&stuff2) == false);
}

void ProductionOptionTest::ProduceTest(){
}

CppUnit::Test* ProductionOptionTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ProductionOptionTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"smokeTest", &ProductionOptionTest::smokeTest) );
	suiteOfTests->addTest( new CppUnit::TestCaller<ProductionOptionTest>(
			"CanProduceTest", &ProductionOptionTest::CanProduceTest) );
	return suiteOfTests;
}
