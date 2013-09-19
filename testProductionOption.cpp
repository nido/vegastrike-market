#include <ProductionOption.hpp>

int main(void){
	std::vector<Cardo> stuff1 = std::vector<Cardo>();
	std::vector<Cardo> stuff2 = std::vector<Cardo>();
	std::vector<Cardo> stuff3 = std::vector<Cardo>();
	stuff1.push_back(Cargo("input", 0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff2.push_back(Cargo("output", 0.0, 1, 0.0, 0.0, 0.0, 0.0));
	stuff3.push_back(Cargo("input", 0.0, 10, 0.0, 0.0, 0.0, 0.0));
	ProductionOption o = ProductionOption(stuff1, stuff2);
	for(int i=0; i<1000; i++) {
		o.Produce(stuff3);
	}
	return 0;
}
