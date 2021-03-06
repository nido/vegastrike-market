#include <algorithm>
#include <fstream>
#include <cassert>

#include <cppunit/TestCaller.h>

#include "XMLNode.hpp"
#include "Economy.hpp"
#include "MPLParse.hpp"

Cargo prepareRandomLottaCargo();
Cargo prepareRandomLottaCargo() {
  Cargo cargo = Cargo();
  for (int i = 0; i < 500; i++) {
    cargo.addCargo(CargoType(), (rand() % 10000) + 100);
  }
  return cargo;
}

Cargo prepareRandomCargo();
Cargo prepareRandomCargo() {
  Cargo cargo = Cargo();
  cargo.addCargo(CargoType(), (rand() % 10) + 1);
  assert((cargo == Cargo()) == false);
  return cargo;
}

ProductionOption prepareRandomProductionOption();
ProductionOption prepareRandomProductionOption() {
  ProductionOption o;
  const Cargo c1 = prepareRandomCargo();
  const Cargo c2 = prepareRandomCargo();
  o = ProductionOption(c1, c2);
  return o;
}

Factory prepareRandomFactory();
Factory prepareRandomFactory() {
  Factory factory = Factory();
  ProductionOption o = prepareRandomProductionOption();
  factory.addProductionOption(o);
  return factory;
}

Base prepareRandomBase(int basesize);
Base prepareRandomBase(int basesize) {
  Base base = Base();
  Factory f;
  for (int i = 0; i < basesize; i++) {
    f = prepareRandomFactory();
    base.addFactory(f);
  }

  Cargo c = prepareRandomLottaCargo();
  base.addCargo(c);
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
  std::string filename;
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
  if (argc > 4) {
    filename = argv[4]; 
    std::cout << "Saving economy to " << filename << "." << std::endl;
  }

  std::vector<CargoType> cargo;

  // initialise regular vegastrike cargo
  MPLParse p = MPLParse();
  cargo = p.Parse();
  assert(cargo.size() > 1);

  std::cout << "building Economy" << std::endl;

  // build an economy with 10k bases
  Economy economy = Economy();
  economy.preallocate(economysize);
  for (int i = 0; i < economysize; i++) {
    Base b = prepareRandomBase(basesize);
    economy.addBase(b);
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
  if (argc > 4){
    std::cout << "Saving economy to " << filename << "." << std::endl;
    XMLNode n = XMLNode(economy);
    std::ofstream XMLFile(filename.c_str(), std::ios::trunc);
    XMLFile<<"<?xml version=\"1.0\"?>"<<std::endl;
    XMLFile<<"<!DOCTYPE economy SYSTEM \"economy.dtd\">"<<std::endl<<std::endl;;
    XMLFile<<n.getXML()<<std::endl;
    XMLFile.close();
  }
  return 0;
}
