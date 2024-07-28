#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


/*8.1*/
istream &testio(istream &is) {
    string data;
    while(is >> data, !is.eof()) {
        if (is.bad())
            throw runtime_error("IO stream error");
        if (is.fail()) {
            cerr << "Data error, please retry." << endl;
            is.clear();
            is.ignore(100, '\n');
            continue;
        }
        cout << data << endl;
    }
    is.clear();
    return is;
}
/*8.4*/
void readfile(string filename, vector<string> &output) {
    fstream is(filename);
    string content;
    while (is && !is.eof()) {
        getline(is, content);//8.4
        //is >> content;//8.5
        output.push_back(content);
    }
}

int main() {
    
    /*8.1*/
    cout << "Please input a string:" << endl;
    testio(cin);
    /*8.4*/
    vector<string> file_content;
    readfile("file", file_content);
    for (auto i : file_content)
        cout << i << endl;

    /*8.9*/
    istringstream in("hello world!\n");
    testio(in);

    /*8.10*/
    string word;
    for (auto i:file_content) {
        istringstream strm(i);
        while (strm >> word)
            cout << word << endl;
    }
}


 