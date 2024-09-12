#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <set>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <regex>
#include <random>
#include <iomanip>

using namespace std;

/*17.3*/
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
typedef tuple<shared_ptr<vector<string>>, shared_ptr<set<int>>, string> QueryResult;
ostream & qr_print(ostream & os, QueryResult qr) {
    os << get<2>(qr) << " occurs " << get<1>(qr)->size() << " times." << endl;
    for (auto i = get<1>(qr)->begin(); i != get<1>(qr)->end(); i++) {
        os << "\t" << "(line " << *i << ") " << (*(get<0>(qr)))[*i - 1] << endl;
    }
    return os;
}
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

/*17.4*/
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const string &s) : bookNo(s) {}
    string isbn() const {return bookNo;}
    Sales_data& operator+=(const Sales_data&);
private:
    double avg_price() const {return units_sold ? revenue/units_sold : 0;}
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
friend std::ostream &operator<<(ostream&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
};
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() < rhs.isbn();
}
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;  
	sum += rhs;            
	return sum;
}
ostream &operator<<(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " 
	   << item.revenue << " " << item.avg_price();
	return os;
}
typedef tuple<vector<Sales_data>::size_type, 
            vector<Sales_data>::const_iterator, 
            vector<Sales_data>::const_iterator> matches;
typedef pair<vector<Sales_data>::size_type, 
            pair<vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator>> pmatches;
class Cmatches{
public:
    Cmatches() = default;
    Cmatches(vector<Sales_data>::size_type n, 
            pair<vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator>p): 
            num(n), first(p.first), last(p.second) {}
    vector<Sales_data>::size_type get_num() const {return num;}
    vector<Sales_data>::const_iterator get_first() const {return first;}
    vector<Sales_data>::const_iterator get_last() const {return last;}
private:
    vector<Sales_data>::size_type num;
    vector<Sales_data>::const_iterator first, last;
};
vector<matches> findBook(const vector<vector<Sales_data>>&files,
                        const string &book) {

    vector<matches> ret;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (found.first != found.second)
            ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
    }
    return ret;
}
/*17.5*/
vector<pmatches> findBook1(const vector<vector<Sales_data>>&files,
                        const string &book) {

    vector<pmatches> ret;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (found.first != found.second)
            ret.push_back(make_pair(it - files.cbegin(), make_pair(found.first, found.second)));
    }
    return ret;
}
/*17.6*/
vector<Cmatches> findBook2(const vector<vector<Sales_data>>&files,
                        const string &book) {

    vector<Cmatches> ret;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (found.first != found.second)
            ret.push_back(Cmatches(it - files.cbegin(), make_pair(found.first, found.second)));
    }
    return ret;
}
void reportResults(istream &in, ostream &os, 
                    const vector<vector<Sales_data>> &files) {
    string s;
    while(in >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            cout << s << " not found in any stores" << endl;
            continue;
        }
        for (const auto &store : trans) {
            os << "store " << get<0>(store) << " sales: " 
                << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
        }
    }
}
istream &read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}
bool lt(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}
vector<Sales_data> build_store(const string &s)
{
	Sales_data item;
	vector<Sales_data> ret;
	ifstream is(s);
	while (read(is, item))
		ret.push_back(item);
	sort (ret.begin(), ret.end(), lt);  // need sort for equal_range to work
	return ret;
}
/*17.13*/
template <size_t N>
class exam {
public:
    exam():s(){}
    size_t get_size() {return N;}
    void set_solution(size_t n, bool b) {s.set(n, b);}
    bitset<N> get_solution() const {return s;}
    size_t score(const bitset<N> &a);
private:
    bitset<N> s;
};
template<size_t N>
size_t exam<N>::score(const bitset<N> &a) {
    size_t ret = 0;
    for (size_t i = 0; i < N; i++)
        if (s[i] == a[i])
            ret++;
    return ret;
}
/*17.20*/
bool valid(const smatch& m) {
    if (m[1].matched)
        return m[3].matched && 
            (m[4].matched == 0 || (m[4].str() != "-" && m[4].str() != "."));
    else
        return !m[3].matched && 
            ((m[4].str() == "-" && m[6].str() == "-") ||
            (m[4].str() == "." && m[6].str() == ".") ||
            (m[4].str() != "-" && m[4].str() == "." && m[6].str() != "-" && m[6].str() == "."));
}

