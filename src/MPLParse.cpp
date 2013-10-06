#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "common/common.h"

#include "MPLParse.hpp"
#include "CargoType.hpp"


MPLParse::MPLParse()
{
	this->file.open(getdatadir().c_str());
	this->filename = getdatadir().c_str();
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

CargoType* MPLParse::ParseLine(std::string line)
{
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
		if (fieldEnd == std::string::npos)
		{
			std::cout<<"warning: invalid line in MPL: "<<line<<std::endl;
			return NULL;
		}
		try {
			substring = line.substr(fieldBegin, fieldEnd - fieldBegin);
		} catch (std::out_of_range){
			std::cout<<"warning: out_of_range in MPL: "<<line<<std::endl;
			return NULL;
		}
		boost::algorithm::trim(substring);

		switch(fieldNumber){
		case 0:
		try {
			name = substring.substr(1, substring.size()-2);
		} catch (std::out_of_range){
			std::cout<<"warning: out_of_range in MPL: "<<line<<std::endl;
			return NULL;
		}
			//std::cout<<"Name: "<<name<<std::endl;
			break;
		case 1:
		try {
			catagory = substring.substr(1, substring.size()-2);
		} catch (std::out_of_range){
			std::cout<<"warning: out_of_range in MPL: "<<line<<std::endl;
			return NULL;
		}
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
	CargoType* t = new CargoType(name, catagory, mass, volume, price);
	return t;
}

std::vector<CargoType> MPLParse::Parse()
{
	std::vector<CargoType> list = std::vector<CargoType>();
	std::string line;

	while (std::getline(this->file, line) ){
		CargoType* cargo;
		if (line.compare(",,,,,")==0){
			// random placeholder line or something. do not add
			continue;
		}
		cargo = ParseLine(line);
		if (cargo != NULL) {
			list.push_back(*cargo);
		}
	}
	return list;
}

std::vector<CargoType> MPLParse::ParseFile(std::string fileName)
{
	MPLParse parser = MPLParse(fileName);
	return parser.Parse();
}

//private:
//	std::ifstream file;

