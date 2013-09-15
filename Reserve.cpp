#include <assert.h>
#include "Reserve.hpp"
#include "Market.hpp"

Reserve::Reserve()
{
    this->reserve = 0.0;
    this->reserveValue = 0.0;
}

double Reserve::getReserve()
{
    return this->reserve;
}

double Reserve::getReserveValue()
{
    return this->reserveValue;
}

double Reserve::getPrice()
{
    if (this->reserve > 0.001) {    //fudge factor for catching rounding errors
        return this->reserveValue / this->reserve;
    } else if (this->reserve >= -0.001) {   //fudge factor for catching rounding errors
        return 0.0;
    } else {
        return 0.0;
    }
}

void Reserve::addReserve(double amount, double total, std::string why)
{
    assert(amount >= 0.0);
//cerr<<why<<"!"<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
    this->reserve += amount;
    this->reserveValue += total;
//cerr<<why<<" "<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
}

void Reserve::subtractReserve(double amount, std::string why)
{
    assert(amount >= 0.0);
//cerr<<why<<"!"<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
    this->reserveValue -= amount * this->getPrice();
    this->reserve -= amount;
//cerr<<why<<" "<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
}

Reserve *Reserve::reserveFromElement(scew_element * root)
{
    Reserve *pr = NULL;
    scew_element *element = NULL;
    XML_Char const *contents = NULL;

    double reserve = 0.0;
    double reserveValue = 0.0;

    element = scew_element_by_name(root, "reserveCount");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            reserve = doubleFromCString(contents, reserve);
        }
    }

    element = scew_element_by_name(root, "reserveValue");
    if (NULL != element) {
        contents = scew_element_contents(element);
        if (NULL != contents) {
            reserveValue = doubleFromCString(contents, reserve);
        }
    }

    if (reserve > 0.0) {
        pr = new Reserve();
        pr->reserve = reserve;
        pr->reserveValue = reserveValue;
    }

    return pr;
}

void Reserve::addElement(scew_element * root) const const
{
    scew_element *element = NULL;

    element = scew_element_add(root, "reserveCount");
    scew_element_set_contents(element, toCString(reserve));
    element = scew_element_add(root, "reserveValue");
    scew_element_set_contents(element, toCString(reserveValue));
}
