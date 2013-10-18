#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "FactoryTest.hpp"

void FactoryTest::setUp() {
  this->intype = CargoType("in", "test", 1, 1, 1);
  this->outtype = CargoType("out", "test", 1, 1, 1);

  this->input = Cargo();
  this->output = Cargo();
  this->cargo = Cargo();

  this->input.addCargo(intype, 1);
  this->output.addCargo(outtype, 1);
  this->cargo.addCargo(intype, 2);
  Cargo *in1 = new Cargo();
  Cargo *in2 = new Cargo();
  Cargo *out1 = new Cargo();
  Cargo *out2 = new Cargo();

  in1->addCargo(intype, 1);
  out1->addCargo(outtype, 1);
  in2->addCargo(intype, 2);
  out2->addCargo(outtype, 1);

  this->po = ProductionOption(*in1, *out1);
  this->bigpo = ProductionOption(*in2, *out2);
  this->factory = Factory();
}

void FactoryTest::tearDown() {}

void FactoryTest::testcanProduce() {
  // empty factory cannot produce
  CPPUNIT_ASSERT(this->factory.canProduce(cargo) == false);

  this->factory.addProductionOption(bigpo);
  // cannot produce with not enough goods
  CPPUNIT_ASSERT(this->factory.canProduce(input) == false);
  // cannot produce without the right goods
  CPPUNIT_ASSERT(this->factory.canProduce(output) == false);

  this->factory.addProductionOption(po);
  this->factory.setProductionOption(po);
  // can produce with just enough input goods
  CPPUNIT_ASSERT(this->factory.canProduce(input) == true);
  // can produce with enough input goods
  CPPUNIT_ASSERT(this->factory.canProduce(cargo) == true);
}

void FactoryTest::testProduce() {
  // test is shitty because produce definition is shitty

  this->factory.addProductionOption(po);
  // produce with enough goods
  this->factory.Produce(cargo);
  CPPUNIT_ASSERT(cargo.getCount(intype) == 1);
  CPPUNIT_ASSERT(cargo.getCount(outtype) == 1);
  // produce with just enough goods
  this->factory.Produce(cargo);
  CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
  CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);
  // Production does nothing when impossible
  this->factory.Produce(cargo);
  CPPUNIT_ASSERT(cargo.getCount(intype) == 0);
  CPPUNIT_ASSERT(cargo.getCount(outtype) == 2);
}

void FactoryTest::testsetProductionOption() {
  this->factory.addProductionOption(po);
  this->factory.addProductionOption(bigpo);
  this->factory.setProductionOption(po);
  // production is possible
  this->factory.Produce(this->cargo);
  CPPUNIT_ASSERT(this->cargo.getCount(intype) == 1);
  // production is inpossible
  this->factory.setProductionOption(bigpo);
  this->factory.Produce(this->cargo);
  CPPUNIT_ASSERT(this->cargo.getCount(intype) == 1);
}

CppUnit::Test *FactoryTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("FactoryTest");
  //	suiteOfTests->addTest( new CppUnit::TestCaller<FactoryTest>(
  //			"testFunction",
  //			&FactoryTest::testFunction));

  suiteOfTests->addTest(new CppUnit::TestCaller<FactoryTest>(
      "testcanProduce", &FactoryTest::testcanProduce));

  suiteOfTests->addTest(new CppUnit::TestCaller<FactoryTest>(
      "testProduce", &FactoryTest::testProduce));

  suiteOfTests->addTest(new CppUnit::TestCaller<FactoryTest>(
      "testsetProductionOption", &FactoryTest::testsetProductionOption));
  return suiteOfTests;
}
