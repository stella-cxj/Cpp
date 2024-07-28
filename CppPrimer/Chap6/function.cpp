#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool has_upper(const string &s) {
    bool ret = false;
    for (auto i : s) {
        if (isupper(i)) {
            ret = true;
        }
    }
    return ret;
}

void to_lower(string &s)
{
    for (auto &i : s)
        i = tolower(i);
}

int compare(const int i, const int *j) {
    if (i > *j) 
        return i;
    else
        return *j;
}

void swap(int *&i, int *&j) {
    int *temp = i;
    i = j;
    j = temp;
}

int summary(initializer_list<int> list) {
    int ret = 0;
    for (auto i : list)
        ret += i;
    return ret;
}
//#define NDEBUG
void print(vector<int> ivec, int index) {
    #ifndef NDEBUG
    cout << "vector size is " << ivec.size() << ", index is " << index << endl;
    #endif
    if (index < ivec.size()) {
        cout << ivec[index] << "\t";
        print(ivec, index + 1);
    }
    return;
}


/*6.36*/
string (&func(void))[10];
/*6.37*/
using arrT = string [10];
arrT &func(void);

auto func(void) -> string (&)[10];

string str[10];
decltype(str) &func(void);

/*6.38*/
int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};
decltype(odd) &arrPtr(int i) {
    return (i%2) ? odd : even;
}

/*6.42*/
string make_plural(size_t ctr, const string &word, const string &ending = "s") {
    return (ctr > 1) ? word+ending : word;
}

/*6.54*/
int func(int, int);
using F = int (*)(int, int);
vector<F> fvec;

/*6.55*/
int sum(int a, int b) {
    return (a+b);
}
int sub(int a, int b){
    return (a-b);
}
int multi(int a, int b) {
    return (a*b);
}
int divid(int a, int b) {
    return (b!=0) ? (a/b) : 0 ;
}


int main(int argc, char *argv[]) {

    /*6.17*/
    string s;
    cout << "Please enter a string: " << endl;
    cin >> s;
    cout << "Has upper is " << has_upper(s) << endl;
    to_lower(s);
    cout << "To lower is " << s << endl;
    cin.clear();
    
    /*6.21*/
    int i,j;
    cout << "Please enter 2 integers: " << endl;
    cin >> i >> j;
    cout << compare(i, &j) << " is bigger" << endl;
    cin.clear();

    /*6.22*/
    int a=5,b=10;
    int *pi = &a, *pj = &b;
    int *&rpi = pi, *&rpj = pj;
    swap(rpi, rpj);
    cout << "pi point to " << *pi << ", pj point to " << *pj << endl;

    /*6.25*/
    if (argc >= 3) {
        strcat(argv[1], argv[2]);
        cout << argv[1] << endl;
    }

    /*6.27*/
    cout << "summary is " << summary({1,2,3,4,5}) << endl;

    /*6.33*/
    vector<int> ivec = {34,7,2,5,82,45,3,6};
    print(ivec, 0);    
    cout << endl;

    /*6.42*/
    cout << make_plural(1, "success", "es") << "\t" << make_plural(2, "success", "es ") << endl;
    cout << make_plural(1, "failure") << "\t" << make_plural(2, "failure") << endl;

    /*6.55*/
    fvec.push_back(sum);
    fvec.push_back(sub);
    fvec.push_back(multi);
    fvec.push_back(divid);

    /*6.56*/
    int num1 = 1, num2 = 2;
    for (auto i : fvec) {
        cout << i(num1, num2) << endl;
    }

}
