#include <iostream>
#include <string>
#include <vector>

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
        delete ps;
        ps = new string(*c.ps);
        i = c.i;
        cout << "copy operator" << endl;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    string *ps;
    int i;
};
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


    return 0;
}