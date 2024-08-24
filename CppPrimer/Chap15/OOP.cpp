#include <iostream>
#include <string>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string &book, double sales_price): bookNo(book), price(sales_price) {}
    string isbn() const {return bookNo;}
    virtual double net_price(size_t n) const { return n * price;}
    virtual void debug() const {
        cout << "bookNo = " << bookNo << ", price = " << price << endl;
    }
    virtual ~Quote() = default;
private:
    string bookNo;
protected:
    double price = 0.0;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const string& book, double p, size_t q, double disc): 
                Quote(book, p), quantity(q), discount(disc) {}
    double net_price(size_t n) const = 0;
protected:
    size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book, double p, size_t q, double disc): 
                Disc_quote(book, p, q, disc) {}
    double net_price(size_t) const override;
    void debug() const {
        Quote::debug();
        cout << "min_qty = " << quantity << ", discount = " << discount << endl;
    }
};
double Bulk_quote::net_price(size_t n) const {
    if (n >= quantity) 
        return n * (1 - discount) * price;
    else
        return n * price;
}

class Limit_quote : public Disc_quote {
public:
    Limit_quote() = default;
    Limit_quote(const string &book, double p, size_t q, double disc):
                Disc_quote(book, p, q, disc){}
    double net_price(size_t) const override;
    void debug() const {
        Quote::debug();
        cout << "max_qty = " << quantity << ", discount = " << discount << endl;
    }    
};
double Limit_quote::net_price(size_t n) const {
    if (n <= quantity)
        return (n * (1 - discount) * price);
    else
        return quantity * (1 - discount) * price + (n - quantity) * price;
}

double print_total(ostream& os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() 
        << " # sold: " << n
        << " total due: " << ret << endl;
    return ret;
}
int main() {
    
    Quote q = {"pupupu", 15.9};
    Bulk_quote bq = {"papap", 15.9, 10, 0.1};
    auto price = print_total(cout, q, 10);
    price = print_total(cout, bq, 10);
     
     

    return 0;
}