#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>

#include "XMLNodeTest.hpp"

void XMLNodeTest::setUp()
{
	this->root = new XMLNode();
	this->singleNode = "<a/>";

	// the xml parser may come in handy.
    this->parser = XML_ParserCreate(NULL);

    //XML_SetElementHandler(parser, XMLNode::ParseXMLNodeBegin, XMLNode::ParseXMLNodeEnd);

    XML_SetUserData(this->parser, static_cast<void*>(root));
    //XML_Parse(this->parser, data, string.size(), 0);
}

void XMLNodeTest::tearDown()
{
    XML_ParserFree(this->parser);
	delete root;
}

void XMLNodeTest::testParseElementBegin()
{	//TODO: Implement test
}

void XMLNodeTest::testParseElementEnd()
{	//TODO: Implement test
}

void XMLNodeTest::testParseString()
{	//TODO: Implement test
	std::string inputstring = "<a><b /><c><b /></c><text>Hi</text>atext</a>";
    XMLNode* n = XMLNode::ParseString(inputstring);
//	std::cout << inputstring << std::endl;
//	std::cout << n->buildXMLString() << std::endl;
	CPPUNIT_ASSERT(inputstring.compare(n->buildXMLString())==0);
}

void XMLNodeTest::testParseXMLNodeBegin()
{	//TODO: Implement test
}

void XMLNodeTest::testParseXMLNodeEnd()
{	//TODO: Implement test
}


CppUnit::Test* XMLNodeTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "XMLNodeTest" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
//			"testFunction",
//			&XMLNodeTest::testFunction));

	
	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
			"testParseElementBegin", &XMLNodeTest::testParseElementBegin));

	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
			"testParseElementEnd", &XMLNodeTest::testParseElementEnd));

	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
			"testParseString", &XMLNodeTest::testParseString));

	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
			"testParseXMLNodeBegin", &XMLNodeTest::testParseXMLNodeBegin));

	suiteOfTests->addTest( new CppUnit::TestCaller<XMLNodeTest>(
			"testParseXMLNodeEnd", &XMLNodeTest::testParseXMLNodeEnd));

	return suiteOfTests;
}
