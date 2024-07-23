#include <iostream>

using namespace std;

class Person {
friend    istream &read(istream &is, Person &per);
friend    ostream &print(ostream &os, const Person &per);

public:
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


int main() {


    return 0;
}