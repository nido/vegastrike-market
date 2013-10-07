#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include <map>
#include <string>
#include <expat.h>
#include <cstdio>
#include <cstdlib>

#include "XMLParseTest.hpp"

#include "XMLParse.hpp"
#include "Cargo.hpp"

void XMLParseTest::setUp()
{
	this->inputcargostring = "<CargoType name=\"input\" catagory =\"test\" mass=\"10\" volume=\"10\" price=\"10\" />";
	this->input = new CargoType("input", "test", 10.0, 10.0, 1.0);
	this->parser = XML_ParserCreate(NULL);
}

void XMLParseTest::tearDown()
{
	delete this->input;
 	XML_ParserFree(this->parser);
}

void XMLParseTest::testParseCargoType(){
	CargoType* test = new CargoType();
	XML_SetElementHandler(this->parser, XMLParseElement, NULL);
	XML_SetUserData(this->parser, test);
	XML_Parse(parser, this->inputcargostring.c_str(), inputcargostring.size(), 0);
	CPPUNIT_ASSERT(*test == *(this->input));
	delete test;
}

/** For use with xml read test
	std::vector<CargoType> t = readCargoTypes("../data/CargoType.xml");
	for (std::vector<CargoType>::iterator i = t.begin();
		i != t.end();
		++i
	){
		std::cout<<i->getName()<<std::endl;
	}
*/

/*static void endElement( void *userData, const XML_Char *name)
{
	(void)userData;
	printf("Ending %s\n", name);
}*/

CppUnit::Test* XMLParseTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "XMLParseTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<XMLParseTest>(
			"testParseCargoType",
			&XMLParseTest::testParseCargoType));
	return suiteOfTests;
}
