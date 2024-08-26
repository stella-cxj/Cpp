#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Quote{
public:
    Quote() = default;
    Quote(const string &book = "", double sales_price = 0.0): bookNo(book), price(sales_price) {
       // cout << "Quote constructor" << endl;
    }
    string isbn() const {return bookNo;}
    virtual double net_price(size_t n) const { return n * price;}
    virtual void debug() const {
        cout << "bookNo = " << bookNo << ", price = " << price << endl;
    }
    virtual ~Quote() {
     //   cout << "Quote destructor" << endl;
    }
    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
friend ostream& operator<< (ostream&, const Quote&);
private:
    string bookNo;
protected:
    double price = 0.0;
};
ostream& operator<< (ostream& os, const Quote& q) {
    os << "Quote operator << " << q.bookNo << " at " << q.price << endl;
    return os;
}

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const string& book, double p, size_t q, double disc): 
                Quote(book, p), quantity(q), discount(disc) {/*cout << "Disc_quote constructor" << endl;*/}
    double net_price(size_t n) const = 0;
    ~Disc_quote() {/*cout << "Disc_quote destructor" << endl;*/ }
protected:
    size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const string& book = "", double p = 0.0, size_t q = 0, double disc = 0.0): 
                Disc_quote(book, p, q, disc) {/*cout << "Bulk_quote constructor" << endl;*/}

/*    using Disc_quote::Disc_quote;*/
    double net_price(size_t) const override;
    void debug() const {
        Quote::debug();
        cout << "min_qty = " << quantity << ", discount = " << discount << endl;
    }
    ~Bulk_quote() {/*cout << "Bulk_quote destructor" << endl;*/}
    Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}
friend ostream& operator<< (ostream&, const Bulk_quote&);
};
double Bulk_quote::net_price(size_t n) const {
    if (n >= quantity) 
        return n * (1 - discount) * price;
    else
        return n * price;
}
ostream& operator<< (ostream& os, const Bulk_quote& bq) {
    os << "Bulk_quote operator << " << bq.isbn() << " at " << bq.price 
        << ", discount " << bq.discount << " at quantity " << bq.quantity << endl;
    return os;
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

class Basket {
public:
    void add_item(const Quote &sale) {
        items.insert(shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale) {
        items.insert(shared_ptr<Quote>(std::move(sale).clone()));
    }
    double total_receipt(ostream&) const;
private:
    static bool compare(const shared_ptr<Quote> &lhs,
                        const shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    multiset<shared_ptr<Quote>, decltype(compare)*> items{compare};
};
double Basket::total_receipt(ostream& os) const {
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); 
                iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << endl; 
    return sum;
}

void trans(string &s) {

    for (auto i = s.begin(); i != s.end();) {
        *i = tolower(*i);
        if (ispunct(*i)) {
            i = s.erase(i);
        } else {
            ++i;
        }
    }
}
class QueryResult {
public:
    QueryResult() = default;
    QueryResult(shared_ptr<vector<string>> txt, shared_ptr<set<int>> lineno, const string &str) : text(txt), line_no(lineno), s(str) {}
    ostream & print(ostream & os) const {
        os << this->s << " occurs " << this->line_no->size() << " times." << endl;
        for (auto i = this->line_no->begin(); i != this->line_no->end(); i++) {
            os << "\t" << "(line " << *i << ") " << (*(this->text))[*i - 1] << endl;
        }
        return os;
    }
    set<int>::iterator begin() {return line_no->begin();}
    set<int>::iterator end() {return line_no->end();}
    shared_ptr<vector<string>> get_file() {return text;}
    ~QueryResult() {}
private:
    int total_time = 0;
    string s;
    shared_ptr<vector<string>> text;
    shared_ptr<set<int>> line_no;
};

class TextQuery {
public:
    TextQuery() = default;
    TextQuery(ifstream &);
    QueryResult query(const string &);
    ~TextQuery() {}
private:
    shared_ptr<vector<string>> text;
    map<string, set<int>> word_line;
};

TextQuery::TextQuery (ifstream &in) {
    
    this->text = make_shared<vector<string>>();

    string line;
    int line_no = 0;
    while(getline(in, line)) {
        line_no++;
        this->text->push_back(line);
        istringstream stream(line);
        string word;        
        while (stream >> word) {
            trans(word);
            this->word_line[word].insert(line_no);
        }
    }
}

QueryResult TextQuery::query(const string &s) {
    auto pset = make_shared<set<int>>(this->word_line[s]);
    QueryResult qr(this->text, pset, s);
    return qr;
}

int main() {
    
    Quote q = {"pupupu", 15.9};
    Bulk_quote bq = {"papap", 15.9, 10, 0.1};
    auto price = print_total(cout, q, 10);
    price = print_total(cout, bq, 10);

    /*15.26*/
    Quote base("C++ Primer", 128.0);
    Bulk_quote bulk("C++ Primer Practice", 99.0, 5, 0.19);
    cout<<base<<endl;
    cout<<bulk<<endl;

    /*15.28*/
    vector<Quote> vecq;
    int quantity = 5;
    for (auto i = 0; i < quantity; i++)
        vecq.push_back(bulk);
    double sum = 0;
    for (auto i : vecq)
        sum += i.net_price(quantity);
    cout << "sum= " << sum << endl;
  
    /*15.29*/
    vector<shared_ptr<Quote>> pq;
    quantity = 5;
    for (auto i = 0; i < quantity; i++)
        pq.push_back(make_shared<Bulk_quote>(bulk));
    sum = 0;
    for (auto i : pq)
        sum += i->net_price(quantity);
    cout << "sum= " << sum << endl;

    
    return 0;
}