#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

/*13.5*/
class HasPtr {
public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}
    HasPtr(const HasPtr &c) {
        ps = new string(*c.ps);
        i = c.i;
        cout << "copy constructor" << endl;
    }
    HasPtr & operator= (const HasPtr &c) {
        auto newp = new string(*c.ps);
        delete ps;
        ps = newp;
        i = c.i;
        cout << "copy operator" << endl;
        return *this;
    }
    HasPtr & operator= (HasPtr &&c) noexcept {
        if (this != &c) {
            delete ps;
            ps = c.ps;
            i = c.i;
            c.ps = nullptr;
            c.i = 0;
        }
        return *this;
    }
    HasPtr & operator= (const string &s) {
        *ps = s;
        return *this;
    }
    string& operator* () {
        return *ps;
    }
    bool operator< (const HasPtr &rhs) const {
        return *(this->ps) < *(rhs.ps);
    }
    ~HasPtr() {
        delete ps;
    }
private:
    string *ps;
    int i;
friend void swap(HasPtr &, HasPtr &);
};
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    cout << "HasPtr.swap called" << endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

/*13.13*/
struct X {
    X() {cout << "X()" << endl;}
    X(const X&) {cout << "X(const X&)" << endl;}
    X& operator=(const X&) {cout << "X& operator=" << endl; return *this;}
    ~X() {cout << "~X()" << endl;}
};

void func1(X x) {
    cout << "func1" << endl;
    return;
}
void func2(X& x) {
    cout << "func2" << endl;
    return;
}
/*13.14*/
class numbered {
public:
    numbered() {mysn = currsn++;}
    numbered(const numbered& n) {mysn = currsn++;}
    int mysn;
private:
    static int currsn;
};
int numbered::currsn = 0;
void f(numbered& s) {cout << s.mysn << endl;}

/*13.18*/
class Employee {
public:
    Employee() {sn = seq++;}
    Employee(const string& employee) : name(employee) {sn=seq++;}
    Employee(const Employee &e) {sn=seq++; name = e.name;}
    Employee & operator= (const Employee &e) {
        name = e.name;
        return *this;
    }
private:
    string name;
    int sn;
    static int seq;
};
int Employee::seq = 0;
/*13.26*/
class StrBlobPtr;
class StrBlob {
public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
    StrBlob(const StrBlob& s) {
        data = make_shared<vector<string>>(*s.data);
    }
    StrBlob & operator= (const StrBlob& s) {
        data = make_shared<vector<string>>(*s.data);
        return *this;
    }
    vector<string>::size_type size() const {return data->size();}
    void push_back(const string &t) {data->push_back(t);}
    void push_back(string &&t) {data->push_back(std::move(t));}
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
bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    if (l == r) 
        return (!r || lhs.curr == rhs.curr);
    else    
        return false;
}

