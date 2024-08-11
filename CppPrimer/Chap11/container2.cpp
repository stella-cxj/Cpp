#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
/*11.4*/
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
/*11.11*/
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

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() < rhs.isbn();
}
typedef bool (*pf)(const Sales_data &, const Sales_data &);
multiset<Sales_data, pf> bookstore(compareIsbn);

/*11.31*/
void print(const multimap<string, string> &m) {
    for (auto i : m)
        cout << i.first << " " << i.second << endl;
}

/*11.33*/

map<string, string> buildMap(ifstream &rule ) {
    map<string, string> trans_map;
    string line;
    string key, value;
    while(rule >> key) {
        getline(rule, line);
        value = line.substr(1);
        trans_map[key] = value;
    }
    return trans_map;
}

const string & transform(const string &s, const map<string, string> &trans_map) {
    auto s_iter = trans_map.find(s);
    if (s_iter != trans_map.end()) {
        return s_iter->second;
    } else {
        return s;
    }
}
void word_transform(ifstream &in, ifstream &rule) {

    auto trans_map = buildMap(rule);
    string text;
    while(getline(in, text)) {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word) {
            if (firstword) {
                firstword = false;
            } else {
                cout << " ";
            }
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}
/*11.38*/
unordered_map<string, string> buildMap_unordered(ifstream &rule ) {
    unordered_map<string, string> trans_map;
    string line;
    string key, value;
    while(rule >> key) {
        getline(rule, line);
        value = line.substr(1);
        trans_map[key] = value;
    }
    return trans_map;
}
const string & transform(const string &s, const unordered_map<string, string> &trans_map) {
    auto s_iter = trans_map.find(s);
    if (s_iter != trans_map.end()) {
        return s_iter->second;
    } else {
        return s;
    }
}

int main() {

    /*11.3*/     /*11.4*/
    map<string, size_t> words;
    string word;
    cout << "Please input some words:" << endl;
    while(cin >> word) {
        trans(word);
        ++words[word];
    }
    for (auto i : words) {
        cout << i.first << " occurs " << i.second << " times."  << endl;
    }
    cin.clear();

    /*11.7*/ /*11.14*/
    map<string, vector<pair<string, string>>> names;
    string name, kid, birthday;
    cout << "Please enter a new family name: " << endl;
    while (cin >> name) {
        names[name] = {};
        cout << "Please enter names and birthdays to the family " << name << endl;
        while(cin >> kid) {
            cin >> birthday;
            names[name].push_back(make_pair(kid, birthday));
        }
        cin.clear();
        cout << "Please enter next family name: " << endl;
    }
    cin.clear();
    for (auto j : names) {
        cout << "Family " << j.first << " has kids: " << endl;
        for (auto i : j.second) {
            cout << i.first << " whose birthday is " << i.second << endl;
        }
    }
    
    /*11.8*/
    vector<int> ivec;
    set<int> iset;
    cout << "Please enter some integers: " << endl;
    int i;
    while(cin >> i) {
        if (find(ivec.begin(), ivec.end(), i) == ivec.end()) {
            ivec.push_back(i);
        }
        iset.insert(i);
    }
    for (auto i : ivec) {cout << i << " "; } cout << endl;
    for (auto i : iset) {cout << i << " "; } cout << endl;
    cin.clear();

    /*11.9*/
    map<string, list<int>> word_line;
    ifstream in("words");
    string line, word9;
    int lineno = 0;
    while(getline(in, line)) {
        lineno++;
        istringstream l_in(line);
        while (l_in >> word9) {
            trans(word9);
            word_line[word9].push_back(lineno);
        }
    }
    for (auto i : word_line) {
        cout << "word " << i.first << " is at ";
        for (auto j : i.second ) {
            cout << j << " ";
        }
        cout << endl;
    }

    /*11.12*/ /*11.13*/
    vector<pair<string, int>> pvec;
    string s;
    int i12;;
    cout << "Please input pairs of string and int:" << endl;
    while (cin >> s) {
        cin >> i12;
        pvec.push_back(make_pair(s, i12));
        pair<string, int> p(s, i12);
        pvec.push_back(p);
        pair<string, int> p1 = {s, i12};
        pvec.push_back(p1);
    }
    for (auto i : pvec) {cout << i.first << " - " << i.second << endl;}
    cin.clear();
    
    /*11.16*/
    map<string, int> map16;
    map<string, int>::iterator it_map = map16.begin();
    it_map = map16.insert(it_map, make_pair("123", 123));
    for (auto i : map16) {cout << i.first << i.second << endl;}

    /*11.17*/
    multiset<string> c = {"a", "b", "c"};
    vector<string> v = {"aa", "bb", "cc"};
    copy(v.begin(), v.end(), inserter(c, c.end())); //把vector拷到multiset
    for (auto i : c) {cout << i << " ";} cout << endl;

    /*11.18*/
    map<string, size_t> map1;
    map<const string, size_t>::iterator map_it;
    map_it = map1.begin();

    /*11.19*/
    typedef bool (*pf)(const Sales_data &, const Sales_data &);
    multiset<Sales_data, pf> bookstore(compareIsbn);
    multiset<Sales_data, pf>::iterator iter = bookstore.begin();   

    /*11.20*/
    map<string, size_t> words20;
    string word20;
    cout << "Please input some words:" << endl;
    while(cin >> word20) {
        trans(word20);
        //++words[word];
        auto ret = words20.insert({word20, 1});
        if (!ret.second) {
            ++ret.first->second;
        }
    }
    for (auto i : words20) {
        cout << i.first << " occurs " << i.second << " times."  << endl;
    }
    cin.clear();

    /*11.22*/
    map<string, vector<int>> map22;
    pair<map<string, vector<int>>::iterator ,bool> ret = map22.insert({"abc", {1,2,3}});

    /*11.23*/
    multimap<string, vector<string>> names23;
    string name23, kid23;
    cout << "Please enter a new family name: " << endl;
    while (cin >> name23) {
        auto ret = names23.insert({name23, {}});
        cout << "Please enter names to the family " << name << endl;
        while(cin >> kid23) {
            ret->second.push_back(kid23);
        }
        cin.clear();
        cout << "Please enter next family name: " << endl;
    }
    cin.clear();
    for (auto j : names23) {
        cout << "Family " << j.first << " has kids: " << endl;
        for (auto i : j.second) {
            cout << i << endl;
        }
    }
   
    /*11.28*/   
    map<string, vector<int>> map28;
    map<string, vector<int>>::iterator iter28 = map28.find("s");
    
    /*11.31*/
    multimap<string, string> author;
    author.insert({"JinYong", "ShenDiaoXiaLv"});
    author.insert({"JinYong", "TianLongBaBu"});
    author.insert({"GuLong", "XiaoLiFeiDao"});
    author.insert({"GuLong", "HarryPotter"});
    print(author);
    auto book = author.begin();
    while (book != author.end()) {
        book = author.find("JinYong");
        book = author.erase(book);
    }
    print(author);

    /*11.32*/
    author.insert({"JinYong", "ShenDiaoXiaLv"});
    author.insert({"JinYong", "TianLongBaBu"});
    print(author);

    /*11.33*/
    ifstream in_file("input"), rule_file("rule");
    word_transform(in_file, rule_file);

    /*11.38*/ 
    unordered_map<string, size_t> words38;
    string word38;
    cout << "Please input some words:" << endl;
    while(cin >> word38) {
        ++words38[word38];
    }
    for (auto i : words38) {
        cout << i.first << " occurs " << i.second << " times."  << endl;
    }
    cin.clear();

    ifstream in_file38("input"), rule_file38("rule");
    auto trans_map = buildMap_unordered(rule_file38);
    string text;
    while(getline(in_file38, text)) {
        istringstream stream(text);
        string word;
        bool firstword = true;
        while (stream >> word) {
            if (firstword) {
                firstword = false;
            } else {
                cout << " ";
            }
            cout << transform(word, trans_map);
        }
        cout << endl;
    }

    return 0;
}


