#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <algorithm>
#include <vector>

#include "Economy.hpp"
#include "Base.hpp"

/** This is the test that is supposed to generate a number of turns in
 * a vagestrike sized universe to measure performance to determine
 * maximum economic turn size in seconds. 
 */
int main(int argc, char* argv[]){
	int count = 10;
	if (argc == 2){
		count = atoi(argv[1]);
	}
	Base base;
	Factory factory1;
	Factory factory2;
        CargoType intype1 = CargoType("in1", "test", 1,1,1);
        CargoType intype2 = CargoType("in2", "test", 1,1,1);
        CargoType outtype = CargoType("out", "test", 1, 1,1);
        Cargo input1 = Cargo();
        Cargo input2 = Cargo();
        Cargo output = Cargo();
        Cargo cargo = Cargo();
        input1.addCargo(intype1.getIterator(), 1);
        input2.addCargo(intype2.getIterator(), 1);
        output.addCargo(outtype.getIterator(), 1);
        cargo.addCargo(intype2.getIterator(), 1);
        cargo.addCargo(intype1.getIterator(), count * 10 );
        cargo.addCargo(intype2.getIterator(), count * 10 );
        ProductionOption po1 = ProductionOption(input1, output);
        ProductionOption po2 = ProductionOption(input2, output);
	factory1 = Factory();
	factory1.addProductionOption(po1);
	factory2 = Factory();
	factory2.addProductionOption(po2);

	base = Base();
	base.addCargo(&cargo);
	base.addFactory(factory1);
	base.addFactory(factory1);
	base.addFactory(factory1);
	base.addFactory(factory1);
	base.addFactory(factory1);
	base.addFactory(factory1);
	base.addFactory(factory2);
	base.addFactory(factory2);
	base.addFactory(factory2);
	base.addFactory(factory2);
	base.addFactory(factory2);
	base.addFactory(factory2);
	// there we have it; a base with two inputs.
	
	// build an economy with 10k bases
	Economy economy = Economy();
	for(int i = 0;
		i < 10000;
		i++
	){
		economy.addBase(base);
	}

	// now let us try it count times
	for(int i = 0;
		i < count;
		i++
	){
		economy.tick();
	}
}
