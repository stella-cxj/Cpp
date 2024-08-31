#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>

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
/*16.12*/
template<typename T> class Blob{
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob(): data(make_shared<vector<T>>()) {}
    Blob(initializer_list<T> il): data(make_shared<vector<T>>(il)) {}
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const T &t) {data->push_back(t);}
    void push_back(T &&t) {data->push_back(std::move(t));}
    void pop_back();
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    T& operator[](size_type i);
    const T& operator[](size_type i) const;
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string &msg) const;
};
template<typename T>
void Blob<T>::check(size_type i, const string &msg) const {
    if (i >= data->size())
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
    return 0;
}