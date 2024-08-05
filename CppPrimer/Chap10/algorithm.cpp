#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <numeric>

using namespace std;

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
    return 0;
}   