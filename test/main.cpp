#include <string.h>

#include <cppunit/TestCaller.h>
#include <cppunit/TestResultCollector.h>

#include "BaseTest.hpp"
#include "CargoTest.hpp"
#include "CargoTypeTest.hpp"
#include "EconomyTest.hpp"
#include "FactoryTest.hpp"
#include "MPLParseTest.hpp"
#include "ProductionOptionTest.hpp"
#include "XMLNodeTest.hpp"

int main(int argc, char* argv[]){
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;

	if (argc != 1 && strcmp(argv[1], "Base") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "Base") == 0){
		 runner.addTest( BaseTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "Cargo") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "Cargo") == 0){
		 runner.addTest( CargoTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "CargoType") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "CargoType") == 0){
		 runner.addTest( CargoTypeTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "Economy") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "Economy") == 0){
		 runner.addTest( EconomyTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "Factory") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "Factory") == 0){
		 runner.addTest( FactoryTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "MPLParse") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "MPLParse") == 0){
		 runner.addTest( MPLParseTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "ProductionOption") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "ProductionOption") == 0){
		 runner.addTest( ProductionOptionTest::suite());
	}
	if (argc != 1 && strcmp(argv[1], "XMLNode") == 0 ){
		std::cout<<argv[1]<<": ";
	}
	if (argc == 1 || strcmp(argv[1], "XMLNode") == 0){
		 runner.addTest( XMLNodeTest::suite());
	}
	runner.run();
	return runner.result().testFailuresTotal();
}
