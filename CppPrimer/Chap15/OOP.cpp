#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

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
string make_plural(size_t ctr, const string &word, const string &ending = "s") {
    return (ctr > 1) ? word+ending : word;
}
class QueryResult; // declaration needed for return type in the query function
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const; 
private:
    std::shared_ptr<std::vector<std::string>> file; // input file
    // maps each word to the set of the lines in which that word appears
    std::map<std::string, 
	         std::shared_ptr<std::set<line_no>>> wm;  

};
TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    while (getline(is, text)) {       // for each line in the file
		file->push_back(text);        // remember this line of text
		int n = file->size() - 1;     // the current line number
		istringstream line(text);     // separate the line into words
		string word;               
		while (line >> word) {        // for each word in that line
            trans(word);
            // if word isn't already in wm, subscripting adds a new entry
            auto &lines = wm[word]; // lines is a shared_ptr 
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new set<line_no>); // allocate a new set
            lines->insert(n);      // insert this line number
		}
	}
}

class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	typedef std::vector<std::string>::size_type line_no;
	typedef std::set<line_no>::const_iterator line_it;
	QueryResult(std::string s, 
	            std::shared_ptr<std::set<line_no>> p, 
	            std::shared_ptr<std::vector<std::string>> f):
		sought(s), lines(p), file(f) { }
	std::set<line_no>::size_type size() const  { return lines->size(); }
	line_it begin() const { return lines->cbegin(); }
	line_it end() const   { return lines->cend(); }
	std::shared_ptr<std::vector<std::string>> get_file() { return file; }
private:
	std::string sought;  // word this query represents
	std::shared_ptr<std::set<line_no>> lines; // lines it's on
	std::shared_ptr<std::vector<std::string>> file;  //input file
};

ostream &print(ostream & os, const QueryResult &qr)
{
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;

    // print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set 
		// don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") " 
		   << *(qr.file->begin() + num) << endl;

	return os;
}
QueryResult TextQuery::query(const string &sought) const
{
	// we'll return a pointer to this set if we don't find sought
	static shared_ptr<set<line_no>> nodata(new set<line_no>); 

    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);

	if (loc == wm.end()) 
		return QueryResult(sought, nodata, file);  // not found
	else 
		return QueryResult(sought, loc->second, file);
}

class Query_base {
friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

class Query {
friend Query operator~(const Query&);
friend Query operator&(const Query&, const Query&);
friend Query operator|(const Query&, const Query&);
public:
    Query(const string&);
    QueryResult eval(const TextQuery& t) const {return q->eval(t);}
    string rep() const {return q->rep();}
private:
    Query(shared_ptr<Query_base> query): q(query) {}
    shared_ptr<Query_base> q;
};
ostream& operator<<(ostream &os, const Query &query){
    return os << query.rep();
}

class WordQuery : public Query_base{
friend class Query;
    WordQuery(const string &s): query_word(s) {}
    QueryResult eval(const TextQuery& t) const {return t.query(query_word);}
    string rep() const {return query_word;}
    string query_word;
};
inline Query::Query(const string &s): q(new WordQuery(s)) {}
class NotQuery: public Query_base{
friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) {}
    string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};
inline Query operator~(const Query &operand) {
    return shared_ptr<Query_base>(new NotQuery(operand));
}
QueryResult NotQuery::eval(const TextQuery& text) const {
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        if (beg == end || *beg != n)
            ret_lines->insert(n);
        else if (beg != end)
            ++beg;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}
class BinaryQuery: public Query_base{
protected:
    BinaryQuery(const Query &l, const Query &r, string s):
        lhs(l), rhs(r), opSym(s) {}
    string rep() const {return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";}
    Query lhs, rhs;
    string opSym;
};
class AndQuery: public BinaryQuery {
friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right): BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator&(const Query& lhs, const Query& rhs) {
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
QueryResult AndQuery::eval(const TextQuery& text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left.begin(), left.end(),
                     right.begin(), right.end(), 
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}
class OrQuery: public BinaryQuery {
friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right): BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query& lhs, const Query& rhs) {
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
QueryResult OrQuery::eval(const TextQuery& text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
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

    /*15.36*/
    ifstream file("words");
    TextQuery tQuery(file);
    Query qu = Query("fiery") & Query("bird") | Query("wind");
    print(cout, qu.eval(tQuery));

    return 0;
}