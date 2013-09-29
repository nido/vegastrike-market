#include <expat.h>

#include "Cargo.hpp"

void XMLParseElement(void *userData, const XML_Char *name, const XML_Char **atts);
void ParseCargoType(CargoType* output, const XML_Char **atts );
