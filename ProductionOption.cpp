#include "math.h"

#include "scew/scew.h"

#include "ProductionOption.hpp"
#include "Market.hpp"

ProductionOption::ProductionOption(Products outputs, Products inputs, double sectorsize, double sectormin, Products costofanother){
	this->outputs= outputs;
	this->inputs= inputs;
	this->sectorsize = sectorsize;
	this->sectormin= sectormin;
	this->costofanother = costofanother;
}


ProductionOption::ProductionOption(Products outputs, Products inputs, double sectorsize, Products costofanother){
	this->outputs= outputs;
	this->inputs= inputs;
	this->sectorsize = sectorsize;
	this->sectormin= sqrt(sectorsize);
	this->costofanother = costofanother;
}

void ProductionOption::addElement(scew_element* root) const{
    scew_element* element = NULL;

    element = scew_element_add(root, "outputs");
    Products_addElement(outputs,element);

    element = scew_element_add(root, "inputs");
    Products_addElement(inputs,element);

    element = scew_element_add(root, "sectorsize");
    scew_element_set_contents(element, toCString(sectorsize));

    element = scew_element_add(root, "sectormin");
    scew_element_set_contents(element, toCString(sectormin));

    element = scew_element_add(root, "costofanother");
    Products_addElement(costofanother,element);
}

ProductionOption *ProductionOption::productionOptionFromElement(scew_element* root){
    ProductionOption *ppo = NULL;
    scew_element *element = NULL;
    XML_Char const*contents = NULL;

    double sectorsize = 0.0;
    double sectormin = 0.0;
    Products *pinputs, *poutputs, *pcostofanother;

    element = scew_element_by_name(root, "sectorsize");
    if(NULL !=element){
        contents= scew_element_contents(element);
        if(NULL != contents){
            sectorsize= doubleFromCString(contents,sectorsize);
        }
    }

    element = scew_element_by_name(root, "sectormin");
    if(NULL !=element){
        contents= scew_element_contents(element);
        if(NULL != contents){
            sectormin= doubleFromCString(contents,sectormin);
        }
    }

    element = scew_element_by_name(root, "inputs");
    if(NULL !=element){
        pinputs= productsFromElement(element);
    }

    element = scew_element_by_name(root, "outputs");
    if(NULL !=element){
        poutputs= productsFromElement(element);
    }

    element = scew_element_by_name(root, "costofanother");
    if(NULL !=element){
        pcostofanother= productsFromElement(element);
    }

    if( NULL!= poutputs && NULL != pinputs && 0.0<=sectorsize && NULL!= pcostofanother){
        ppo= new ProductionOption(*poutputs,*pinputs,sectorsize,sectormin,*pcostofanother);
    }

    //clean up
    if(NULL!= poutputs){
        delete poutputs;
    }

    if(NULL!= pinputs){
        delete pinputs;
    }

    if(NULL!= pcostofanother){
        delete pcostofanother;
    }

    return ppo;
}
void Products_addElement(const Products &products, scew_element* root){
    scew_element* element = NULL;

    for(Products::const_iterator pitr = products.begin(); pitr != products.end(); ++pitr){
	element = scew_element_add(root, "product");
	scew_element_add_attr_pair(element, "name", (*pitr).first.c_str());
	scew_element_set_contents(element, toCString((*pitr).second));
    }
}


Products *productsFromElement(scew_element* element){
    Products *pp= new Products();
    XML_Char const*contents = NULL;

    for(scew_element* sub_element=scew_element_next(element, NULL);NULL != sub_element;sub_element=scew_element_next(element, sub_element)){
        if(0==strcmp(scew_element_name(sub_element),"product")){
            string name;
            double amount=0.0;
            for(scew_attribute* attribute=scew_attribute_next(sub_element, NULL);NULL != attribute;attribute=scew_attribute_next(sub_element, attribute)){
                if(0==strcmp(scew_attribute_name(attribute),"name")){
                    name= string(scew_attribute_value(attribute));
                }
            }
            contents= scew_element_contents(sub_element);
            if(NULL != contents){
                amount= doubleFromCString(contents,amount);
            }
            pp->push_back(Stack(name,amount));
        }
    }

    return pp;
}
