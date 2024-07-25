#include <iostream>
#include <vector>
using namespace std;

class Person {
friend    istream &read(istream &is, Person &per);
friend    ostream &print(ostream &os, const Person &per);

public:
    Person() = default;
    Person(const string &person_name, const string &address) : name(person_name), addr(address) {}
    explicit Person(istream &is) {
        read(is, *this);
    }
    string get_name() const {return name;}
    string get_addr() const {return addr;}
private:
    string name;
    string addr;
};

istream &read(istream &is, Person &per) {
    is >> per.name >> per.addr;
    return is;
}
ostream &print(ostream &os, const Person &per) {
    os << "name is " << per.name << ", addr is " << per.addr << endl;
    return os;
}


class Screen;
class Win_mgr {
public:
    Win_mgr();
    using ScreenIndex = vector<Screen>::size_type;
    void clear(ScreenIndex);
    void print();
private:
    vector<Screen> screens;
};

class Screen {
friend void Win_mgr::clear(vector<Screen>::size_type);
public:
    typedef string::size_type pos;
    Screen() = default;
    Screen(unsigned wid, unsigned hit) : width(wid), height(hit), content(wid*hit, ' ') {}
    Screen(unsigned wid, unsigned hit, char c) : width(wid), height(hit), content(wid*hit, c) {}
    Screen &move(int r, int c) {
        cursor = r*width + c;
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
    pos size() const;
private:
    string content;
    unsigned width = 0, height = 0, cursor = 0;
};

Screen::pos Screen::size() const {
    return height * width;
}

void Win_mgr::clear(ScreenIndex i) {    
    Screen &s = screens[i];
    s.content = string(s.height*s.width, ' ');
}

Win_mgr::Win_mgr() {
    screens = {Screen(2, 3, 'X')};
}
void Win_mgr::print() {
    for (auto i:screens)
        i.display(cout);
}

int main() {
    /*7.27*/
    Screen myScreen(5,5,'X');
    myScreen.move(4,0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << "\n";
    /*7.32*/
    Win_mgr win;
    win.print();cout << "\n";
    win.clear(0);
    win.print();cout << "\n";

    return 0;
}

/*7.31*/
class Y;
class X {
    Y* y;
};
class Y {
    X x;
};

/*7.36*/
struct Z {
    Z (int i, int j) : base(i), rem(base % j) {}
    int base, rem;
};

/*7.43*/
class NoDefault{
public:
    NoDefault(int x) {}
};

class C {
public:
    C() : nodefault(0) {}
    NoDefault nodefault;
};