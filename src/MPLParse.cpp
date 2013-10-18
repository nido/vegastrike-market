#include <fstream>

#include <boost/algorithm/string.hpp>

#include "common/common.h"
#include "MPLParse.hpp"

MPLParse::MPLParse():
filename((getdatadir() + "/master_part_list.csv")),
file(this->filename.c_str())
{
  assert(file.is_open());
}

MPLParse::MPLParse(const MPLParse &that) :
filename(that.filename),
file(this->filename.c_str())
{
  assert(file.is_open());
}

MPLParse::MPLParse(std::string fileName) : filename(fileName),
file(this->filename.c_str())
{
  assert(file.is_open());
}

MPLParse& MPLParse::operator=(const MPLParse &that)
{
  this->filename = that.filename;
  this->initStream();
  return *this;
}

void MPLParse::initStream() {
  this->file.open(this->filename.c_str());
  assert(file.is_open());
}

MPLParse::~MPLParse() { this->file.close(); }

CargoType *MPLParse::ParseLine(std::string line) {
  std::string name;
  std::string category;
  std::string substring;
  float mass;
  float volume;
  float price;
  int fieldNumber = 0;
  size_t fieldBegin = 0;
  do {
    size_t fieldEnd;
    fieldEnd = line.find(",", fieldBegin);
    if (fieldEnd == std::string::npos) {
      return NULL;
    }
    try {
      substring = line.substr(fieldBegin, fieldEnd - fieldBegin);
    }
    catch (std::out_of_range) {
      return NULL;
    }
    boost::algorithm::trim(substring);

    switch (fieldNumber) {
    case 0:
      try {
        name = substring.substr(1, substring.size() - 2);
      }
      catch (std::out_of_range) {
        return NULL;
      }
      break;
    case 1:
      try {
        category = substring.substr(1, substring.size() - 2);
      }
      catch (std::out_of_range) {
        return NULL;
      }
      break;
    case 2:
      price = atof(substring.c_str());
      break;
    case 3:
      mass = atof(substring.c_str());
      break;
    case 4:
      volume = atof(substring.c_str());
      break;
      //		case 5:
      // description we don't yet care about
    }
    fieldNumber++;
    fieldBegin = fieldEnd + 1;
  } while (fieldNumber < 5);
  CargoType *t = new CargoType(name, category, mass, volume, price);
  return t;
}

std::vector<CargoType> MPLParse::Parse() {
  std::vector<CargoType> list = std::vector<CargoType>();
  std::string line;

  assert(this->file.is_open());
  this->file.seekg(0, this->file.beg);

  while (std::getline(this->file, line)) {
    CargoType *cargo;
    if (line.compare(",,,,,") == 0) {
      // random placeholder line or something. do not add
      continue;
    }
    cargo = ParseLine(line);
    if (cargo != NULL) {
      list.push_back(*cargo);
    }
    delete cargo;
  }
  return list;
}

std::vector<CargoType> MPLParse::ParseFile(std::string fileName) {
  MPLParse parser = MPLParse(fileName);
  std::vector<CargoType> v = parser.Parse();
  return v;
}

//private:
//	std::ifstream file;
