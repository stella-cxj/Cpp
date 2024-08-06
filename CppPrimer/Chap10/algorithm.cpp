#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::placeholders;

/*10.9*/
void print(const vector<string> &svec) {
    for (auto i : svec) {cout << i << "\t";} cout << endl;
}

void elimDupl(vector<string> &svec) {

    sort(svec.begin(), svec.end());
    print(svec);

    auto unique_end = unique(svec.begin(), svec.end());
    print(svec);
    
    svec.erase(unique_end, svec.end());
    print(svec);
} 

bool isShorter(const string &s1, const string &s2) {
    return (s1.size() < s2.size());
}

/*10.12*/
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(const string &s) : bookNo(s) {}
    string isbn() const {return bookNo;}

private:
    double avg_price() const {return units_sold ? revenue/units_sold : 0;}
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

bool compareIsbn(const Sales_data &obj1, const Sales_data &obj2) {
    return (obj1.isbn() < obj2.isbn());
}

void print(const vector<Sales_data> &obj) {
    for (auto i : obj) {
        cout << i.isbn() << "\t";
    }
    cout << endl;
}

/*10.13*/
bool longer_than5(const string &s) {
    return (s.size() >= 5);
}

/*10.16*/    //biggies 求一个string vector中，大于等于一个给定长度的单词有多少并输出
void biggies(vector<string> &svec, vector<string>::size_type s) {

    elimDupl(svec);
    stable_sort(svec.begin(), svec.end(), isShorter);

    auto i = find_if(svec.begin(), svec.end(), [s](const string &a){return (a.size() > s);});
    cout << "There are " << (svec.end() - i) << " words longer than " << s << " : " ;
    for_each(i, svec.end(), [](const string &s){cout << s << "  ";});
    cout << endl;
}

/*10.18*/    //用partition替代find_if
void biggies2(vector<string> &svec, vector<string>::size_type s) {

    elimDupl(svec);
    stable_sort(svec.begin(), svec.end(), isShorter);

    auto i = partition(svec.begin(), svec.end(), [s](const string &a){return (a.size() <= s);});
    cout << "There are " << (svec.end() - i) << " words longer than " << s << " : " ;
    for_each(i, svec.end(), [](const string &s){cout << s << "  ";});
    cout << endl;
}

/*10.19*/    //用stable_partition替代partition
void biggies3(vector<string> &svec, vector<string>::size_type s) {

    elimDupl(svec);
    stable_sort(svec.begin(), svec.end(), isShorter);

    auto i = stable_partition(svec.begin(), svec.end(), [s](const string &a){return (a.size() <= s);});
    cout << "There are " << (svec.end() - i) << " words longer than " << s << " : " ;
    for_each(i, svec.end(), [](const string &s){cout << s << "  ";});
    cout << endl;
}

/*20.22*/
bool less_than(int size, const string &s) {
    return (s.size() <= size);
}

/*10.24*/
bool check_size(const string &s, string::size_type sz) {
    return (s.size() <= sz);
}

/*10.25*/ //用check_size和bind重写此函数
void biggies4(vector<string> &svec, vector<string>::size_type s) {

    elimDupl(svec);
    stable_sort(svec.begin(), svec.end(), isShorter);

    auto i = partition(svec.begin(), svec.end(), bind(check_size, _1, s));
    cout << "There are " << (svec.end() - i) << " words longer than " << s << " : " ;
    for_each(i, svec.end(), [](const string &s){cout << s << "  ";});
    cout << endl;
}

