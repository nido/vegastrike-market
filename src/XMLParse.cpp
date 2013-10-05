#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <expat.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>


#include "CargoType.hpp"
#include "XMLParse.hpp"

#define MAXSTRLEN 100

std::vector<CargoType> readCargoTypes(std::string filename)
{
	FILE* file;
	char* data;
	size_t fileSize;
	std::vector<CargoType> vect;

	file = fopen(filename.c_str(), "r");
	// obtain file size:
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	rewind(file);

	data = (char*)malloc(sizeof(char) * fileSize + 1);
	assert(data != NULL);
	#ifndef NDEBUG
	size_t result =
	#endif //NDEBUG save the result for assertion
	fread(data, sizeof(char), fileSize + 1, file);
	// check whether the requested data is read
	assert(result == fileSize * sizeof(char));
	// check if the whole file is read
	assert(feof(file) != 0);
	// add terminating NULL
	data[fileSize] = 0;
	// close the file
	fclose(file);
	// and now we have a proper string called data containing the contents
	// of the file.
	
	vect = std::vector<CargoType>();
        XML_Parser parser = XML_ParserCreate(NULL);
        XML_SetElementHandler(parser, XMLCargoTypeVectorBegin, NULL);
        XML_SetUserData(parser, (void*)&vect);
        XML_Parse(parser, data, fileSize, 0);
	XML_ParserFree(parser);
	free(data);
	return(vect);
}

void XMLCargoTypeVectorBegin( void *userData, const XML_Char *name, const XML_Char **atts )
{
	std::vector<CargoType>* store = (std::vector<CargoType>*)userData;

	if(strcmp(name, "CargoType") == 0){
		std::vector<CargoType>::iterator i;
		CargoType* datapointer;
		CargoType data;
		// add a (rather, room for a) new CargoType to the end of the list
		store->push_back(CargoType());

		i = store->end() - 1;
		datapointer = &(*i);
		ParseCargoType(datapointer, atts);
	}
	
}

void XMLParseElement( void *userData, const XML_Char *name, const XML_Char **atts )
{
	if (strcmp(name, "CargoType") == 0){
		ParseCargoType(static_cast<CargoType*>(userData), atts);
	} 
}

void ParseCargoType(CargoType* output, const XML_Char **atts )
{
	int i = 0;
	std::map<std::string, std::string> dict;
	std::string name;
	std::string catagory;
	float mass;
	float volume;
	float price;
	std::string temp;

	do {
		std::string name = std::string(atts[i], strlen(atts[i]));
		std::string value = std::string(atts[i+1], strlen(atts[i + 1]));
		dict[name] = value;
		i = i + 2;
	} while(atts[i] != NULL);

	name = dict["name"];
	assert(name.compare("")!=0);
	
	catagory = dict["catagory"];
	assert(catagory.compare("")!=0);	

	temp = dict["mass"];
	assert(temp.compare("")!=0);
	mass = atof(temp.c_str());
	assert(mass != NAN);

	temp = dict["volume"];
	assert(temp.compare("")!=0);
	volume = atof(temp.c_str());
	assert(volume != NAN);

	temp = dict["price"];
	assert(temp.compare("")!=0);
	price = atof(temp.c_str());
	assert(price != NAN);

	*output = CargoType(name, catagory, mass, volume, price);
}
