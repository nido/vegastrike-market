#include "Reserve.hpp"

Reserve::Reserve(){
    this->reserve=0.0;
    this->reserveValue=0.0;
}

double Reserve::getReserve(){
    return this->reserve;
}

double Reserve::getReserveValue(){
    return this->reserveValue;
}

double Reserve::getPrice(){
    if(this->reserve>0.001){//fudge factor for catching rounding errors
cerr<<"calculating price "<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
        return this->reserveValue/this->reserve;
    }else if(this->reserve>=-0.001){//fudge factor for catching rounding errors
        return 0.0;
    }else{
cerr<<"Resource negative:"<<this->reserve<<endl;
        return 0.0;
    }
}

void Reserve::addReserve(double amount,double total,string why){
    assert(amount>=0.0);
//cerr<<why<<"!"<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
    this->reserve+= amount;
    this->reserveValue+= total;
//cerr<<why<<" "<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
}

void Reserve::subtractReserve(double amount,string why){
    assert(amount>=0.0);
//cerr<<why<<"!"<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
    this->reserveValue-= amount*this->getPrice();
    this->reserve-= amount;
//cerr<<why<<" "<<"reserve="<<this->reserve<<" @total="<<this->reserveValue<<endl;
}
