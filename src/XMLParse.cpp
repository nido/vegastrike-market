#include <map>
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

void XMLParseElement( void *userData, const XML_Char *name, const XML_Char **atts )
{
	#ifndef NDEBUG
	printf("name %s\n", name);
	int i = 0;
	const XML_Char* c;
	do {
		c = atts[i];
		i++;
		printf("atts %s\n", c);
	}while(c != NULL);
	#endif //NDEBUG
	if (strcmp(name, "CargoType") == 0){
		ParseCargoType((CargoType*)userData, atts);
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
#ifndef NDEBUG
		std::cout<<name<<" = "<<value<<std::endl;
#endif //NDEBUG
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
