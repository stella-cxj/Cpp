#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {

    /*3.27*/
    unsigned buf_size = 1024;
    int ia[buf_size];//不合法，buf_size不是const表达式。这里编译器不报错是gcc对可变长数组的扩展

    /*3.31*/
    int arr[10];
    for (auto i = 0; i < 10; i++) {
        arr[i] = i;
        cout << arr[i] << "\t";
    }
    cout << endl;
    
    /*3.32*/
    int arr32[10];
    for (auto i = 0; i < 10; i++) {
        arr32[i] = arr[i];
        cout << arr32[i] << "\t";
    }
    cout << endl;

    vector<int> vec1, vec2;
    for (auto i = 0; i < 10; i++) {
        vec1.push_back(i);
    }
    vec2 = vec1;
    for (auto i : vec2) {
        cout << i << "\t";
    }
    cout << endl;

    /*3.35*/
    int arr35[3] = {1,2,3};
    for (int *p = begin(arr35); p < end(arr35); p++) {
        *p = 0;
    }
    for (auto index : arr35) {
        cout << index << "\t";
    }
    cout << endl;

    /*3.36*/
    int arr1[5] = {1,2,3,4,5};
    int arr2[5] = {1,2,3,4,5};
    int *b1 = begin(arr1), *e1 = end(arr1);
    int *b2 = begin(arr2), *e2 = end(arr2);
    int i;
    if ((e1 - b1) == (e2 - b2)) {
        for (i = 0; i < (e1 - b1); i++) {
            if (arr1[i] != arr2[i])
                break;
        }
    }
    if (i == (e1 - b1))
        cout << "arr1 == arr2" << endl;
    else
        cout << "arr1 != arr2" << endl;

    vector<int> ivec1 = {1,2,3,4,5};
    vector<int> ivec2 = {1,2,3,4,5,6};
    if (ivec1 == ivec2)
        cout << "ivec1 == ivec2" << endl;
    else
        cout << "ivec1 != ivec2" << endl;

    /*3.39*/
    string str1 = "hello";
    string str2 = "hello1";
    if (str1 < str2)
        cout << "str1 < str2" << endl;
    else if (str1 > str2)
        cout << "str1 > str2" << endl;
    else
        cout << "str1 == str2" << endl;

    char sarr1[] = "hello";
    char sarr2[] = "hello";
    if (strcmp(sarr1, sarr2) > 0)
        cout << "sarr1 > sarr2" << endl;
    else if (strcmp(sarr1, sarr2) < 0)
        cout << "sarr1 < sarr2" << endl;
    else
        cout << "sarr1 == sarr2" << endl;

    /*3.40*/
    char string1[] = "Hello";
    char string2[] = "world";
    const int len = strlen(string1) + strlen(string2);
    char string3[len] = "";
    strcat(string1, string2);
    strcpy(string3, string1);
    for (auto i : string3) {
        cout << i;
    }
    cout << endl;

    /*3.41*/
    int intarr[5] = {3,4,5,6,7};
    vector<int> intvec(begin(intarr), end(intarr));
    for (auto index : intvec) {
        cout << index << "\t";
    }
    cout << endl;

    /*3.42*/
    vector<int> vecint{7,6,5,4,3};
    int arrint[5];
    for (auto i = 0; i < vecint.size(); i++) {
        arrint[i] = vecint[i];
    }
    for (auto index : arrint) {
        cout << index << "\t";
    }
    cout << endl;

    /*3.43*/
    int iaa[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
    for (int (&i)[4] : iaa)
        for (int j : i)
            cout << j << "\t";
    cout << endl;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            cout << iaa[i][j] << "\t";
    cout << endl;

    for (int (*pi)[4] = begin(iaa); pi != end(iaa); pi++)
        for (int *pj = begin(*pi); pj != end(*pi); pj++)
            cout << *pj << "\t"; 
    cout << endl;
    
    using int_array = int[4];
    for (int_array &i : iaa)
        for (int j : i)
            cout << j << "\t";
    cout << endl;
    for (int_array *pi = begin(iaa); pi != end(iaa); pi++)
        for (int *pj = begin(*pi); pj != end(*pi); pj++)
            cout << *pj << "\t"; 
    cout << endl;

    for (auto &i : iaa)
        for (auto j : i)
            cout << j << "\t";
    cout << endl;
    for (auto i = 0; i < 3; i++)
        for (auto j = 0; j < 4; j++)
            cout << iaa[i][j] << "\t";
    cout << endl;
    for (auto pi = begin(iaa); pi != end(iaa); pi++)
        for (auto pj = begin(*pi); pj != end(*pi); pj++)
            cout << *pj << "\t"; 
    cout << endl;

    return 0;

}