#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <numeric>
#include <functional>
#include <fstream>
#include <iterator>
#include "Sales_item.h"

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

bool compareIsbn12(const Sales_data &obj1, const Sales_data &obj2) {
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
    sort(Svec.begin(), Svec.end(), compareIsbn12);
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

    /*10.27*/
    vector<int> ivec27 = {1,1,2,3,3,7,7,7,7,2,45,4,4};
    list<int> ilist27;
    sort(ivec27.begin(), ivec27.end());
    unique_copy(ivec27.begin(), ivec27.end(), inserter(ilist27, ilist27.begin()));
    for_each(ilist27.begin(), ilist27.end(), [](const int &i){cout << i << "\t";});
    cout << endl;

    /*10.28*/
    vector<int> ivec28 = {1,2,3,4,5,6,7,8,9};
    vector<int> ivec_b, ivec_i;
    list<int> ilist28_f;
    copy(ivec28.begin(), ivec28.end(), inserter(ivec_i, ivec_i.begin()));
    for_each(ivec_i.begin(), ivec_i.end(), [](const int &i){cout << i << "\t";});
    cout << endl;
    copy(ivec28.begin(), ivec28.end(), back_inserter(ivec_b));
    for_each(ivec_b.begin(), ivec_b.end(), [](const int &i){cout << i << "\t";});
    cout << endl;
    copy(ivec28.begin(), ivec28.end(), front_inserter(ilist28_f));
    for_each(ilist28_f.begin(), ilist28_f.end(), [](const int &i){cout << i << "\t";});
    cout << endl;

    /*10.29*/
    fstream in("words");
    istream_iterator<string> i_iter(in), eof;
    vector<string> svec29(i_iter, eof);
    for_each(svec29.begin(), svec29.end(), [](const string &i){cout << i << " ";});
    cout << endl;
    in.close();

    /*10.30*/
    cout << "Please input some integers:" << endl;
    istream_iterator<int> i_iter30(cin), eof30;
    vector<int> ivec30(i_iter30, eof30);
    sort(ivec30.begin(), ivec30.end());
    ostream_iterator<int> o_iter30(cout, " ");
    copy(ivec30.begin(), ivec30.end(), o_iter30);
    cout << endl;
    cin.clear();

    /*10.31*/
    cout << "Please input some integers:" << endl;
    istream_iterator<int> i_iter31(cin), eof31;
    vector<int> ivec31(i_iter31, eof31);
    sort(ivec31.begin(), ivec31.end());
    ostream_iterator<int> o_iter31(cout, " ");
    unique_copy(ivec31.begin(), ivec31.end(), o_iter31);
    cout << endl;
    cin.clear();
    
    /*10.32*/
    vector<Sales_item> vs;
    cout << "Please input some Sales_items:" << endl;
    istream_iterator<Sales_item> in_iter(cin), eof32;
    while(in_iter != eof32) {
        vs.push_back(*in_iter++);
    }
    sort(vs.begin(), vs.end(), compareIsbn);
    auto l = vs.begin();
    while (l != vs.end()) {
        auto item = *l;
        auto r = find_if(l+1, vs.end(),
                        [item](const Sales_item &item1){return (item1.isbn() != item.isbn());}
                        );
        cout << accumulate(l+1, r, item) << endl;
        l = r;
    }
    
    /*10.33*/
    fstream in33("int");
    ofstream out1("out1"), out2("out2");
    istream_iterator<int> i_iter33(in33), eof33;
    vector<int> ivec33(i_iter33, eof33);
    ostream_iterator<int> o_iter1(out1, " "), o_iter2(out2, "\n");
    for (auto i : ivec33) {
        if ((i % 2) == 0) {
            *o_iter2++ = i;
        } else {
            *o_iter1++ = i;
        }
    }

    /*10.34*/
    vector<int> ivec34 = {1,2,3,4,5};
    ostream_iterator<int> o_iter34(cout, " ");
    copy(ivec34.rbegin(), ivec34.rend(), o_iter34);    
    cout << endl;

    /*10.35*/
    for (auto i = ivec34.end(); i != ivec34.begin(); --i) {
        cout << *(i-1) << " ";
    }
    cout << endl;
    
    /*10.36*/
    list<int> ilist36 = {2,236,64,2,0,8,0,9,0,3,2};
    auto r0 = find(ilist36.rbegin(), ilist36.rend(), 0);
    cout << distance(ilist36.rbegin(), r0) << endl;

    /*10.37*/
    vector<int> ivec37 = {1,2,3,4,5,6,7,8,9,10};
    list<int> ilist37;
    copy((ivec37.rbegin() + 3), (ivec37.rbegin() + 8), back_inserter(ilist37));
    for (auto i : ilist37) {cout << i << " ";} 
    cout << endl;

    /*10.42*/
    list<string> slist42 = {"fox", "jump", "over", "fox", "red", "the", "red", "fox", "the"};
    slist42.sort();
    slist42.unique();
    for (auto i : slist42) {cout << i << " ";} cout << endl;

    return 0;
}

