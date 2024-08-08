#include <iostream>
#include <string>
#include <map>

using namespace std;
/*11.4*/
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

int main() {

    /*11.3*/     /*11.4*/
    map<string, size_t> words;
    string word;
    cout << "Please input some words:" << endl;
    while(cin >> word) {
        trans(word);
        ++words[word];
    }
    for (auto i : words) {
        cout << i.first << " occurs " << i.second << " times."  << endl;
    }



    return 0;
}