#ifndef H_XMLPARSE
#define H_XMLPARSE

#include <string>
#include <vector>
#include <map>

#include <expat.h>

#include "Cargo.hpp"

std::vector<CargoType> readCargoTypes(std::string filename);
void XMLParseElement(void *userData, const XML_Char *name,
                     const XML_Char **atts);
void ParseCargoType(CargoType *output, const XML_Char **atts);
void XMLCargoTypeVectorBegin(void *userData, const XML_Char *name,
                             const XML_Char **atts);
std::vector<CargoType> readCargoTypes(std::string filename);
#endif //H_XMLPARSE
