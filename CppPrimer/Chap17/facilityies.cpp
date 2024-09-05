#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <set>
#include <sstream>
#include <fstream>
#include <map>


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


    return 0;
}