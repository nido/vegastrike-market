#ifndef H_CONSUMER
#define H_CONSUMER
#include "scew/scew.h"

class Consumer;

#include "Economy.hpp"
#include "Factory.hpp"

class Consumer{
friend class Economy;
public:
    Consumer(double capital, Economy *economy, Products consumption, std::string name,double subsidyrate);

    void tick();

    ~Consumer();

	void addElement(scew_element* root) const;
    static Consumer *consumerFromElement(scew_element* root,Economy *economy,std::string name);

private:
    std::string name;
    double capital;
    Economy *economy;
    Products consumption;
    double subsidyrate;
};

#endif
