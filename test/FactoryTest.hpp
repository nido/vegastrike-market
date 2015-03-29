#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Factory.hpp"

class FactoryTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testaddProductionOption();
  void testcanProduce();
  void testProduce();
  void testsetProductionOption();
  /** Not a function or even an unit test per se, but this test
   * exhibits an error that took a while to track down. Running this
   * test in valgrind will result in read errors and an address
   * sanitizer will error out upon hitting the Produce function in case
   * the Factory's productionPlan point to the wrong place.
   */
  void testAllocation();
  static CppUnit::Test *suite();

private:
  CargoType intype;
  CargoType outtype;
  Cargo input;
  Cargo output;
  Cargo cargo;
  ProductionOption po;
  ProductionOption bigpo;
  Factory factory;
};
