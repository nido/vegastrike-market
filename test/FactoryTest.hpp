#include "Factory.hpp"

class FactoryTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testaddProductionOption();
  void testcanProduce();
  void testProduce();
  void testsetProductionOption();
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
