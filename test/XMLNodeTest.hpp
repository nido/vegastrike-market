#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "XMLNode.hpp"

class XMLNodeTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testParseElementBegin();
  void testParseElementEnd();
  void testParseString();
  void testParseXMLNodeBegin();
  void testParseXMLNodeEnd();
  void testgetCargoType();
  static CppUnit::Test *suite();

private:
  std::string singleNode;
  XMLNode *root;
  XML_Parser parser;
};
