#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "xmlTest.hpp"
#include "CargoType.hpp"

void xmlTest::setUp()
{
	t = CargoType("name", "category", 1, 2, 3);
	t2 = CargoType("otherstuff", "category", 1, 2, 3);
	c.addCargo(t, 10);
	c.addCargo(t2, 12);
}

void xmlTest::tearDown()
{
}

void xmlTest::testCargoType()
{
	std::string xml = this->t.getXML();
	CPPUNIT_ASSERT(xml.compare("<CargoType name=\"name\" category=\"category\" mass=\"1\" volume=\"2\" price=\"3\" />") == 0);
}

void xmlTest::testCargo()
{
	std::string xml = this->c.getXML();
	CPPUNIT_ASSERT(xml.compare("<Cargo><pair><CargoType name=\"name\" category=\"category\" mass=\"1\" volume=\"2\" price=\"3\" /><value>10</value></pair><pair><CargoType name=\"otherstuff\" category=\"category\" mass=\"1\" volume=\"2\" price=\"3\" /><value>12</value></pair></Cargo>") == 0);
}

CppUnit::Test* xmlTest::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "xmlTest" );
	suiteOfTests->addTest( new CppUnit::TestCaller<xmlTest>(
			"testCargoType", &xmlTest::testCargoType));

	suiteOfTests->addTest( new CppUnit::TestCaller<xmlTest>(
			"testCargo", &xmlTest::testCargo));

	
	return suiteOfTests;
}
