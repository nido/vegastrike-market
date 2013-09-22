#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

#include "FactoryTest.hpp"
#include "Factory.hpp"

#include "Cargo.hpp"

void FactoryTest::setUp(){
}

void FactoryTest::tearDown(){
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
	return suiteOfTests;
}
