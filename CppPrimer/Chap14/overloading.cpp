#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*14.2*/
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const string &s) : bookNo(s) {}
    string isbn() const {return bookNo;}
    Sales_data & operator+=(const Sales_data &);
    Sales_data & operator-=(const Sales_data &);
    Sales_data & operator=(const string &isbn);
private:
    double avg_price() const {return units_sold ? revenue/units_sold : 0;}
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
friend ostream & operator<< (ostream &, const Sales_data&);
friend istream & operator>> (istream &, Sales_data&);
friend Sales_data operator- (const Sales_data&, const Sales_data&);
friend Sales_data operator+ (const Sales_data&, const Sales_data&);
};
Sales_data operator+ (const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;

    /*14.21*/
    /*Sales_data sum = lhs;
    sum.units_sold += rhs.units_sold;
    sum.revenue += rhs.revenue;
    return sum;*/

}
Sales_data & Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;

    /*14.21*/
    /**this = (*this) + rhs;
    return *this;   */
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
Sales_data & Sales_data::operator-=(const Sales_data &rhs){
    units_sold -= rhs.units_sold;
    revenue -= rhs.revenue;
    return *this;
}
Sales_data operator- (const Sales_data& lhs, const Sales_data&rhs) {
    Sales_data ret = lhs;
    ret -= rhs;
    return ret;
}
Sales_data& Sales_data::operator=(const string &isbn) {
    bookNo = isbn;
    return *this;
}


class Date {
public:
    Date() {}
    Date(int y, int m, int d) {year = y; month = m; day = d;}
    Date& operator=(const string&);
private:
    int year, month, day;
friend ostream& operator<< (ostream&, const Date&);
friend istream& operator>> (istream&, Date&);
friend bool operator== (const Date&, const Date&);
friend bool operator< (const Date&, const Date&);
friend bool operator<= (const Date&, const Date&);
friend bool operator> (const Date&, const Date&);
friend bool operator>= (const Date&, const Date&);
};
Date& Date::operator=(const string &s) {
    istringstream in(s);
    char ch1, ch2;
    in >> year >> ch1 >> month >> ch2 >> day;
    if (!in || ch1 != '-' || ch2 != '-')
        throw std::invalid_argument("Bad date");
    if (month < 1 || month >12 || day < 1 || day > 31)
        throw std::invalid_argument("Bad date");
    return *this;
}
ostream& operator<< (ostream& os, const Date& date) {
    os << "year: " << date.year << " month: " << date.month << " day: " << date.day;
    return os;
}
istream& operator>> (istream& is, Date& date) {
    is >> date.year >> date.month >> date.day;
    if (!is) 
        date = Date();
    return is;
}
bool operator== (const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year &&
            lhs.month == rhs.month &&
            lhs.day == rhs.day;
}
bool operator!= (const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}
bool operator< (const Date& lhs, const Date& rhs) {
    return (lhs.year < rhs.year) ||
            (lhs.year == rhs.year && lhs.month < rhs.month) ||
            (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day);
}
bool operator<= (const Date& lhs, const Date& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}
bool operator> (const Date& lhs, const Date& rhs) {
    return !(lhs <= rhs);
}
bool operator>= (const Date& lhs, const Date& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}


int main() {


    return 0;
}