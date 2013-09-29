#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "@template@.hpp"

void @template@::setUp()
{
}

void @template@::tearDown()
{
}

@testcode@

CppUnit::Test* @template@::suite()
{
	CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "@template@" );
//	suiteOfTests->addTest( new CppUnit::TestCaller<@template@>(
//			"testFunction",
//			&@template@::testFunction));

	@suitecode@
	return suiteOfTests;
}
