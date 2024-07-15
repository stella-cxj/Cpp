#include <vector>
#include <string>
#include <iostream>

using namespace std;
//using std::vector;

int main() {

    /*3.14*/
    vector<int> ivec;
    cout << "Please enter some integers:" << endl;
    int i;
    while (cin >> i) {
        ivec.push_back(i);
    }
    for (auto index : ivec)
        cout << index << endl;
    cin.clear();

    /*3.15*/
    vector<string> svec;
    cout << "Please enter some strings:" << endl;
    string str;
    while (cin >> str) {
        svec.push_back(str);
    }
    for (auto index : svec)
        cout << index << endl;
    cin.clear();
    
}