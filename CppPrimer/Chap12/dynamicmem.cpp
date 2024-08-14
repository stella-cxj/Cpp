#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <set>

using namespace std;
/*12.2*/
class StrBlobPtr;
class StrBlob {
public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
    vector<string>::size_type size() const {return data->size();}
    void push_back(const string &t) {data->push_back(t);}
    void pop_back() {data->pop_back();}
    string & front() {return data->front();}
    string & back() {return data->back();}
    string & front() const {return data->front();}
    string & back() const {return data->back();}
    StrBlobPtr begin();
    StrBlobPtr end();
    StrBlobPtr begin() const;
    StrBlobPtr end() const;
private:
    shared_ptr<vector<string>> data;
friend class StrBlobPtr;
};
/*12.19*/
class StrBlobPtr {
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    string & deref() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    StrBlobPtr& incr() {
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }
private:
    shared_ptr<vector<string>> check(size_t i, const string &msg) const {
        auto ret = wptr.lock();
        if (!ret) 
            throw runtime_error("unbound StrBlobPtr");
        if (i >= ret->size()) 
            throw out_of_range(msg);
        return ret;
    }
    weak_ptr<vector<string>> wptr;
    size_t curr;
friend bool eq(const StrBlobPtr &, const StrBlobPtr &);
};

StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}
StrBlobPtr StrBlob::begin() const {
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() const {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

/*12.20*/
bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    if (l == r) 
        return (!r || lhs.curr == rhs.curr);
    else    
        return false;
}

/*12.6*/
vector<int> * func6() {
    auto *p = new vector<int>;
    return p;
}
void func_in(vector<int> *ivec) {
    int i;
    cout << "Please enter some integers: " << endl;
    while(cin >> i) {
        ivec->push_back(i);
    }
    cin.clear();
}
void func_out(vector<int> *ivec) {
    for (auto i : *ivec) {
        cout << i << " ";
    }
    cout << endl;
    delete ivec;
}
/*12.7*/
shared_ptr<vector<int>> func7() {
    auto p = make_shared<vector<int>>();
    return p;
}
void func_in7(shared_ptr<vector<int>> p) {
    int i;
    cout << "Please enter some integers: " << endl;
    while(cin >> i) {
        p->push_back(i);
    }
    cin.clear();
}
void func_out7(shared_ptr<vector<int>> p) {
    for (auto i : *p) {
        cout << i << " ";
    }
    cout << endl;
}

/*12.14*/ /*12.15*/
struct connection {int a;};
struct destination {int b;};
connection connect(destination*) {return {0};}
void disconnect(connection) {return;}
void end_connection(connection *p) {disconnect(*p);}
void f(destination &d) {
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
}
void f1(destination &d) {
    connection c = connect(&d);
    shared_ptr<connection> p(&c, [](connection *p){disconnect(*p);});
}

/*12.27*/
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
/*12.28*/
void query(string word, vector<string> &txt, map<string, set<int>> &smap) {

    auto sset = smap[word];
    cout << word << " occurs " << sset.size() << " times." << endl;
    for (auto i = sset.begin(); i != sset.end(); ++i) {
        cout << "\t" << "(line " << *i << ") " << txt[*i - 1] << endl;       
    }

}

void make_map(ifstream &in, vector<string> &txt, map<string, set<int>> &smap) {

    string line;
    int line_no = 0;
    while(getline(in, line)) {
        line_no++;
        txt.push_back(line);
        istringstream stream(line);
        string word;        
        while (stream >> word) {
            trans(word);
            smap[word].insert(line_no);
        }
    }
}


int main() {
    
    /*12.6*/
    vector<int> *ivec = func6();
    func_in(ivec);
    func_out(ivec);
    /*12.7*/
    auto p7 = func7();
    func_in7(p7);
    func_out7(p7);

    /*12.20*/
    ifstream in("words");
    string line;
    StrBlob words;
    while (getline(in, line)) {
        words.push_back(line);
    }
    StrBlobPtr pwords(words.begin());
    while (!eq(pwords, words.end())) {
        cout << pwords.deref() << endl;
        pwords.incr();
    }

    /*12.22*/
    const StrBlob cwords = {"Hello", "world", "!"};
    StrBlobPtr pcwords(cwords.begin());
    while (!eq(pcwords, cwords.end())) {
        cout << pcwords.deref() << " ";
        pcwords.incr();
    }
    cout << endl;

    /*12.23*/
    const char* p1 = "Hello ";
    const char* p2 = "world!";
    char* p = new char[strlen(p1) + strlen(p2) + 1];
    strcpy(p, p1);
    strcat(p, p2);
    cout << p << endl;
    delete [] p;

    string s1 = "Hello ", s2 = "world!";
    string s = s1 + s2;
    cout << s << endl;

    /*12.24*/
    cout << "Please enter a string " << endl;
    string str;
    if (cin >> str) {
        char *ps = new char [str.size()];
        strcpy(ps, str.c_str());
        cout << ps << endl;
        delete [] ps;
    }
    cin.clear();

    /*12.26*/
    allocator<string> alloc;
    size_t size = 0, max_size = 100;
    string s26;
    string *const p26 = alloc.allocate(max_size);
    auto q26 = p26;
    cout << "Please enter some strings: " << endl;
    while((cin >> s26) && (q26 != p26 + max_size)) {
        alloc.construct(q26++, s26);
    }
    for (auto i = p26; i != q26; i++) {
        cout << *i << " ";
    }
    while(q26 != p26) {
        alloc.destroy(q26--);
    }
    alloc.deallocate(p26, max_size);
    cin.clear();

    /*12.27*/
    ifstream infile("words");
    TextQuery tq(infile);
    while(true) {
        cout << "1. enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        const QueryResult& qr = tq.query(s);
        qr.print(cout) << endl;
    }
    infile.close();
    cin.clear();
    
    /*12.28*/
    ifstream infile28("words");
    vector<string> text;
    map<string, set<int>> word_line;
    make_map(infile28, text, word_line);

    while(true) {
        cout << "2. enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        query(s, text, word_line);
    }
    infile28.close();
    cin.clear();
    
    /*12.29*/
    do {
        cout << "3. enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        query(s, text, word_line);
    } while(true);
    cin.clear();

    return 0;
}
