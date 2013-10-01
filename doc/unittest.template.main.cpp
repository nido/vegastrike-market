#include <string.h>

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

@includecode@

int main(int argc, char* argv[]){
	CppUnit::TestSuite suite;
	CppUnit::TextUi::TestRunner runner;
@unittestcode@
	runner.run();
	return runner.result().testFailuresTotal();
}
