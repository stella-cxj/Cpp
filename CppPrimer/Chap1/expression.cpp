#include <iostream>
#include <vector>

using namespace std;


int main() {

    /*4.7*/
    vector<int> ivec = {2,5,2,4,3,26,4};
    for (auto i : ivec) {
        cout << (((i % 2) != 0) ? i*=2 : i) << "\t";
    }
    cout << endl;

    /*4.8*/
    string finalgrade;
    int grade;
    cout << "Please enter the grade: " << endl;
    cin >> grade;
    finalgrade = (grade>60 && grade<75) ? "low pass" : 
                 (grade>90) ? "high pass" : 
                 (grade<60) ? "fail" : "pass";
    cout << finalgrade << endl;    

    if (grade<60) {
        finalgrade = "fail";
    } else if (grade>90){
        finalgrade = "high pass";
    } else if (grade>60 && grade<75) {
        finalgrade = "low pass";
    } else {
        finalgrade = "pass";
    }
    cout << finalgrade << endl;    
    cin.clear();

    /*4.23*/
    string s="word";
    string p1=s + (s[s.size()-1] == 's' ? "" : "s");
    cout << p1 << endl;



    return 0;
}
