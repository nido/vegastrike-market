#include <string.h>

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>


#include "CargoTest.hpp"
#include "CargoTypeTest.hpp"
#include "FactoryTest.hpp"
#include "ProductionOptionTest.hpp"
#include "XMLParseTest.hpp"

int main(int argc, char* argv[]){
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;


	if (argc == 1 || strcmp(argv[1], "CargoTest") == 0){
		 runner.addTest( CargoTest::suite());
	}
	if (argc == 1 || strcmp(argv[1], "CargoTypeTest") == 0){
		 runner.addTest( CargoTypeTest::suite());
	}
	if (argc == 1 || strcmp(argv[1], "FactoryTest") == 0){
		 runner.addTest( FactoryTest::suite());
	}
	if (argc == 1 || strcmp(argv[1], "ProductionOptionTest") == 0){
		 runner.addTest( ProductionOptionTest::suite());
	}
	if (argc == 1 || strcmp(argv[1], "XMLParseTest") == 0){
		 runner.addTest( XMLParseTest::suite());
	}

	runner.run();
	return 0;
}
