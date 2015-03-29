#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>

#include "XMLNodeTest.hpp"

void XMLNodeTest::setUp() {
  this->root = new XMLNode();
  this->singleNode = "<a/>";

  // the xml parser may come in handy.
  this->parser = XML_ParserCreate(NULL);

  // XML_SetElementHandler(parser, XMLNode::ParseXMLNodeBegin,
  // XMLNode::ParseXMLNodeEnd);

  XML_SetUserData(this->parser, static_cast<void *>(root));
  // XML_Parse(this->parser, data, string.size(), 0);
}

void XMLNodeTest::tearDown() {
  XML_ParserFree(this->parser);
  delete root;
}

void XMLNodeTest::testConstructors() {
  CargoType t = CargoType("name", "category", 1, 2, 3);
  XMLNode n = XMLNode(t);
  CargoType *xmltype = n.getCargoType();
  CPPUNIT_ASSERT(*xmltype == t);
  delete xmltype;
}

void XMLNodeTest::testParseElementBegin() // TODO: Implement test
{}

void XMLNodeTest::testParseElementEnd() // TODO: Implement test
{}

void XMLNodeTest::testParseString() // TODO: Implement test
{
  std::string inputstring = "<a><b vega=\"strike\" /><c><b /></c><text "
                            "hilight=\"true\">Hi</text>atext</a>";
  XMLNode *n = XMLNode::ParseString(inputstring);
  CPPUNIT_ASSERT(inputstring.compare(n->getXML()) == 0);
  delete n;
}

void XMLNodeTest::testParseXMLNodeBegin() // TODO: Implement test
{}

void XMLNodeTest::testParseXMLNodeEnd() // TODO: Implement test
{}

void XMLNodeTest::testgetCargoType() {
  XMLNode *n =
      XMLNode::ParseString("<CargoType name=\"cargo\" category=\"category\" "
                           "mass=\"1\" volume=\"2\" price=\"3\" />");
  CargoType *test = n->getCargoType();

  CargoType reference = CargoType("cargo", "category", 1, 2, 3);

  CPPUNIT_ASSERT(test != NULL);
  if (test != NULL) {
    CPPUNIT_ASSERT(reference == *test);
  }
  delete n;
  delete test;
}

void XMLNodeTest::testgetCargo() {
  std::string s = "<Cargo><CargoType name=\"name\" category=\"category\" "
                  "mass=\"1\" volume=\"2\" "
                  "price=\"3\">10</CargoType><CargoType name=\"otherstuff\" "
                  "category=\"category\" mass=\"1\" volume=\"2\" price=\"3\" "
                  ">12</CargoType></Cargo>";
  XMLNode *n = XMLNode::ParseString(s);
  Cargo *c = n->getCargo();
  delete n;
  CPPUNIT_ASSERT(c != NULL);
  if (c != NULL) {
    CargoType t1 = CargoType("name", "category", 1, 2, 3);
    CargoType t2 = CargoType("otherstuff", "category", 1, 2, 3);
    CPPUNIT_ASSERT(c->getCount(t1) == 10);
    CPPUNIT_ASSERT(c->getCount(t2) == 12);
    delete c;
  };
}

void XMLNodeTest::testgetProductionOption() {
  std::string s = "<ProductionOption><Cargo type=\"in\"><CargoType "
                  "name=\"name\" category=\"category\" mass=\"1\" volume=\"2\" "
                  "price=\"3\">10</CargoType></Cargo><Cargo "
                  "type=\"out\"><CargoType name=\"otherstuff\" "
                  "category=\"category\" mass=\"1\" volume=\"2\" price=\"3\" "
                  ">12</CargoType></Cargo>";
  XMLNode *n = XMLNode::ParseString(s);
  ProductionOption *p = n->getProductionOption();
  CPPUNIT_ASSERT(p != NULL);
  if (p != NULL) {
    CargoType t1 = CargoType("name", "category", 1, 2, 3);
    CargoType t2 = CargoType("otherstuff", "category", 1, 2, 3);
    Cargo c = Cargo();
    c.addCargo(t1, 10);
    CPPUNIT_ASSERT(c.getCount(t1) == 10);
    CPPUNIT_ASSERT(c.getCount(t2) == 0);
    p->Produce(c);
    CPPUNIT_ASSERT(c.getCount(t1) == 0);
    CPPUNIT_ASSERT(c.getCount(t2) == 12);
    XMLNode m = XMLNode(*p);
    ProductionOption* q = m.getProductionOption();
    CPPUNIT_ASSERT(q != NULL);
    if( q != NULL){
      CPPUNIT_ASSERT(*p == *q);
      delete q;
    }
    delete p;
  };
  delete n;
}

void XMLNodeTest::testCopyConstructor() {
  XMLNode *n =
      XMLNode::ParseString("<CargoType name=\"cargo\" category=\"category\" "
                           "mass=\"1\" volume=\"2\" price=\"3\" />");
  XMLNode m = *n;
  delete n;
  CargoType *c = m.getCargoType();
  CPPUNIT_ASSERT(c != NULL);
  if (c != NULL) {
    CPPUNIT_ASSERT(c->getBasePrice() == 3);
    CPPUNIT_ASSERT(c->getName().compare("cargo") == 0);
  }
  delete c;
}

void XMLNodeTest::testGetXMLNode() {
  CargoType ct = CargoType("cargo", "category", 1, 2, 3);
  XMLNode n = XMLNode(ct);
  CargoType *check = n.getCargoType();
  CPPUNIT_ASSERT(check != NULL);
  if (check != NULL) {
    CPPUNIT_ASSERT(ct == *check);
    delete check;
  }

  Cargo c = Cargo();
  c.addCargo(ct, 4);
  XMLNode m = XMLNode(c);
  Cargo* cargocheck = m.getCargo();
  CPPUNIT_ASSERT(cargocheck != NULL);
  if (cargocheck != NULL){
    CPPUNIT_ASSERT(*cargocheck == c);
    delete cargocheck;
  }
}

CppUnit::Test *XMLNodeTest::suite() {
  CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("XMLNodeTest");
  //	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
  //			"testFunction",
  //			&XMLNodeTest::testFunction));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testGetXMLNode", &XMLNodeTest::testGetXMLNode));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testParseElementBegin", &XMLNodeTest::testParseElementBegin));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testParseElementEnd", &XMLNodeTest::testParseElementEnd));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testParseString", &XMLNodeTest::testParseString));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testParseXMLNodeBegin", &XMLNodeTest::testParseXMLNodeBegin));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testParseXMLNodeEnd", &XMLNodeTest::testParseXMLNodeEnd));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testgetCargoType", &XMLNodeTest::testgetCargoType));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testgetCargo", &XMLNodeTest::testgetCargo));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testgetProductionOption", &XMLNodeTest::testgetProductionOption));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testCopyConstructor", &XMLNodeTest::testCopyConstructor));

  suiteOfTests->addTest(new CppUnit::TestCaller<XMLNodeTest>(
      "testConstructors", &XMLNodeTest::testConstructors));

  return suiteOfTests;
}
