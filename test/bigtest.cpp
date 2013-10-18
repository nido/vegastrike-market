#include <algorithm>
#include <cassert>

#include <cppunit/TestCaller.h>

#include "Economy.hpp"
#include "MPLParse.hpp"

Cargo *prepareRandomLottaCargo() {
  Cargo *cargo = new Cargo();
  for (int i = 0; i < 500; i++) {
    cargo->addCargo(CargoType(), (rand() % 10000) + 100);
  }
  return cargo;
}

Cargo *prepareRandomCargo() {
  Cargo *cargo = new Cargo();
  cargo->addCargo(CargoType(), (rand() % 10) + 1);
  assert((*cargo == Cargo()) == false);
  return cargo;
}

ProductionOption *prepareRandomProductionOption() {
  ProductionOption* o;
  Cargo* c1 = prepareRandomCargo();
  Cargo* c2 = prepareRandomCargo();
  o = new ProductionOption(c1, c2);
  return o;
}

Factory *prepareRandomFactory() {
  Factory *factory = new Factory();
  ProductionOption* o = prepareRandomProductionOption();
  factory->addProductionOption(o);
  delete o;
  return factory;
}

Base *prepareRandomBase(int basesize) {
  Base *base = new Base();

  for (int i = 0; i < basesize; i++) {
	Factory* f = prepareRandomFactory();
    base->addFactory(*f);
    //delete f;
  }

  Cargo* c = prepareRandomLottaCargo();
  base->addCargo(c);
  delete c;
  return base;
}

/** This is the test that is supposed to generate a number of turns in
 * a vagestrike sized universe to measure performance to determine
 * maximum economic turn size in seconds.
 */
int main(int argc, char *argv[]) {
  int count = 10;
  int basesize = 10;
  int economysize = 10;

  if (argc > 1) {
    count = atoi(argv[1]);
    std::cout << "Doing " << count << " rounds." << std::endl;
  }
  if (argc > 2) {
    basesize = atoi(argv[2]);
    std::cout << "Doing " << basesize << " sized bases." << std::endl;
  }
  if (argc > 3) {
    economysize = atoi(argv[3]);
    std::cout << "Doing " << economysize << " bases." << std::endl;
  }

  std::vector<CargoType> cargo;

  // initialise regular vegastrike cargo
  MPLParse p = MPLParse();
  cargo = p.Parse();
  assert(cargo.size() > 1);

  std::cout << "building Economy" << std::endl;

  // build an economy with 10k bases
  Economy economy = Economy();
  for (int i = 0; i < economysize; i++) {
	Base* b = prepareRandomBase(basesize);
    economy.addBase(*b);
    delete b;
  }
  std::cout << "Running Economy" << std::endl;
  // now let us try it count times
  for (int i = 0; i < count; i++) {
    economy.tick();
    std::cout << "tick" << std::endl;
  }

  if (argc > 1) {
    count = atoi(argv[1]);
    std::cout << "Finished " << count << " rounds." << std::endl;
  }
  if (argc > 2) {
    basesize = atoi(argv[2]);
    std::cout << "Finished " << basesize << " sized bases." << std::endl;
  }
  if (argc > 3) {
    economysize = atoi(argv[3]);
    std::cout << "Finished " << economysize << " bases." << std::endl;
  }
}
