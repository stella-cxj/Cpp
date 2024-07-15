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

    /*3.16*/
    vector<string> v6{10};
    cout << "v6 size is " << v6.size() << endl;
    if (v6.size() > 0)
    for (auto index : v6)
        cout << index << endl;

    /*3.17*/
    vector<string> words;
    string str17;
    cout << "Please enter some words: " << endl;
    while(cin >> str17) {
        for (auto &c : str17) {
            c = toupper(c);
        }
        words.push_back(str17);
    }
    for (string index : words) {
        cout << index << endl;
    }
    cin.clear();   

    /*3.20*/
    vector<int> vec20;
    cout << "Please enter some integers: " << endl;
    int input;
    while(cin >> input) {
        vec20.push_back(input);
    }
    for (int i = 0; i < vec20.size(); i++) {
        if ((i % 2) != 0) {
            cout << vec20[i - 1] + vec20[i] << endl;
        }
    }
    for (int i = 0; i < vec20.size()/2; i++) {
        cout << vec20[i] + vec20[vec20.size()-i-1] << endl;
    }
    cin.clear();

    /*3.21*/
    vector<string> v7{10,"hi"};
    for (auto iter = v7.cbegin(); iter != v7.cend(); iter++) {
        cout << *iter << endl;
    }

    /*3.22*/
    cout << "Please enter several lines of text: " << endl;
    string str22;
    vector<string> vec22;
    while(getline(cin, str22)){
        vec22.push_back(str22);
    }
    for (auto index = vec22.begin(); index != vec22.end(); index++) {
        if (index->empty()) {
            break;
        }
        for (auto ii = (*index).begin(); ii != (*index).end(); ii++) {
            *ii = toupper(*ii);
        }
        cout << *index << endl;
    }
    cin.clear();

    /*3.23*/
    vector<int> vec23{1,2,3,4,5,6,7,8,9,10};
    for (auto index = vec23.begin(); index != vec23.end(); index++) {
        *index = *index * 2;
        cout << *index << endl;
    }   

    /*3.24*/
    vector<int> vec24;
    cout << "Please enter some integers: " << endl;
    int input24;
    while(cin >> input24) {
        vec24.push_back(input24);
    }
    for (auto index = vec24.cbegin(); index != vec24.cend(); index++) {
        if (((index - vec24.cbegin()) % 2) != 0) {
            cout << (*index) + (*(index - 1)) << endl;
        }
    }
    for (auto index = vec24.cbegin(); index < vec24.cbegin() + (vec24.cend() - vec24.cbegin())/2; index++) {
        cout << (*index) + *(vec24.cend() - (index - vec24.cbegin() + 1)) << endl;
    }
    cin.clear();

    /*3.25*/
    vector<unsigned> scores(11,0);
    unsigned grade;
    auto it = scores.begin();
    cout << "Please enter grades: " << endl;
    while(cin >> grade) {
        if (grade <= 100)
            (*(it + (grade/10)))++;
    }
    for (auto index : scores) {
        cout << index << endl;
    }

    return 0;
}