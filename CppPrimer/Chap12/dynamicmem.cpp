#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
/*12.2*/
class StrBlob {
public:
    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
    void push_back(const string &t) {data->push_back(t);}
    void pop_back() {data->pop_back();}
    string & front() {return data->front();}
    string & back() {return data->back();}
    string & front() const {return data->front();}
    string & back() const {return data->back();}
private:
    shared_ptr<vector<string>> data;
};
/*12.6*/
vector<int> * func6() {
    auto *p = new vector<int>;
    return p;
}
void func_in(vector<int> *ivec) {
    int i;
    cout << "Please enter some integers: " << endl;
    while(cin >> i) {
        ivec->push_back(i);
    }
    cin.clear();
}
void func_out(vector<int> *ivec) {
    for (auto i : *ivec) {
        cout << i << " ";
    }
    cout << endl;
    delete ivec;
}
/*12.7*/
shared_ptr<vector<int>> func7() {
    auto p = make_shared<vector<int>>();
    return p;
}
void func_in7(shared_ptr<vector<int>> p) {
    int i;
    cout << "Please enter some integers: " << endl;
    while(cin >> i) {
        p->push_back(i);
    }
    cin.clear();
}
void func_out7(shared_ptr<vector<int>> p) {
    for (auto i : *p) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    
    /*12.6*/
    vector<int> *ivec = func6();
    func_in(ivec);
    func_out(ivec);
    /*12.7*/
    auto p7 = func7();
    func_in7(p7);
    func_out7(p7);

    return 0;
}