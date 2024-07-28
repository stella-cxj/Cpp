#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    /*5.14*/
    vector<string> svec;
    string s;
    cout << "Please enter some strings: " << endl;
    while(cin >> s)
        svec.push_back(s);
    int count = 0, max_count = 0, counting = 0;
    string word;
    auto i = svec.begin();
    while(i != svec.end()) {
        if (*i == *(i+1)) {
            if (counting) {
                count++;
            }
            else {
                count = 1;
                counting = 1;
            }
        }
        else {
            if (counting) {
                count ++;
                if (count > max_count) {
                    max_count = count;
                    word = *i;
                    count = 0;
                }
                counting = 0;
            }
        }
        i++;
    }
    cout << "max_count = " << max_count << ", word = " << word << endl;
    cin.clear();

    /*5.17*/
    vector<int> vec1, vec2;
    int in, counter = 0;
    cout << "Please enter int vec1: " << endl;
    while (cin >> in) {
        vec1.push_back(in);
    }
    cin.clear();
    cout << "Please enter int vec2: " << endl;
    while (cin >> in) {
        vec2.push_back(in);
    }
    cin.clear();
    auto size = (vec1.size() > vec2.size()) ? vec2.size() : vec1.size();
    for (auto i = 0; i < size; i++) {
        if (vec1[i] == vec2[i]) {
            counter++;
        }
    }
    if (counter == size) 
        cout << "TRUE" << endl;
    else
        cout << "FALSE" << endl;

    /*5.19*/
    string s1, s2;
    do {
        cout << "Please enter 2 strings: " << endl;
        cin >> s1 >> s2;
        if (s1.size() > s2.size())
            cout << s2 << endl;
        else   
            cout << s1 << endl;
    } while (cin);
    cin.clear();

    /*5.20*/
    string str, last_str;
    cout << "Please enter some strings: " << endl;
    while(cin >> str) {
        if (str == last_str) {
            cout << "same words: " << str << endl;
            break;
        }
        else {
            last_str = str;
        }
    }
    if (!cin)
        cout << "no same words." << endl;
    cin.clear();

    /*5.21*/
    string str21, last_str21;
    cout << "Please enter some strings: " << endl;
    char c;
    while(cin >> str21) {
        c = *(str21.begin());
        if ((str21 != last_str21) || (!(c >= 'A' && c <= 'Z'))) {
            last_str21 = str21;
            continue;
        }
        else {
            cout << "same words: " << str21 << endl;
            break;
        }
    }
    if (!cin)
        cout << "no same words." << endl;
    cin.clear();

    /*5.23*/
    int a1, a2;
    cout << "Please enter 2 integers: " << endl;
    cin >> a1 >> a2;
    try {
        if (a2 != 0)
            cout << a1 << " / " << a2 << " = " << a1/a2 << endl;
        else
            throw runtime_error("dividing by zero!");
    } catch (runtime_error err) {
        cout << "Error: " << err.what() << endl;
        return 0;
    }


    return 0;
}