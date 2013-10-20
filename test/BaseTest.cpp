#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include <algorithm>

#include "BaseTest.hpp"

void BaseTest::setUp() {

  this->cargo = Cargo();
  this->cargo.addCargo(CargoType("in2", "test", 1, 1, 1), 1);
  this->cargo.addCargo(CargoType("in1", "test", 1, 1, 1), 5);

  Cargo in1 = Cargo();
  in1.addCargo(CargoType("in1", "test", 1, 1, 1), 1);
  Cargo in2 = Cargo();
  in2.addCargo(CargoType("in2", "test", 1, 1, 1), 1);
  Cargo out1 = Cargo();
  out1.addCargo(CargoType("out", "test", 1, 1, 1), 1);
  Cargo out2 = Cargo();
  out2.addCargo(CargoType("out", "test", 1, 1, 1), 1);



  ProductionOption po1 = ProductionOption(in1, out1);
  ProductionOption po2 = ProductionOption(in2, out2);
  this->factory1 = Factory();
  this->factory1.addProductionOption(po1);
  this->factory2 = Factory();
  this->factory2.addProductionOption(po2);
  this->base = Base();
}

void BaseTest::tearDown() {
}

void BaseTest::testaddCargo() {
/*
  this->base.addCargo(&(this->cargo));
  CPPUNIT_ASSERT(*(this->base.getCargo()) == this->cargo);
*/
}

void BaseTest::testaddFactory() {
  this->base.addFactory(factory1);
  std::vector<Factory> list = this->base.getFactories();
  std::vector<Factory>::iterator iter =
      std::find(list.begin(), list.end(), factory1);
  CPPUNIT_ASSERT(iter != list.end());
  CPPUNIT_ASSERT(*iter == factory1);
}

void BaseTest::testdelCargo() {
  this->base.addCargo(this->cargo);
  this->base.delCargo(this->cargo);
  //empty now
  CPPUNIT_ASSERT((this->base.getCargo()) == Cargo());
}

void BaseTest::testdelFactory() {
  this->base.addFactory(factory1);
  this->base.delFactory(factory1);
  std::vector<Factory> list = this->base.getFactories();
  std::vector<Factory>::iterator iter =
      std::find(list.begin(), list.end(), factory1);
  // factory cannot be found
  CPPUNIT_ASSERT(iter == list.end());
}

void BaseTest::testgetFactories() {
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

void BaseTest::testProcess() {
  CargoType intype1 = CargoType("in1", "test", 1, 1, 1);
  this->base.addFactory(factory1);
  this->base.addCargo(cargo);
  Cargo basecargo = this->base.getCargo();
  CPPUNIT_ASSERT(basecargo.getCount(intype1) == 5);

  this->base.Process();
  basecargo = this->base.getCargo();
  CPPUNIT_ASSERT(basecargo.getCount(intype1) == 4);

  this->base.addFactory(factory1);
  this->base.Process();
  basecargo = this->base.getCargo();
  CPPUNIT_ASSERT(basecargo.getCount(intype1) == 2);
}

void BaseTest::testgetCargo() {
  this->base.addCargo(this->cargo);
  CPPUNIT_ASSERT((this->base.getCargo()) == this->cargo);
}

CppUnit::Test *BaseTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("BaseTest");

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testaddCargo", &BaseTest::testaddCargo));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testaddFactory", &BaseTest::testaddFactory));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testdelCargo", &BaseTest::testdelCargo));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testdelFactory", &BaseTest::testdelFactory));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testgetFactories", &BaseTest::testgetFactories));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testProcess", &BaseTest::testProcess));

  suiteOfTests->addTest(new CppUnit::TestCaller<BaseTest>(
      "testgetCargo", &BaseTest::testgetCargo));
  return suiteOfTests;
}
