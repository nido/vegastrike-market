#ifndef H_MPLPARSE
#define H_MPLPARSE

#include <fstream>
#include <vector>

#include "CargoType.hpp"

class MPLParse {
public:
  MPLParse();
  MPLParse(const MPLParse &);
  MPLParse(std::string fileName);
  ~MPLParse();

  std::vector<CargoType> Parse();
  MPLParse& operator=(const MPLParse &that);


  static CargoType *ParseLine(std::string line);
  static std::vector<CargoType> ParseFile(std::string fileName);

private:
  void initStream();
  std::string filename;
  std::ifstream file;
};

#endif //H_MPLPARSE
