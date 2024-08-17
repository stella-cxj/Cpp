#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <set>

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
    X& operator=(const X&) {cout << "X& operator=" << endl;}
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


    return 0;
}

