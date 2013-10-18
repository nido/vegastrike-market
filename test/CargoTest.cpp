#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <assert.h>
#include <string>
#include <stdexcept>
#include "CargoTest.hpp"

void CargoTest::setUp() {
  type1 = CargoType("1", "test", 1, 1, 1);
  type2 = CargoType("2", "test", 2, 2, 2);
  type3 = CargoType("3", "test", 3, 3, 3);
  pile1 = Cargo();
  pile2 = Cargo();
  pile3 = Cargo();
}

void CargoTest::tearDown() {}

void CargoTest::testaddCargo() {
  pile1.addCargo(type1, 1);
  // pile1 now has 1 type1 cargo
  CPPUNIT_ASSERT(pile1.getCount(type1) == 1);

  pile2.addCargo(pile1);
  // pile2 now has 1 type1 cargo
  CPPUNIT_ASSERT(pile2.getCount(type1) == 1);

  pile1.addCargo(type1, 1);
  CPPUNIT_ASSERT(pile1.getCount(type1) == 2);
  CPPUNIT_ASSERT(pile2.getCount(type1) == 1);
}

void CargoTest::testcontains() {
  pile1.addCargo(type1, 1);
  pile2.addCargo(type2, 1);
  pile3.addCargo(type1, 3);

  CPPUNIT_ASSERT(pile1.contains(pile2) == false);
  CPPUNIT_ASSERT(pile1.contains(pile3) == false);

  CPPUNIT_ASSERT(pile2.contains(pile1) == false);
  CPPUNIT_ASSERT(pile2.contains(pile3) == false);

  CPPUNIT_ASSERT(pile3.contains(pile1) == true);
  CPPUNIT_ASSERT(pile3.contains(pile2) == false);
}

void CargoTest::testdelCargo() {
  pile1.addCargo(type1, 100);
  pile2.addCargo(type1, 50);

  CPPUNIT_ASSERT(pile3.delCargo(pile1) == false);
  CPPUNIT_ASSERT(pile1.getCount(type1) == 100);
  CPPUNIT_ASSERT(pile3.getCount(type1) == 0);

  CPPUNIT_ASSERT(pile2.delCargo(pile1) == false);
  CPPUNIT_ASSERT(pile1.getCount(type1) == 100);
  CPPUNIT_ASSERT(pile2.getCount(type1) == 50);

  CPPUNIT_ASSERT(pile1.delCargo(pile2) == true);
  CPPUNIT_ASSERT(pile1.getCount(type1) == 50);
  CPPUNIT_ASSERT(pile2.getCount(type1) == 50);

  CPPUNIT_ASSERT(pile1.delCargo(pile1) == true);
  CPPUNIT_ASSERT(pile1.getCount(type1) == 0);
  CPPUNIT_ASSERT(pile2.getCount(type1) == 50);
}

void CargoTest::testoperatorEquals() {
  pile1.addCargo(type1, 100);
  // pile1 has 100 type1 cargo, pile2 and pile3 are empty
  CPPUNIT_ASSERT(pile2 == pile3);
  CPPUNIT_ASSERT((pile1 == pile2) == false);
  CPPUNIT_ASSERT(pile1 == pile1);
  pile3.addCargo(type1, 100);
  // pile1 and pile3 have 100 type1; pile2 is empty
  CPPUNIT_ASSERT(pile3 == pile1);
  pile2.addCargo(type3, 100);
  // pile1 and pile3 have 100 type1; pile2 has 100 type3
  CPPUNIT_ASSERT((pile1 == pile2) == false);
}

CppUnit::Test *CargoTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("CargoTest");
  //	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTest>(
  //			"testFunction",
  //			&CargoTest::testFunction));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTest>(
      "testaddCargo", &CargoTest::testaddCargo));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTest>(
      "testcontains", &CargoTest::testcontains));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTest>(
      "testdelCargo", &CargoTest::testdelCargo));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTest>(
      "testoperatorEquals", &CargoTest::testoperatorEquals));

  return suiteOfTests;
}
