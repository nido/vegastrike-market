#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>

#include "MPLParseTest.hpp"
#include "MPLParse.hpp"

#include "common/common.h"
#include "MPLParse.hpp"
#include "CargoType.hpp"

void MPLParseTest::setUp() {}

void MPLParseTest::tearDown() {}

void MPLParseTest::testParse() {
  // default should get system mpl
  MPLParse p = MPLParse();
  std::vector<CargoType> cargo = p.Parse();
  CPPUNIT_ASSERT(cargo.empty() == false);
  MPLParse p2 = MPLParse(getdatadir() + "/master_part_list.csv");
  std::vector<CargoType> cargo2 = p2.Parse();
  CPPUNIT_ASSERT(cargo2.empty() == false);
  CPPUNIT_ASSERT(cargo == cargo2);
}

void MPLParseTest::testParseFile() {
  std::string file = getdatadir() + "/master_part_list.csv";
  std::vector<CargoType> cargo = MPLParse::ParseFile(file);
  CPPUNIT_ASSERT(cargo.empty() == false);
}

void MPLParseTest::testParseLine() {
  CargoType *t =
      MPLParse::ParseLine("\"name\",\"catagory\", 1, 2.3, 4,\"many bla\"");
  CPPUNIT_ASSERT(t->getBasePrice() == 1);
  CPPUNIT_ASSERT(t->getName().compare("name") == 0);
  delete t;
}

CppUnit::Test *MPLParseTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("MPLParseTest");
  //	suiteOfTests->addTest( new CppUnit::TestCaller<MPLParseTest>(
  //			"testFunction",
  //			&MPLParseTest::testFunction));

  suiteOfTests->addTest(new CppUnit::TestCaller<MPLParseTest>(
      "testParse", &MPLParseTest::testParse));

  suiteOfTests->addTest(new CppUnit::TestCaller<MPLParseTest>(
      "testParseFile", &MPLParseTest::testParseFile));

  suiteOfTests->addTest(new CppUnit::TestCaller<MPLParseTest>(
      "testParseLine", &MPLParseTest::testParseLine));

  return suiteOfTests;
}
