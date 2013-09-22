#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CargoTest.hpp"
#include "CargoHoldTest.hpp"
#include "ProductionOptionTest.hpp"
#include "FactoryTest.hpp"

int main(void){
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;

	runner.addTest( CargoTest::suite() );
	runner.addTest( CargoHoldTest::suite() );
	runner.addTest( ProductionOptionTest::suite() );
	runner.addTest( FactoryTest::suite() );

	runner.run();
	return 0;
}
