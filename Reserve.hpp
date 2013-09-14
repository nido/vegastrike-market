#include <string>
#include "scew/scew.h"

class Reserve {
public:
    Reserve();
    double getReserve();
    double getReserveValue();
    double getPrice();
    void addReserve(double amount,double total,std::string why);
    void subtractReserve(double amount, std::string why);
	void addElement(scew_element* root) const;
    static Reserve *reserveFromElement(scew_element* root);
private:
    double reserve;
    double reserveValue;
};