/*17.28*/
unsigned int random(long seed = -1, long min = 1, long max = 0) {
    static uniform_int_distribution<unsigned> u(0, 9999);
    static default_random_engine e;
    if (seed >= 0)
        e.seed(seed);
    if (min <= max)
        u = uniform_int_distribution<unsigned>(min, max);
    return u(e);
}
int main() {

    /*17.1*/
    tuple<int, int, int> three_int{10, 20, 30};
    /*17.2*/
    tuple<string, vector<string>, pair<string, int>> t;

    /*17.3*/
    ifstream infile("..\\Chap12\\words");
    TextQuery tq(infile);
    while(true) {
        cout << "1. enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        const QueryResult& qr = tq.query(s);
        qr_print(cout, qr) << endl;
    }
    infile.close();
    cin.clear();    

    /*17.4*/
    vector<vector<Sales_data>> files;
	files.push_back(build_store("store1"));
	files.push_back(build_store("store2"));
	files.push_back(build_store("store3"));
	files.push_back(build_store("store4"));
    cout << "Input book name to find, CtrlZ to stop:" << endl;
    reportResults(cin, cout, files);
    cin.clear();

    /*17.10*/
    unsigned ul = (1 << 21) | (1 << 13) | (1 << 8) | (1 << 5) | (1 << 3) | (1 << 2) | 2;
    bitset<32> b32(ul);
    cout << b32 << endl;

    bitset<32> bs32;
    bs32.set(21);bs32.set(13);bs32.set(8);bs32.set(5);
    bs32.set(3);bs32.set(2);bs32.set(1);
    cout << bs32 << endl;

    /*17.13*/
    exam<80> e;
    e.set_solution(0, 1);
    e.set_solution(79, 1);
    cout << e.get_solution() << endl;

    bitset<80> a;
    cout << e.get_size() << " questions, corret: " << e.score(a) << endl;

    /*17.14*/
    try {
        regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
        smatch results;
        string filename;
        cout << "Please enter a file name:" << endl;
        while(cin >> filename)
            if (regex_search(filename, results, r))
                cout << results.str() << endl;
    } catch (regex_error e)
    {cout << e.what() << "\ncode: " << e.code() << endl;}
    cin.clear();

    /*17.15*/
    regex r("[[:alpha:]]*[^c]ei[[:alpha:]]*");
    smatch results;
    string s = "freind thief theif friend receipt reciept";
    for (sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
        cout << it->str() << endl;

    /*17.20*/
    string phone = "(\\()?(\\d{3})(\\))?([-.]|(\\s)*)?(\\d{3})([-.]|(\\s)*)?(\\d{4})";
    regex re(phone);
    smatch m;
    string ss;
    ifstream infile20("phonesFinal");
    while(getline(infile20, ss)) {
        for (sregex_iterator it(ss.begin(), ss.end(), re), end_it; it != end_it; ++it) {
            if (valid(*it))
                cout << "Valid: " << it->str() << endl;
            else
                cout << "Invalid: " << it->str() << endl;
        }
    }
    infile20.close();

    /*17.23*/
    string code = "(\\d{5})((-?)(\\d{4}))?";
    
    /*17.24*/
    string phone24 = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
    regex r24(phone24);
    smatch m24;
    string s24;
    string fmt = "$2.$5.$7";
    ifstream infile24("phonesFinal");
    while(getline(infile24, s24)) {
        cout << regex_replace(s24, r24, fmt) << endl;
    }
    infile24.close();

    /*17.28*/
    for (auto i = 0; i < 10; i++)
        cout << random() << " ";
    cout << endl;
    cout << random(0) << " ";
    for (auto i = 0; i < 9; i++)
        cout << random() << " ";
    cout << endl;
    cout << random(19743) << " ";
    for (auto i = 0; i < 9; i++)
        cout << random() << " ";
    cout << endl;
    cout << random(19743, 0, 5000) << " ";
    for (auto i = 0; i < 9; i++)
        cout << random() << " ";
    cout << endl;
   
    /*17.4.2*/
    default_random_engine ee;
    normal_distribution<> n(4, 1.5);
    vector<unsigned> vals(9);
    for (size_t i=0;i!=200;++i) {
        unsigned v = lround(n(ee));
        if (v<vals.size()) ++vals[v];
    }
    for (size_t j=0; j!=vals.size();++j)
        cout<<j<<": " << string(vals[j], '*')<<endl;

    /*17.34*/
    cout << unitbuf;
    cout<<setw(20) <<"default format:" << 100*sqrt(2.0)<<'\n'
        <<setw(20) <<"scientific: "<<scientific<<100*sqrt(2.0)<<'\n'
        <<setw(20) <<"fixed decimal:" << fixed<<100*sqrt(2.0)<<'\n'
        <<setw(20) <<"hexadecimal:" << hexfloat<<100*sqrt(2.0)<<'\n'
        <<setw(20) <<"use defaults: "<<defaultfloat<<100*sqrt(2.0)<<"\n\n";
    cout<<nounitbuf;
    cout<<"hi!"<<endl;
    cout<<"hi!"<<flush;
    cout<<"hi!"<<ends;
    char ch;
    cin >> noskipws;
    while(cin>>ch)
        cout<<ch;
    cout<<endl;cin.clear();
    cin>>skipws;
    while(cin>>ch)
        cout<<ch;    
    cout<<endl;cin.clear();

    /*17.37*/
    ifstream in("phonesFinal");
    char line[50];
    while(!in.eof()) {
        in.getline(line, 30);
        cout<<line;
        //cout<<in.gcount()<<endl;
        if (!in.good())
            if (in.gcount() == 29) 
                in.clear();
            else
                break;
        else    
            cout <<endl;
    }
    return 0;
}
