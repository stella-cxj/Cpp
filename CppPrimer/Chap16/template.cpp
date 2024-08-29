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
template<unsigned H, unsigned W>
class Screen {
//friend void Win_mgr::clear(vector<Screen>::size_type);
public:
    Screen() :content(W * H, ' ') {}
    Screen(char c) :content(W * H, c) {}
    char get() const {return content[cursor];}
    inline char get(int, int) const ;
    Screen &clear(char = bkground);
private:
    static const char bkground = ' ';
    Screen &move(int r, int c) {
        cursor = r*W + c;
        return *this;
    }
    Screen &set(char c) {
        content[cursor] = c;
        return *this;
    }
    const Screen &display(ostream &os) const {
        os << content;
        return *this;
    }
    //pos size() const;
private:
    string content;
    unsigned cursor = 0;
};

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

    return 0;
}