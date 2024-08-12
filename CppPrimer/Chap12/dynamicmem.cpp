#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

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

    return 0;
}
