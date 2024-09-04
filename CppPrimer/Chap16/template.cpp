#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <set>
#include <map>

using namespace std;

/*16.2*/
template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}
/*16.4*/
template<typename IT, typename T>
IT find(IT begin, IT end, const T &val) {
    IT i;
    for (i = begin; i != end; i++) {
        if (*i == val)
            return i;
    }
    return i;
}
/*16.6*/
template<typename T, size_t N>
const T* begin(const T (&arr)[N]) {
    return &arr[0];
}
template<typename T, size_t N>
const T* end(const T (&arr)[N]) {
    return &arr[0] + N;
}
/*16.5*/
template<typename T, unsigned N>
void print(const T (&arr)[N]) {
    //for (auto elem : arr)
    for (auto i = begin(arr); i != end(arr); i++)
        cout << *i << " ";
    cout << endl;
}
/*16.7*/
template<typename T, size_t N>
constexpr size_t size(const T (&arr)[N]) {
    return N;
}

/*16.28*/
template<typename T> 
class SP {
public:
    SP(): p(nullptr), use(nullptr) {}
    explicit SP(T* pt): p(pt), use(new size_t(1)) {}
    SP(const SP& sp):p(sp.p), use(sp.use) {if (use) ++*use;}
    SP& operator=(const SP&);
    ~SP();
    T& operator*() {return *p;}
    T& operator*() const {return *p;}
private:
    T *p;
    size_t *use;
};
template<typename T> 
SP<T>::~SP() {
    if (use && --*use == 0){
        delete p;
        delete use;
    }
}
template<typename T> 
SP<T>& SP<T>::operator=(const SP& sp) {
    if (sp.use)
        ++*sp.use;
    if (use && --*use == 0) {
        delete p;
        delete use;
    }
    p = sp.p;
    use = sp.use;
    return *this;
}
template<typename T, class... Args>
SP<T> make_SP(Args&&... args) {
    return SP<T>(new T(forward<Args>(args)...));
}

template<typename T>
class UP {
public:
    UP(): p(nullptr) {}
    UP(const UP&) = delete;
    explicit UP(T* pt): p(pt) {}
    UP& operator=(const UP&) = delete;
    ~UP();
    T* release();
    void reset(T *new_p=nullptr);
    T& operator*() {return *p;}
    T& operator*() const {return *p;}
private:
    T *p;
};
template<typename T>
UP<T>::~UP() {
    if (p)
        delete(p);
}
template<typename T>
void UP<T>::reset(T* new_p) {
    if (p)
        delete p;
    p = new_p;
}
template<typename T>
T* UP<T>::release() {
    T *q = p;
    p = nullptr;
    return q;
}


