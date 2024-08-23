#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <map>

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
    explicit operator string() const {return bookNo;}
    explicit operator double() const {return revenue;}

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
    explicit operator bool() {
        vector<vector<int>> days_per_month = {
            {31,28,31,30,31,30,31,31,30,31,30,31},
            {31,29,31,30,31,30,31,31,30,31,30,31}
        };
        return 1 <= month && month <=12 && 1 <= day && 
               day <= days_per_month[is_LeapYear()?1:0][month - 1];
    }
    bool is_LeapYear() {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
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

/*14.34*/
class Condi {
public:
    Condi(){};
    int operator()(int a, int b, int c){
        return a ? b : c;
    }
};

/*14.35*/
class ReadString{
public:
    ReadString(istream &is = cin) : input(is){}
    string operator()(){
        string s;
        if (!getline(input, s))
            s = "";
        return s;
    }
private:
    istream &input;
};

/*14.37*/
class Equal {
public:
    Equal(){}
    bool operator()(int a, int b) {return a==b;}
};

/*14.38*/
class LengthEqual{
public:
    LengthEqual(){}
    bool operator()(const string &s, int length) {
        return s.size() == length;
    }
};
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

/*14.39*/
class LengthBetween{
public:
    LengthBetween(int minv, int maxv): min(minv), max(maxv){}
    bool operator()(const string &s) {
        return (s.size() >= min) && (s.size() <= max);
    }
private:
    int min;
    int max;
};
class LengthNotShorter{
public:
    LengthNotShorter(int minv): lower(minv){}
    bool operator()(const string &s) {
        return (s.size() >= lower);
    }
private:
    int lower;
};

class StringLesser {
public:
    StringLesser(){}
    bool operator()(const string &a, const string &b) {
        return a.size() < b.size();
    }
};
class StringNotLess{
public:
    StringNotLess(int sz): size(sz) {}
    bool operator()(const string &a) {
        return a.size() >= size;
    }
private:
    int size;
};
class PrintString {
public:
    PrintString(){}
    ostream& operator()(const string &s) {cout << s << " ";}
};
/*14.40*/
void elimDups(vector<string> &words)
{
    // sort words alphabetically so we can find the duplicates
    sort(words.begin(), words.end());
	for_each(words.begin(), words.end(), 
	         [](const string &s) { cout << s << " "; });
	cout << endl;


    // unique reorders the input so that each word appears once in the
    // front part of the range 
	// returns an iterator one past the unique range
    auto end_unique = unique(words.begin(), words.end());
	for_each(words.begin(), words.end(), 
	         [](const string &s) { cout << s << " "; });
	cout << endl;

    // erase uses a vector operation to remove the nonunique elements
    words.erase(end_unique, words.end());
	for_each(words.begin(), words.end(), 
	         [](const string &s) { cout << s << " "; });
	cout << endl;
}
void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    StringLesser lesser;
    StringNotLess notLesser(sz);
    stable_sort(words.begin(), words.end(), lesser);
    auto wc = find_if(words.begin(), words.end(), notLesser);
    auto count = words.end() - wc;
    cout << count << " words of length " << sz << " or longer" << endl;
    PrintString print;
    for_each(wc, words.end(), print);
    cout << endl;
}

/*14.44*/
int add(int i, int j) {return i+j;}
auto mod = [](int i, int j){return i%j;};
struct divide {
    int operator()(int denominator, int divisor) {return denominator/divisor;}
};


int main() {

    /*14.36*/
    vector<string> ivec;
    ReadString read;
    cout << "Please enter some strings" << endl;
    while(true) {
        string s = read();
        if (!s.empty())
            ivec.push_back(s);
        else
            break;
    }
    for (auto i : ivec) cout << i << " ";
    cout << endl;
    cin.clear();

    /*14.37*/
    vector<int> ivec37 = {1,2,3,4,3,4,5};
    int oldV = 4, newV = 400;
    Equal eq;
    replace_if(ivec37.begin(), ivec37.end(), bind(eq, std::placeholders::_1, oldV), newV);
    for (auto i : ivec37) cout << i << " ";
    cout << endl;

    /*14.38*/
    LengthEqual lengthequal;
    ifstream infile("words");
    vector<string> words;
    int min = 1, max = 10;
    string word;
    while (infile >> word) {
        trans(word);
        words.push_back(word);
    }
    for (auto i = min; i <= max; i++) {
        auto count = count_if(words.begin(), words.end(), bind(lengthequal, std::placeholders::_1, i));
        cout << "length " << i << " : " << count << endl;
    }
    cout << endl;

    /*14.39*/
    LengthNotShorter lengthNotShorter(10);
    LengthBetween lengthBetween(1, 9);
    auto count = count_if(words.begin(), words.end(), lengthNotShorter);
    cout << "length not shorter than 10: " << count << endl;
    count = count_if(words.begin(), words.end(), lengthBetween);
    cout << "length between 1~9: " << count << endl;

    /*14.40*/
    biggies(words, 5);

    /*4.42*/
    vector<int> ivec42 = {4000, 5000, 1023, 1024, 1025, 1000, 7000};
    auto c = count_if(ivec42.begin(), ivec42.end(), bind2nd(greater<int>(), 1024));
    cout << c << " greater than 1024." << endl;
    vector<string> svec42 = {"pooh", "pooh", "pooh", "pooh", "abc", "pooh", "b"};
    auto s = find_if(svec42.begin(), svec42.end(), bind2nd(not_equal_to<string>(), "pooh"));
    cout << "first word not pooh is " << *s << endl;
    transform(ivec42.begin(), ivec42.end(), ivec42.begin(), bind2nd(multiplies<int>(), 2));
    for_each(ivec42.begin(), ivec42.end(), [](const int &i) { cout << i << " "; });
    cout << endl;

    /*14.43*/
    int div = 2;
    vector<int> ivec43 = {2,3,4,6,8,9};
    auto count43 = count_if(ivec43.begin(), ivec43.end(), bind2nd(modulus<int>(), div));
    cout << count43 << " in the vector cannot divided by 2" << endl;

    /*14.44*/
    map<string, function<int(int,int)>> binops = {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", divide()},
        {"*", [](int i, int j){return i*j;}},
        {"%", mod}
    };
    int left, right;
    string op;
    while (true) {
        cout << "left operand:";
        if (cin >> left) {
            cout << "op: " ;
            if (cin >> op) {
                cout << "right operand: " ;
                if (cin >> right) {
                    cout << binops[op](left, right) << endl;
                }
                else break;
            } else break;
        } else break;
    }
    cin.clear();


    return 0;
}

