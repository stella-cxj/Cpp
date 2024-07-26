#include <iostream>
using namespace std;

/*8.1*/
istream &testio(istream &is) {
    int data;
    while(is >> data, !is.eof()) {
        if (is.bad())
            throw runtime_error("IO stream error");
        if (is.fail()) {
            cerr << "Data error, please retry." << endl;
            is.clear();
            is.ignore(100, '\n');
            continue;
        }
        cout << data << endl;
    }
    is.clear();
    return is;
}

int main() {

    testio(cin);
}