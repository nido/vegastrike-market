#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "XMLParse.hpp"
#include "Cargo.hpp"

class XMLParseTest : public CppUnit::TestFixture  {
public:
	void setUp();
	void tearDown();

	void testParseCargoType();
	static CppUnit::Test* suite();
private:
	std::string inputcargostring;
	CargoType* input;
	XML_Parser parser;
};
