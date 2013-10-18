#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTypeTest.hpp"

void CargoTypeTest::setUp() {
  one = CargoType("1", "1", 0, 0, 0);
  two = CargoType("2", "1", 0, 0, 0);
  three = CargoType("1", "2", 0, 0, 0);

}

void CargoTypeTest::tearDown() {}


void CargoTypeTest::testoperatorEquals() {
  // compare to self 
  CPPUNIT_ASSERT(one == one);
  //compare equal CargoTypes
  CargoType copyone = CargoType("1", "1", 0, 0, 0);
  CPPUNIT_ASSERT(one == copyone);
  // negative case
  CPPUNIT_ASSERT((one == two) == false);
}

void CargoTypeTest::testoperatorLessThen() {
  // positive case
  CPPUNIT_ASSERT(one < two);
  // negative case
  CPPUNIT_ASSERT((one < one) == false);
  CPPUNIT_ASSERT((two < one) == false);
  // cargo catagory difference case
  CPPUNIT_ASSERT(one < three);
}

void CargoTypeTest::testgetBasePrice() {
  CPPUNIT_ASSERT(one.getBasePrice() == 0);
  CargoType type = CargoType("yay", "cata/gory", 1, 2, 3);
  CPPUNIT_ASSERT(type.getBasePrice() == 3);
  type = CargoType("yay2", "cata/gory", 1, 2, 0);
  CPPUNIT_ASSERT(type.getBasePrice() == 0);
}

void CargoTypeTest::testgetName() {
	CPPUNIT_ASSERT(one.getName().compare("1")==0);
	CPPUNIT_ASSERT(two.getName().compare("2")==0);
	CPPUNIT_ASSERT(three.getName().compare("1")==0);
}

void CargoTypeTest::testgetXML() {
	CPPUNIT_ASSERT(one.getXML().compare("<CargoType name=\"1\" category=\"1\" mass=\"0\" volume=\"0\" price=\"0\">")==0);
	CPPUNIT_ASSERT(two.getXML().compare("<CargoType name=\"2\" category=\"1\" mass=\"0\" volume=\"0\" price=\"0\">")==0);
	CPPUNIT_ASSERT(three.getXML().compare("<CargoType name=\"1\" category=\"2\" mass=\"0\" volume=\"0\" price=\"0\">")==0);
}

CppUnit::Test *CargoTypeTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("CargoTypeTest");
  //	suiteOfTests->addTest( new CppUnit::TestCaller<CargoTypeTest>(
  //			"testFunction",
  //			&CargoTypeTest::testFunction));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTypeTest>(
      "testoperatorEquals", &CargoTypeTest::testoperatorEquals));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTypeTest>(
      "testoperatorLessThen", &CargoTypeTest::testoperatorLessThen));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTypeTest>(
      "testgetBasePrice", &CargoTypeTest::testgetBasePrice));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTypeTest>(
      "testgetName", &CargoTypeTest::testgetName));

  suiteOfTests->addTest(new CppUnit::TestCaller<CargoTypeTest>(
      "testgetXML", &CargoTypeTest::testgetXML));

  return suiteOfTests;
}
