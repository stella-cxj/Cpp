#include <iostream>
#include <cctype>
using namespace std;
int main() {
    /*3.2*/
    string word;
    cout << "Input by words" << endl;
    while (cin >> word) {
        cout << word << endl;
    }
    cin.clear();
    string line;
    cout << "Input by lines" << endl;
    while (getline(cin, line)) {
        cout << line << endl;
    }
    cin.clear();

    /*3.4*/
    string str1, str2;
    cout << "Input 2 strings." << endl;
    cin >> str1 >> str2;
    if (str1 == str2)
        cout << "Same." << endl;
    else if (str1 > str2)
        cout << str1 << " is bigger" << endl;
    else
        cout << str2 << " is bigger" << endl;

    if (str1.size() == str2.size())
        cout << "Length same." << endl;
    else if (str1.size() > str2.size())
        cout << str1 << " is longer" << endl;
    else
        cout << str2 << " is longer" << endl;
    cin.clear();

    /*3.5*/
    string str, sum1, sum2;
    cout << "Input multiple strings." << endl;
    while (cin >> str){
        sum1 += str;
        sum2 += str; sum2 += ';';
    }
    cout << "sum1 = " << sum1 << endl;
    if (sum2.size() > 0) {
        sum2.erase(sum2.size()-1, 1);
        cout << "sum2 = " << sum2 << endl;
    }
    cin.clear();
    /*3.6*/
    string str6;
    cout << "Input a string" << endl;
    cin >> str6;
    for (auto &c : str6)
        c = 'X';
    cout << "Replaced with X: " << str6 << endl;
    cin.clear();
    /*3.10*/
    string str10;
    cout << "please enter a string with punctuation:" << endl;
    cin >> str10;
    for (auto c : str10) {
        if (!ispunct(c))
            cout << c;
    }    
    cout << endl;

    return 0;
}


