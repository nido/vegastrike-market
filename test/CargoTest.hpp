#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Cargo.hpp"

class CargoTest : public CppUnit::TestFixture {
public:
  void setUp();
  void tearDown();

  void testaddCargo();
  void testcontains();
  void testdelCargo();
  void testoperatorEquals();
  void testgetCount();
  void testgetXML();
  static CppUnit::Test *suite();

private:
  CargoType type1;
  CargoType type2;
  CargoType type3;
  Cargo pile1;
  Cargo pile2;
  Cargo pile3;
};
