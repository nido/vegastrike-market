#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "common/common.h"

#include "MPLParse.hpp"
#include "CargoType.hpp"

MPLParse::MPLParse():
filename((getdatadir() + "/master_part_list.csv")),
file(this->filename.c_str())
{
  std::cerr<<"MPLParse: "<<this->filename<<std::endl;
  assert(file.is_open());
}

MPLParse::MPLParse(const MPLParse &that) :
filename((getdatadir() + "/master_part_list.csv")),
file(this->filename.c_str())
{
  std::cerr<<"MPLParse &that: "<<this->filename<<std::endl;
  assert(file.is_open());
}

MPLParse::MPLParse(std::string fileName) : filename(fileName),
file(this->filename.c_str())
{
  std::cerr<<"MPLParse std::string: "<<this->filename<<std::endl;
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
  std::string catagory;
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
      std::cerr << "warning: invalid line in MPL: " << line << std::endl;
      return NULL;
    }
    try {
      substring = line.substr(fieldBegin, fieldEnd - fieldBegin);
    }
    catch (std::out_of_range) {
      std::cerr << "warning: out_of_range in MPL: " << line << std::endl;
      return NULL;
    }
    boost::algorithm::trim(substring);

    switch (fieldNumber) {
    case 0:
      try {
        name = substring.substr(1, substring.size() - 2);
      }
      catch (std::out_of_range) {
        std::cerr << "warning: out_of_range in MPL: " << line << std::endl;
        return NULL;
      }
      //std::cerr<<"Name: "<<name<<std::endl;
      break;
    case 1:
      try {
        catagory = substring.substr(1, substring.size() - 2);
      }
      catch (std::out_of_range) {
        std::cerr << "warning: out_of_range in MPL: " << line << std::endl;
        return NULL;
      }
      //std::cerr<<"catagory: "<<catagory<<std::endl;
      break;
    case 2:
      price = atof(substring.c_str());
      //std::cerr<<"Price: "<<price<<std::endl;
      break;
    case 3:
      mass = atof(substring.c_str());
      //std::cerr<<"Mass: "<<mass<<std::endl;
      break;
    case 4:
      volume = atof(substring.c_str());
      //std::cerr<<"volume: "<<volume<<std::endl;
      break;
      //		case 5:
      // description we don't yet care about
    }
    fieldNumber++;
    fieldBegin = fieldEnd + 1;
  } while (fieldNumber < 5);
  CargoType *t = new CargoType(name, catagory, mass, volume, price);
  return t;
}

std::vector<CargoType> MPLParse::Parse() {
  std::vector<CargoType>* list = new std::vector<CargoType>();
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
	std::cerr<<"parsed cargo: "<<cargo->getXML()<<std::endl;
    if (cargo != NULL) {
      list->push_back(*cargo);
    }
  }
  std::cout<<"list size: "<<list->size()<<std::endl;
  return *list;
}

std::vector<CargoType> MPLParse::ParseFile(std::string fileName) {
  MPLParse parser = MPLParse(fileName);
  std::vector<CargoType> v = parser.Parse();
  std::cout<<"v size: "<<v.size()<<std::endl;
  return v;
}

//private:
//	std::ifstream file;
