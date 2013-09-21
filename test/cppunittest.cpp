#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "testCargoHold.hpp"

int main(void){
	CppUnit::TestResult result;
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;

	runner.addTest( CargoHoldTest::suite() );
	runner.run();
	return 0;
}