/*16.12*/
template<typename T> class Blob{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob(): data(make_SP<vector<T>>()) {}
    Blob(initializer_list<T> il): data(make_SP<vector<T>>(il)) {}
    template<typename IT>Blob(IT b, IT e): data(make_SP<vector<T>>(b, e)) {}
    size_type size() const {return (*data).size();}
    bool empty() const {return data->empty();}
    void push_back(const T &t) {data->push_back(t);}
    void push_back(T &&t) {(*data).push_back(std::move(t));}
    void pop_back();
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    T& operator[](size_type i);
    const T& operator[](size_type i) const;
    T& at(size_type);
    const T& at(size_type) const;
private:
    SP<vector<T>> data;
    void check(size_type i, const string &msg) const;
};
template<typename T>
void Blob<T>::check(size_type i, const string &msg) const {
    if (i >= (*data).size())
        throw out_of_range(msg);
}
template<typename T>
T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}
template<typename T>
const T& Blob<T>::operator[](size_type i) const {
    check(i, "subscript out of range");
    return (*data)[i];
}
template<typename T>
T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}
template<typename T>
const T& Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data->back();
}
template<typename T>
T& Blob<T>::front() {
    check(0, "front on empty Blob");
    return data->front();
}
template<typename T>
const T& Blob<T>::front() const {
    check(0, "front on empty Blob");
    return data->front();
}
template<typename T> void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data->pop_back();
}
template <typename T>
T& Blob<T>::at(size_type i) 
{
	check(i, "subscript out of range");
	return (*data)[i]; 
}
template <typename T>
const T&
Blob<T>::at(size_type i) const
{
	check(i, "subscript out of range");
	return (*data)[i];
}
template<typename T> class BlobPtr{
public:
    BlobPtr(): curr(0) {}
    BlobPtr(Blob<T> &a, size_t sz = 0): wptr(a.data), curr(sz) {}
    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++();
    BlobPtr operator++(int);
    BlobPtr& operator--();
private:
    shared_ptr<vector<T>> check(size_t, const string&) const;
    weak_ptr<vector<T>> wptr;
    size_t curr;
};
template<typename T> 
BlobPtr<T> BlobPtr<T>::operator++(int) {
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

/*16.14*/
template<int H, int W> class Screen;
template<int H, int W> ostream& operator<<(ostream &, const Screen<H, W>&);
template<int H, int W> istream& operator>>(istream &, Screen<H, W>&);
template<int H, int W>
class Screen {
friend ostream& operator<< <H,W>(ostream &, const Screen&);
friend istream& operator>> <H,W>(istream &, Screen&);
public:
    Screen() :content(W * H, ' ') {}
    Screen(char c) :content(W * H, c) {}
    char get() const {return content[cursor];}
    inline char get(int, int) const ;
    Screen &clear(char = bkground);
private:
    static const char bkground = ' ';
public:
    Screen &move(int r, int c);
    Screen &set(char c);
    Screen &set(int, int, char);
    Screen &display(ostream &os) {do_display(os); return *this;}
    const Screen &display(ostream &os) const {do_display(os); return *this;}
private:
    void do_display(ostream &os) const {os << content;}
    string content;
    int cursor = 0;
};
template<int H, int W>
Screen<H, W>& Screen<H, W>::clear(char c) {
    content = string(H * W, c);
    return *this;
}
template<int H, int W>
inline Screen<H, W>& Screen<H, W>::move(int r, int c)
{
    cursor = r*W + c;
    return *this;
}
template<int H, int W>
inline Screen<H, W>& Screen<H, W>::set(char c) {
    content[cursor] = c;
    return *this;
}
template<int H, int W>
inline Screen<H, W>& Screen<H, W>::set(int r, int c, char ch) {
    content[r * W + c] = ch;
    return *this;
}
template<int H, int W>
char Screen<H, W>::get(int r, int c) const {
    return content[r*W + c];
}

template<int H, int W>
ostream& operator<<(ostream &os, const Screen<H, W>& s){
    os << s.content;
    return os;
}
template<int H, int W>
istream& operator>>(istream &is, Screen<H, W>& s) {
    string t;
    is >> t;
    s.content = t.substr(0, H * W);
    return is;
}

/*16.16*/
template <typename T> class Vec;
template <typename T> bool operator==(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator< (const Vec<T>&, const Vec<T>&);
template <typename T> bool operator<= (const Vec<T>&, const Vec<T>&);
template <typename T> bool operator> (const Vec<T>&, const Vec<T>&);
template <typename T> bool operator>= (const Vec<T>&, const Vec<T>&);
template <typename T>
class Vec {
public:
    Vec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(initializer_list<T>);
    Vec(const Vec&);
    Vec &operator=(const Vec&);
    Vec(Vec &&) noexcept;
    Vec &operator=(Vec &&) noexcept;
    ~Vec();
    Vec &operator=(initializer_list<T>);
    void push_back(const T&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    T *begin() const {return elements;}
    T *end() const {return first_free;}
    void reserve(size_t n) {if (n > capacity()) reallocate(n);}
    inline void resize(size_t);
    inline void resize(size_t, const T &);
    T& operator[] (size_t i) { return elements[i];}
    const T& operator[] (size_t i) const {return elements[i];}
    
private:
    static allocator<T> alloc;
    void chk_n_alloc() { if (size() == capacity()) reallocate();}
    pair<T*, T*> alloc_n_copy(const T*, const T*);
    void free();
    inline void reallocate();
    inline void reallocate(size_t);
    T *elements;
    T *first_free;
    T *cap;
friend bool operator== <T>(const Vec&, const Vec&);
friend bool operator< <T> (const Vec&, const Vec&);
friend bool operator<= <T> (const Vec&, const Vec&);
friend bool operator> <T> (const Vec&, const Vec&);
friend bool operator>= <T> (const Vec&, const Vec&);
};
template <typename T> allocator<T> Vec<T>::alloc;
template <typename T>
void Vec<T>::push_back(const T& s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
template <typename T>
pair<T*, T*> Vec<T>::alloc_n_copy(const T *b, const T *e) {
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};

}
template <typename T>
void Vec<T>::free() {
    if (elements) {
        for_each(elements, first_free, 
                [](T &s){alloc.destroy(&s);});
        alloc.deallocate(elements, cap - elements);
    }
}
template <typename T>
Vec<T>::Vec(initializer_list<T> il) {
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
template <typename T>
Vec<T>::Vec(const Vec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
template <typename T>
Vec<T>::~Vec() {
    free();
}
template <typename T>
Vec<T>& Vec<T>::operator=(const Vec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
template <typename T>
Vec<T>::Vec(Vec &&rhs) noexcept : elements(rhs.elements),
                              first_free(rhs.first_free),
                              cap(rhs.cap) {
    rhs.elements = nullptr;
    rhs.first_free = nullptr;
    rhs.cap = nullptr;
}
template <typename T>
Vec<T> &Vec<T>::operator=(Vec &&rhs) noexcept {
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
template <typename T>
Vec<T>& Vec<T>::operator=(initializer_list<T> il) {
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
template <typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs){
    if (lhs.size() != rhs.size()) return false;
    for (auto iter1 = lhs.begin(), iter2 = rhs.begin(); 
        iter1 != lhs.end() && iter2 != rhs.end(); 
        iter1++, iter2++) {
            if (*iter1 != *iter2)
                return false;
        }
    return true;
}
template <typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs) {
    return !(lhs == rhs);
}
template <typename T>
bool operator< (const Vec<T>& lhs, const Vec<T>& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return true;
        else if (*p1 > *p2)
            return false;
    if (p1 == lhs.end() && p2 != rhs.end())
        return true;
    return false;
}
template <typename T>
bool operator<= (const Vec<T>& lhs, const Vec<T>& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return true;
        else if (*p1 > *p2)
            return false;
    if (p1 == lhs.end())
        return true;
    return false;
}
template <typename T>
bool operator> (const Vec<T>& lhs, const Vec<T>& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return false;
        else if (*p1 > *p2)
            return true;
    if (p1 != lhs.end() && p2 == rhs.end())
        return true;
    return false;
}
template <typename T>
bool operator>= (const Vec<T>& lhs, const Vec<T>& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return false;
        else if (*p1 > *p2)
            return true;
    if (p2 == rhs.end())
        return true;
    return false;
}
template <typename T>
void Vec<T>::reallocate(){
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
template <typename T>
void Vec<T>::reallocate(size_t newcapacity){
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
template <typename T>
inline void Vec<T>::resize(size_t n) {
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
template <typename T>
inline void Vec<T>::resize(size_t n, const T &s) {
    if (n > size()) {
        while(size() < n) {
            push_back(s);
        }
    }
}
/*16.19*/
template <typename T>
void func(T& container) {
    using size_type = typename T::size_type;
    for (size_type i = 0; i < container.size(); i++) 
        cout << container[i] << " ";
    cout << endl;
}
/*16.20*/
template <typename T>
void func1(T& container) {
    using size_type = typename T::size_type;
    for (auto i = container.begin(); i != container.end(); i++) 
        cout << *i << " ";
    cout << endl;
}
/*16.21*/
class DebugDelete{
public:
    DebugDelete(ostream &s = cerr): os(s) {}
    template<typename T> void operator()(T *p) {os<<"deleting object"<<endl;delete p;}
private:
    ostream &os;
};
/*16.22*/
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
    set<int>::iterator begin() {return line_no->begin();}
    set<int>::iterator end() {return line_no->end();}
    shared_ptr<vector<string>> get_file() {return text;}
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

TextQuery::TextQuery (ifstream &in):text(new vector<string>, DebugDelete()) {
    
    //this->text = make_shared<vector<string>>();
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

/*16.41*/
template<typename T1, typename T2>
auto sum(T1 a, T2 b) -> decltype(a + b) {
    return (a + b);
}
/*16.47*/
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
template<typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}
template<typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2) {
    f(t2, t1);
}
void f(int v1, int &v2) {
    cout << v1 << " " << ++v2 << endl;
}
void g(int &&i, int& j) {
    cout << i << " " << j << endl;
}
/*16.48*/
template<typename T> string debug_rep(const T &t) {
    ostringstream ret;
    ret << t;
    return ret.str();
}
template<typename T> string debug_rep(T* p) {
    ostringstream ret;
    ret << "pointer: " << p;
    if (p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}
string debug_rep(const string &s) {
     return '"'+s+'"';
}
string debug_rep(char *p) 
{
	return debug_rep(std::string(p));
}
string debug_rep(const char *p) 
{
	return debug_rep(std::string(p));
}
template<typename T, typename... Args>
void foo(const T &t, const Args& ... rest) {
    cout << sizeof...(Args) << endl;
    cout << sizeof...(rest) << endl;
}

/*16.53*/
template<typename T>
ostream &print(ostream& os, const T &t) {
    return os<<t<<endl;
}
template<typename T, typename... Args> 
ostream &print(ostream& os, const T &t, const Args&... rest) {
    os << t << ", ";
    return print(os, rest...);
}

/*16.56*/
template<typename... Args>
ostream &errMsg(ostream& os, const Args&... rest) {
    return print(os, debug_rep(rest)...);
}

/*16.58*/
class StrVec {
public:
    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(StrVec &&) noexcept;
    ~StrVec();
    StrVec &operator=(initializer_list<string>);
    void push_back(const string&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    string *begin() const {return elements;}
    string *end() const {return first_free;}
    void reserve(size_t n) {if (n > capacity()) reallocate(n);}
    inline void resize(size_t);
    inline void resize(size_t, const string &);
    string& operator[] (size_t i) { return elements[i];}
    const string& operator[] (size_t i) const {return elements[i];}
    template<class... Args> void emplace_back(Args&&...);
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
friend bool operator==(const StrVec&, const StrVec&);
friend bool operator< (const StrVec&, const StrVec&);
friend bool operator<= (const StrVec&, const StrVec&);
friend bool operator> (const StrVec&, const StrVec&);
friend bool operator>= (const StrVec&, const StrVec&);
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
StrVec& StrVec::operator=(initializer_list<string> il) {
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
bool operator==(const StrVec& lhs, const StrVec& rhs){
    if (lhs.size() != rhs.size()) return false;
    for (auto iter1 = lhs.begin(), iter2 = rhs.begin(); 
        iter1 != lhs.end() && iter2 != rhs.end(); 
        iter1++, iter2++) {
            if (*iter1 != *iter2)
                return false;
        }
    return true;
}
bool operator!=(const StrVec& lhs, const StrVec& rhs) {
    return !(lhs == rhs);
}
bool operator< (const StrVec& lhs, const StrVec& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return true;
        else if (*p1 > *p2)
            return false;
    if (p1 == lhs.end() && p2 != rhs.end())
        return true;
    return false;
}
bool operator<= (const StrVec& lhs, const StrVec& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return true;
        else if (*p1 > *p2)
            return false;
    if (p1 == lhs.end())
        return true;
    return false;
}
bool operator> (const StrVec& lhs, const StrVec& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return false;
        else if (*p1 > *p2)
            return true;
    if (p1 != lhs.end() && p2 == rhs.end())
        return true;
    return false;
}
bool operator>= (const StrVec& lhs, const StrVec& rhs) {
    auto p1 = lhs.begin(), p2 = rhs.begin();
    for (; p1 != lhs.end() && p2 != rhs.end(); p1++, p2++) 
        if (*p1 < *p2)
            return false;
        else if (*p1 > *p2)
            return true;
    if (p2 == rhs.end())
        return true;
    return false;
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
template<class... Args> inline void StrVec::emplace_back(Args&&... args) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

int main() {

    /*16.4*/
    vector<int> ivec = {1,4,2,4,6};
    list<string> slist = {"ab", "abc", "def", "g"};
    cout << (find(ivec.begin(), ivec.end(), 6) - ivec.begin()) << endl;
    cout << *(find(slist.begin(), slist.end(), "def")) << endl;
    /*16.5*/
    int iarr[5] = {2,4,56,74,3};
    char carr[5] = "abcd";
    print(iarr);
    print(carr);
    /*16.7*/
    cout << size(iarr) << endl;

    /*16.14*/
    Screen<5,3> myscreen;
    myscreen.display(cout);cout<<endl;
    myscreen.move(4,0).set('#');
    myscreen.display(cout);cout<<endl;
    myscreen.clear('Z').display(cout);cout<<endl;

    /*16.15*/
    cout <<"enter myscreen:" << endl;
    if (cin>>myscreen)
        cout<<myscreen;cout<<endl;
    cin.clear();

    /*16.19*/
    vector<int> ivec19 = {5,12,6,34,1534,1};
    func(ivec19);
    /*16.20*/
    vector<string> svec20 = {"5","12","6","34","1534","1"};
    func1(svec20);

    /*16.23*/
    ifstream infile("..\\Chap12\\words");
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

    /*16.30*/
    Blob<string> b1;
    cout << b1.size() << endl;
    {
        Blob<string> b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        cout << b1.size() << " " << b2.size() << endl;
    }
    cout << b1.size() << endl;
    for (size_t i=0; i<b1.size(); ++i) cout << b1.at(i) << " ";
    cout << endl <<endl;
    UP<int> u1(new int(42));
    cout << *u1 <<endl;
    UP<int> u2(u1.release());
    cout << *u2 <<endl;

    /*16.39*/
    auto i39 = compare<string>("hello", "world!");

    /*16.47*/
    int i=0, j=0, k=0, l=0;
    cout << i << j << k << l << endl;
    f(42, i);
    cout << i << j << k << l << endl;
    flip1(f, j, 42);
    cout << i << j << k << l << endl;
    flip2(f, k, 42);
    cout << i << j << k << l << endl;
    g(42, i);
    cout << i << j << k << l << endl;
    //flip2(g, i, 42);
    flip(g,i,42);
    cout << i << j << k << l << endl;

    /*16.48*/
	string s("hi");
	cout << debug_rep(s) << endl; 
	cout << debug_rep(&s) << endl;
    const string *sp = &s;
    cout << debug_rep(sp) << endl; 
    cout << debug_rep("hi world!") << endl;
    
    /*16.51*/
    int i51 = 0; double d51 = 3.14; string s51 = "how now brown cow";
    foo(i51, s51, 42, d51);
    foo(s51, 42, "hi");
    foo(d51, s51);
    foo("hi");
    
    /*16.53*/
    print(cout, "hi");
    print(cout, "hi", 42);
    print(cout, "hi", 42, 3.14, 'd', string("hi"));

    /*16.56*/
    errMsg(cerr, "hi", 42, 3.14, 'd', string("hi"));
    return 0;
}