/*13.27*/
class HasPtr1 {
public:
    HasPtr1(const string &s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {}
    HasPtr1(const HasPtr1 &c) : ps(c.ps), i(c.i), use(c.use) {++*use;}
    HasPtr1 & operator= (const HasPtr1 &c) {
        ++*c.use;
        if (--*use == 0) {
            delete ps;
            delete use;
        }        
        ps = c.ps;
        i = c.i;
        use = c.use;
        return *this;
    }
    HasPtr1 & operator= (const string &s) {
        *ps = s;
        return *this;
    }
    string& operator* () {
        return *ps;
    }
    ~HasPtr1() {
        if (--*use == 0) {
            delete ps;
            delete use;
        }        
    }
private:
    string *ps;
    int i;
    size_t *use;
};

/*13.28*/
class TreeNode{
public:
    TreeNode(): value(""), count(new int(1)), left(nullptr), right(nullptr){}
    TreeNode(const TreeNode& t): value(t.value), count(t.count), left(t.left), right(t.right) {
        ++(*count);
    }
    TreeNode& operator= (const TreeNode& t) {
        if (this != &t) {
            if (--(*count)==0) {
                delete count;
                delete left;
                delete right;                
            }
            value = t.value;
            count = t.count;
            left = t.left;
            right = t.right;
            ++(*count);
        }
        return *this;
    }
    ~TreeNode() {
        if (count && --(*count) == 0) {
            delete count;
            delete left;
            delete right;
        }
    }
private:
    string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
friend class BinStrTree;     
};
class BinStrTree{
public:
    BinStrTree(): root(nullptr) {}
    BinStrTree(const BinStrTree& b) : root(b.root) {
        if (root) {
            ++(*root->count);
        }
    }
    BinStrTree& operator=(const BinStrTree& b) {
        if (this!=&b) {
            if (root && (*root->count) == 0) {
                delete root;
            }
            root = b.root;
            if (root) {
                ++(*root->count);
            }
        }
        return *this;
    }
    ~BinStrTree() {
        if (root && --(*root->count) == 0)
            delete root;
    }
private:
    TreeNode *root;
};

/*13.34*/
class Folder;
class Message{
friend class Folder;
friend void swap(Message &, Message &);
public:
    explicit Message(const string &s = ""): contents(s) {}
    Message(const Message&);
    Message& operator=(const Message&);
    Message(Message &&m);
    Message& operator=(Message &&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
private:
    string contents;
    set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
    void addFldr(Folder *f) {folders.insert(f);}
    void remFldr(Folder *f) {folders.erase(f);}
    void move_Folders(Message *);
};
Message::Message(const Message& m): contents(m.contents), folders(m.folders) {
    add_to_Folders(m);
}
Message& Message::operator=(const Message &m) {
    remove_from_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
    return *this;
}
Message::~Message() {
    remove_from_Folders();
}
Message::Message(Message &&m): contents(std::move(m.contents)) {
    move_Folders(&m);
}
Message& Message::operator=(Message &&rhs) {
    if (this != &rhs) {
        remove_from_Folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}
class Folder{
friend class Message;
friend void swap(Message &, Message &);
public:
    Folder() {}
    Folder(const Folder& f): messages(f.messages) {
        add_to_Messages(f);
    }
    Folder& operator=(const Folder& f) {
        remove_from_Msgs();
        messages = f.messages;
        add_to_Messages(f);
        return *this;
    }
    ~Folder() {
        remove_from_Msgs();
    }

private:
    set<Message*> messages;
    void addMsg(Message *m){messages.insert(m);}
    void remMsg(Message *m){messages.erase(m);}
    void add_to_Messages(const Folder &f) {
        for (auto msg : f.messages) {
            msg->addFldr(this);
        }
    }
    void remove_from_Msgs() {
        while (!messages.empty()) {
            (*messages.begin())->remove(*this);
        }
    }
};

void Message::save(Folder& f) {
    folders.insert(&f);
    f.addMsg(this);
}
void Message::remove(Folder& f) {
    folders.erase(&f);
    f.remMsg(this);
}
void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders) {
        f->addMsg(this);
    }
}
void Message::remove_from_Folders() {
    for (auto f : folders) {
        f->remMsg(this);
    }
}
void swap(Message &lhs, Message &rhs) {
    using std::swap;
    for (auto f : lhs.folders) {f->remMsg(&lhs);}
    for (auto f : rhs.folders) {f->remMsg(&rhs);}
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders) {f->addMsg(&lhs);}
    for (auto f : rhs.folders) {f->addMsg(&rhs);}
}
void Message::move_Folders(Message *m) {
    folders = std::move(m->folders);
    for (auto f : folders) {
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear();
}


/*13.39*/
class StrVec {
public:
    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(StrVec &&) noexcept;
    ~StrVec();
    void push_back(const string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    string *begin() const {return elements;}
    string *end() const {return first_free;}
    void reserve(size_t n) {if (n > capacity()) reallocate(n);}
    inline void resize(size_t);
    inline void resize(size_t, const string &);
    
private:
    static allocator<string> alloc;
    void chk_n_alloc() { if (size() == capacity()) reallocate();}
    pair<string*, string*> alloc_n_copy(const string*, const string*);
    void free();
    inline void reallocate();
    inline void reallocate(size_t);
    string *elements;
    string *first_free;
    string *cap;
};
allocator<string> StrVec::alloc;
void StrVec::push_back(const string& s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};

}
void StrVec::free() {
    if (elements) {
        for_each(elements, first_free, 
                [](string &s){alloc.destroy(&s);});
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(initializer_list<string> il) {
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec() {
    free();
}
StrVec& StrVec::operator=(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
StrVec::StrVec(StrVec &&rhs) noexcept : elements(rhs.elements),
                              first_free(rhs.first_free),
                              cap(rhs.cap) {
    rhs.elements = nullptr;
    rhs.first_free = nullptr;
    rhs.cap = nullptr;
}
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = nullptr;
        rhs.first_free = nullptr;
        rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reallocate(){
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = uninitialized_copy(make_move_iterator(begin()), 
                                    make_move_iterator(end()),
                                    first);   
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}
void StrVec::reallocate(size_t newcapacity){
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i) {
        alloc.construct(dest++, std::move(*elem++));
    }
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
inline void StrVec::resize(size_t n) {
    if (n > size()) {
        while(size() < n) {
            push_back("");
        }
    } else if(n < size()) {
        while(size() > n) {
            alloc.destroy(--first_free);
        }
    }
}
inline void StrVec::resize(size_t n, const string &s) {
    if (n > size()) {
        while(size() < n) {
            push_back(s);
        }
    }
}

/*13.42*/
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
    QueryResult(shared_ptr<StrVec> txt, shared_ptr<set<int>> lineno, const string &str) : text(txt), line_no(lineno), s(str) {}
    ostream & print(ostream & os) const {
        os << this->s << " occurs " << this->line_no->size() << " times." << endl;
        for (auto i = this->line_no->begin(); i != this->line_no->end(); i++) {
            os << "\t" << "(line " << *i << ") " << *(this->text->begin() + (*i-1)) << endl;
        }
        return os;
    }
    set<int>::iterator begin() {return line_no->begin();}
    set<int>::iterator end() {return line_no->end();}
    shared_ptr<StrVec> get_file() {return text;}
    ~QueryResult() {}
private:
    int total_time = 0;
    string s;
    shared_ptr<StrVec> text;
    shared_ptr<set<int>> line_no;
};

class TextQuery {
public:
    TextQuery() = default;
    TextQuery(ifstream &);
    QueryResult query(const string &);
    ~TextQuery() {}
private:
    shared_ptr<StrVec> text;
    map<string, set<int>> word_line;
};

TextQuery::TextQuery (ifstream &in) {
    
    this->text = make_shared<StrVec>();

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

/*13.44*/
class String{
friend ostream &operator<<(ostream&, const String&);
public:
    String() = default;
    String(const char *cp) : 
	          sz(std::strlen(cp)), p(a.allocate(sz))
	          { std::uninitialized_copy(cp, cp + sz, p); }

	String(const String &s):sz(s.sz), p(a.allocate(s.sz))
	          { cout << "String copy constructor" << endl;
                std::uninitialized_copy(s.p, s.p + sz , p); }

	String(String &&s) noexcept : sz(s.size()), p(s.p) 
	          { cout << "String move constructor" << endl;
              s.p = 0; s.sz = 0; }

    String &operator=(const String &);              
    String &operator=(const char*);
    String &operator=(String &&) noexcept;
   	~String() noexcept { if (p) a.deallocate(p, sz); }
	const char *begin() { return p; }
	const char *begin() const { return p; }
	const char *end() { return p + sz; }
	const char *end() const { return p + sz; }
	size_t size() const { return sz; }
private:
    static allocator<char> a;
    size_t sz = 0;
    char *p = nullptr;
};
allocator<char> String::a;
String & String::operator=(const String &rhs) {
    cout << "String copy = operator" << endl;
    auto newp = a.allocate(rhs.sz); 
	uninitialized_copy(rhs.p, rhs.p + rhs.sz, newp);
	if (p)
		a.deallocate(p, sz); 
	p = newp;    
	sz = rhs.sz; 
    return *this;     
}
String & String::operator=(const char *cp) {
	if (p) a.deallocate(p, sz);
	p = a.allocate(sz = strlen(cp));
	uninitialized_copy(cp, cp + sz, p);
	return *this;
}
String & String::operator=(String &&rhs) noexcept {
    cout << "String move = operator" << endl;
    if (this != &rhs) {
        if (p) a.deallocate(p, sz);
        sz = rhs.size(); p = rhs.p;
        rhs.p = nullptr; rhs.sz = 0; 
    }
    return *this;
}
ostream &operator<<(ostream &os, const String &s){
	auto p = s.begin();
	while (p != s.end())
		os << *p++ ;
	return os;
}

/*13.58*/
class Foo {
public:
    Foo sorted() &&;
    Foo sorted() const &;
private:
    vector<int> data;
};
Foo Foo::sorted() && {
    cout << "Rvalue version" << endl;
    sort(data.begin(), data.end());
    return *this;
}
Foo Foo::sorted() const & {
    cout << "Lvalue version" << endl;
    //sort(ret.data.begin(), ret.data.end());
    return Foo(*this).sorted();
}


int main() {
    /*13.13*/
    X x;
    func1(x);
    func2(x);
    cout << "new x" << endl;
    auto px = new X;
    cout << "delete x" << endl;
    delete px;
    
    vector<X> xvec(1,x);
    xvec.push_back(x);

    cout << "init y by x" << endl;
    X y=x;
    cout << "copy x to y" << endl;
    y=x;

    /*13.14*/
    numbered a, b = a, c = b;
    f(a);f(b);f(c);
    /*13.26*/
    StrBlob b1; 
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << "b2.size=" << b2.size() << ", front is " << b2.front() << ", back is " << b2.back() << endl;
    }
    cout << "b1.size=" << b1.size() << ", front is " << b1.front() << ", back is " << b1.back() << endl;

    StrBlob b3 = b1;
    b3.push_back("next");
    cout << "b3.size=" << b3.size() << ", front is " << b3.front() << ", back is " << b3.back() << endl;

    StrBlobPtr p1(b1.begin());
    while (!eq(p1, b1.end())) {
        cout << "b1 " << p1.deref() << endl;
        p1.incr();
    }

    /*13.27*/
    HasPtr1 h("hi mom!");
    HasPtr1 h2 = h;
    h = "hi dad!";
    cout << "h=" << *h << endl;
    cout << "h2=" << *h2 << endl;

    /*13.30*/
    HasPtr hh("hi mom!");
    HasPtr hh2(hh);
    HasPtr hh3 = hh;
    hh2 = "hi dad!";
    hh3 = "hi son!";
    swap(hh2, hh3);
    cout << "hh: " << *hh << endl;
    cout << "hh2: " << *hh2 << endl;
    cout << "hh3: " << *hh3 << endl;

    /*13.31*/
    vector<HasPtr> hvec;
    hvec.push_back(hh);
    hvec.push_back(hh2);
    hvec.push_back(hh3);
    sort(hvec.begin(), hvec.end());
    for (auto i : hvec) {cout << *i << endl;}

    /*13.42*/
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

    /*13.47*/
    String s1("One"), s2("Two");
    cout << s1 << " " << s2 << endl;
    String s3(s2);
    cout << s1 << " " << s2 << " " << s3 << endl;
    s3 = s1;
    cout << s1 << " " << s2 << " " << s3 << endl;
    s3 = String("Three");
    cout << s1 << " " << s2 << " " << s3 << endl;

    vector<String> vs;
    //vs.reserve(4);
    vs.push_back(s1);
    for_each(vs.begin(), vs.end(), [](const String &s){cout << s << " ";});
    cout << endl;

    vs.push_back(std::move(s2));
    for_each(vs.begin(), vs.end(), [](const String &s){cout << s << " ";});
    cout << endl;

    vs.push_back(String("Three"));
    for_each(vs.begin(), vs.end(), [](const String &s){cout << s << " ";});
    cout << endl;
    
    vs.push_back("Four");
    for_each(vs.begin(), vs.end(), [](const String &s){cout << s << " ";});
    cout << endl;

    /*13.58*/
    Foo f;
    f.sorted();
    return 0;
}

