#ifndef H_MPLPARSE
#define H_MPLPARSE

#include <vector>
#include <fstream>

#include "CargoType.hpp"

class MPLParse{
public:
	MPLParse();
	MPLParse(const MPLParse&);
	MPLParse(std::string fileName);
	~MPLParse();

	std::vector<CargoType> Parse();

	static CargoType* ParseLine(std::string line);
	static std::vector<CargoType> ParseFile(std::string fileName);
private:
	const char* filename;
	std::ifstream file;
};

#endif //H_MPLPARSE
