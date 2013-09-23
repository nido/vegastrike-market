#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include <string.h>

#include "CargoTest.hpp"
#include "CargoHoldTest.hpp"
#include "ProductionOptionTest.hpp"
#include "FactoryTest.hpp"

int main(int argc, char* argv[]){
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;

	if (argc == 1 || strcmp(argv[1], "cargo") == 0){
		runner.addTest( CargoTest::suite() );
	}
	if (argc == 1 || strcmp(argv[1], "cargohold") == 0){
		runner.addTest( CargoHoldTest::suite() );
	}
	if (argc == 1 || strcmp(argv[1], "productionoption") == 0){
		runner.addTest( ProductionOptionTest::suite() );
	}
	if (argc == 1 || strcmp(argv[1], "factory") == 0){
		runner.addTest( FactoryTest::suite() );
	}

	runner.run();
	return 0;
}
