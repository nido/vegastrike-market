#include <iostream>
#include <iterator>
#include "ProductionOption.hpp"
#include "MPLParse.hpp"
#include "XMLNode.hpp"

int main(int argc, char* argv[])
{
  MPLParse parser = MPLParse();
  std::vector<CargoType> cts = parser.ParseFile("../data/master_part_list.csv");
  std::vector<ProductionOption> pos;
  for (std::vector<CargoType>::iterator i = cts.begin(); i != cts.end(); ++i){
    if ((i+ 1) != cts.end()){
      CargoType t = *i;
      CargoType u = *(i+1);
      Cargo in, out;
      in.addCargo(t, 1);
      out.addCargo(u, 2);
      ProductionOption p = ProductionOption(in, out);
      XMLNode n = XMLNode(p);
      std::cout<<n.getXML()<<std::endl;
      pos.push_back(p);
    }
  }
  std::cout<<pos.size()<<std::endl;
}
