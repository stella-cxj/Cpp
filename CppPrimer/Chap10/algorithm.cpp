#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <numeric>

using namespace std;

int main() {
    
    /*10.1*/
    vector<int> ivec;
    int i;
    cout << "Please enter some integers:" << endl;
    while(cin >> i) {
        ivec.push_back(i);
    }
    int counter = count(ivec.cbegin(), ivec.cend(), 5);
    cout << "There are " << counter << " 5 in your input." << endl;
    cin.clear();

    /*10.2*/
    list<string> slist;
    string s;
    cout << "Please enter some strings:" << endl;
    while(cin >> s) {
        slist.push_back(s);
    }
    counter = count(slist.cbegin(), slist.cend(), "5");
    cout << "There are " << counter << " 5 in your input." << endl;
    cin.clear();

    /*10.3*/
    vector<int> ivec2 = {1,2,3,4,5};
    int sum = accumulate(ivec2.cbegin(), ivec2.cend(), 0);
    cout << "sum is " << sum << endl;

    /*10.6*/
    list<int> ilist(10,6);
    fill_n(ilist.begin(), ilist.size(), 0);
    for (auto i : ilist) {
        cout << i << "\t";
    }
    cout << endl;

    /**/

    return 0;
}   