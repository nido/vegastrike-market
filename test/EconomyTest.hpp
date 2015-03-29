#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Economy.hpp"

class EconomyTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testaddBase();
  void testdelBase();
  void testgetBases();
  void testtick();
  static CppUnit::Test *suite();

private:
  Economy *e;
  Base *b;
};