int main() {
    
    /*10.1*/
    vector<int> ivec;
    int i;
    cout << "Please enter some integers:" << endl;
    while(cin >> i) {
        ivec.push_back(i);
    }
    int counter = count(ivec.cbegin(), ivec.cend(), 5);
    cout << "There are " << counter << " 5 in your input." << endl;
    cin.clear();

    /*10.2*/
    list<string> slist;
    string s;
    cout << "Please enter some strings:" << endl;
    while(cin >> s) {
        slist.push_back(s);
    }
    counter = count(slist.cbegin(), slist.cend(), "5");
    cout << "There are " << counter << " 5 in your input." << endl;
    cin.clear();

    /*10.3*/
    vector<int> ivec2 = {1,2,3,4,5};
    int sum = accumulate(ivec2.cbegin(), ivec2.cend(), 0);
    cout << "sum is " << sum << endl;

    /*10.6*/
    list<int> ilist(10,6);
    fill_n(ilist.begin(), ilist.size(), 0);
    for (auto i : ilist) {
        cout << i << "\t";
    }
    cout << endl;

    /*10.9*/
    vector<string> svec = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    print(svec);
    elimDupl(svec);

    stable_sort(svec.begin(), svec.end(), isShorter);
    print(svec);
    
    /*10.12*/
    vector<Sales_data> Svec = {Sales_data("123"), 
                               Sales_data("122343-51"),
                               Sales_data("2343-512"),
                               Sales_data("162343-51"),
                               Sales_data("92343-51")};
    print(Svec);
    sort(Svec.begin(), Svec.end(), compareIsbn);
    print(Svec);

    /*10.13*/
    vector<string> svec13 = {"fox", "jumeep", "owefeqver", "fox", "red", "thrweqwde", "red", "fox", "the"};
    auto index = partition(svec13.begin(), svec13.end(), longer_than5);
    for (auto i = svec13.begin(); i != index; i++) {
        cout << *i << "\t";
    }
    cout << endl;

    /*10.14*/
    auto f = [](int a, int b) -> int {return (a+b);};
    cout << f(1,2) << endl;
    
    /*10.15*/
    int b = 5;
    auto f15 = [b](int a) -> int {return (b+a);};
    cout << f15(5) << endl;

    /*10.16*/
    vector<string> svec16 = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    biggies(svec16, 3);

    /*10.17*/
    Svec = {Sales_data("123"), 
            Sales_data("122343-51"),
            Sales_data("2343-512"),
            Sales_data("162343-51"),
            Sales_data("92343-51")};
    print(Svec);
    sort(Svec.begin(), Svec.end(), [](const Sales_data &s1, const Sales_data &s2){return (s1.isbn() < s2.isbn());});
    print(Svec);

    /*10.18*/
    vector<string> svec18 = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    biggies2(svec18, 3);

    /*10.19*/
    vector<string> svec19 = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    biggies3(svec19, 3);

    /*10.20*/
    vector<string> svec20 = {"fox", "jumpfasdd", "over", "fofasdfa"};
    int size = 6;
    auto count = count_if(svec20.begin(), svec20.end(), [=](const string &s){return (s.size() > size);});
    cout << "There're " << count << " words longer than " << size << endl;
    
    /*10.21*/
    int val = 5;
    auto f21 = [val]() mutable ->bool {
        int ret = (val == 0);
        if (val > 0) {
            val--;
        }
        return ret;
    };
    for (auto i = 0; i < 7; i++) {
        cout << "i = " << i << ", val is 0: " << f21() << endl;
    }

    /*10.22*/
    vector<string> svec22 = {"fox", "jumpfasdd", "over", "fofasdfa"};
    int size22 = 6;
    auto count22 = count_if(svec22.begin(), svec22.end(), bind(less_than, size22, _1));
    cout << "There're " << count22 << " words longer than " << size22 << endl;
    
    /*10.24*/
    vector<int> ivec24 = {3,5,14,5,3,1,3,65};
    string s24 = "abcdef";
    auto i24 = find_if(ivec24.begin(), ivec24.end(), bind(check_size, s24, _1));
    cout << "The first value bigger than s24 is " << *i24 << endl;

    /*10.25*/
    vector<string> svec25 = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    biggies4(svec25, 3);


    return 0;
}

