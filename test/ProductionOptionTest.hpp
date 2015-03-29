#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "ProductionOption.hpp"

class ProductionOptionTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testCanProduce();
  void testProduce();
  void testoperatorEquals();
  static CppUnit::Test *suite();

private:
  CargoType intype;
  CargoType outtype;
  Cargo input;
  Cargo output;
  Cargo cargo;
  ProductionOption po;
  ProductionOption bigpo;
};
