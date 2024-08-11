#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

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

int main() {
    
    

    
    return 0;
}