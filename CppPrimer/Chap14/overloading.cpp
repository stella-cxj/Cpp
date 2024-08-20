#include <iostream>
#include <string>

using namespace std;

/*14.2*/
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const string &s) : bookNo(s) {}
    string isbn() const {return bookNo;}
    Sales_data & operator+=(const Sales_data &);
private:
    double avg_price() const {return units_sold ? revenue/units_sold : 0;}
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
friend ostream & operator<< (ostream &, const Sales_data&);
friend istream & operator>> (istream &, Sales_data&);
};
Sales_data operator+ (const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}
Sales_data & Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
ostream & operator<< (ostream &os, const Sales_data& item) {
	os << item.isbn() << " " << item.units_sold << " " 
	   << item.revenue << " " << item.avg_price();
	return os;
}
istream & operator>> (istream &is, Sales_data& item) {
	double price; 
	is >> item.bookNo >> item.units_sold >> price;
	if (is)       
    	item.revenue = item.units_sold * price;
	else
    	item = Sales_data(); 
	return is;
}

int main() {


    return 0;
}