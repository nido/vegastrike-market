#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "MPLParse.hpp"
#include "CargoType.hpp"

#ifndef MASTER_PART_LIST
#define MASTER_PART_LIST "../data/master_part_list.csv"
#endif

MPLParse::MPLParse()
{
	this->file.open(MASTER_PART_LIST);
	this->filename = MASTER_PART_LIST;
}

MPLParse::MPLParse(const MPLParse& that)
{
	this->filename = that.filename;
	this->file.open(this->filename);
}

MPLParse::MPLParse(std::string fileName)
{
	this->file.open(fileName.c_str());
	this->filename = fileName.c_str();
}

MPLParse::~MPLParse()
{
	this->file.close();
}

CargoType MPLParse::ParseLine(std::string line)
{
	std::string name;
	std::string catagory;
	std::string substring;
	float mass;
	float volume;
	float price;
	int fieldNumber = 0;
	size_t fieldBegin = 0;
	size_t fieldEnd;
	do {
		fieldEnd = line.find(",", fieldBegin);
		if (fieldEnd == std::string::npos)
		{
			std::cout<<"warning: invalid line in MPL: "<<line<<std::endl;
			break;
		}
		substring = line.substr(fieldBegin, fieldEnd - fieldBegin);
		boost::algorithm::trim(substring);

		switch(fieldNumber){
		case 0:
			name = substring.substr(1, substring.size()-2);
			//std::cout<<"Name: "<<name<<std::endl;
			break;
		case 1:
			catagory = substring.substr(1, substring.size()-2);
			//std::cout<<"catagory: "<<catagory<<std::endl;
			break;
		case 2:
			price = atof(substring.c_str());
			//std::cout<<"Price: "<<price<<std::endl;
			break;
		case 3:
			mass = atof(substring.c_str());
			//std::cout<<"Mass: "<<mass<<std::endl;
			break;
		case 4:
			volume = atof(substring.c_str());
			//std::cout<<"volume: "<<volume<<std::endl;
			break;
//		case 5:
			// description we don't yet care about
		}
		fieldNumber++;
		fieldBegin = fieldEnd+1;
	} while(fieldNumber < 5);
	CargoType t = CargoType(name, catagory, mass, volume, price);
	return t;
}

std::vector<CargoType> MPLParse::Parse()
{
	std::vector<CargoType> list = std::vector<CargoType>();
	CargoType cargo;
	std::string line;

	while (std::getline(this->file, line) ){
		cargo = ParseLine(line);
		list.push_back(cargo);
	}
}

std::vector<CargoType> MPLParse::ParseFile(std::string fileName)
{
}

//private:
//	std::ifstream file;
