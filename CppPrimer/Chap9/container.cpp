#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <forward_list>

using namespace std;
/*9.4*/
bool find(vector<int>::iterator begin, vector<int>::iterator end, int i) {
    auto index = begin;
    while(index != end) {
        if (*index == i)
            return true;
        index++;
    }
    return false;
}
/*9.5*/
auto find_iter(vector<int>::iterator begin, vector<int>::iterator end, int i) {
    auto index = begin;
    while(index != end) {
        if (*index == i)
            return index;
        index++;
    }
    return end;
}

/*9.16*/
bool compare(list<int> il, vector<int> iv) {
    bool ret = false;

    if (il.size() != iv.size())
        return false;
        
    auto it = iv.cbegin();
    auto i = il.cbegin();
    for (; i != il.cend(); i++) {
        if (*i != *it) 
            return false;
        else 
            it++;
    }
    return true;
}

/*9.28*/
void inserts(forward_list<string> &flist, const string &s1, const string &s2) {
    auto curr = flist.begin();
    auto prev = flist.before_begin();
    while(curr != flist.end()) {
        if (*curr == s1) {
            curr = flist.insert_after(curr, s2);
            return;
        } else {
            prev = curr;
            ++curr;
        }
    }
    curr = flist.insert_after(prev, s2);
    return;

}


int main() {
    /*9.4*/
    vector<int> ivec = {2,4,7,34,51,6,8,3};
    cout << find(++ivec.begin(), ivec.end(), 4) << endl;
    cout << find(++ivec.begin(), ivec.end(), 44) << endl;

    /*9.5*/
    vector<int>::iterator iter = find_iter(++ivec.begin(), ivec.end(), 4);
    if (iter != ivec.end())
        cout << *iter << endl;
    else
        cout << "not found" << endl;
    iter = find_iter(++ivec.begin(), ivec.end(), 44);
    if (iter != ivec.end())
        cout << *iter << endl;
    else
        cout << "not found" << endl;

    /*9.13*/
    list<int> ilist = {1,2,3};
    vector<double> dvec(ilist.begin(), ilist.end());
    vector<int> ivec2(ilist.begin(), ilist.end());

    /*9.14*/
    list<const char *>clist = {"aa","bb","cc"};
    vector<string> svec;
    svec.assign(clist.begin(), clist.end());

    /*9.15*/
    vector<int> vec{1,2,3,4,5,6,7};
    vector<int> vec1{1,2,3,4,5,6,7};
    cout << (vec==vec1) << endl;
    vec1.push_back(8);
    vec1.pop_back();
    cout << vec1.capacity() << " " << vec1.size() << endl;
    cout << (vec==vec1) << endl;

    /*9.16*/
    list<int>ilist2{1,2,3,4,5,6,7};
    cout << compare(ilist2, vec) << endl;

    /*9.18*/
    deque<string> sque;
    string s;
    cout << "please enter some strings:" << endl;
    while(cin >> s)
        sque.push_back(s);
    for (auto i : sque)
        cout << i << endl;
    cin.clear();

    /*9.19*/
    list<string> slist;
    string ss;
    cout << "please enter some strings:" << endl;
    while(cin >> ss)
        slist.push_back(ss);
    for (auto i : slist)
        cout << i << endl;
    cin.clear();

    /*9.20*/
    list<int> ilist3 = {1,2,3,4,5};
    deque<int> ique1, ique2;
    for (auto i : ilist3) {
        if (i % 2 == 0) {
            ique1.push_back(i);
        } else {
            ique2.push_back(i);
        }
    }
    cout << "deque1" << endl;
    for (auto i : ique1)
        cout << i << "\t";
    cout << endl;
    cout << "deque2" << endl;
    for (auto i : ique2)
        cout << i << "\t";
    cout << endl;
         
    /*9.24*/
    vector<int> ivec3 = {4};
    int a = ivec3.at(0);
    int b = ivec3[0];
    int c = ivec3.front();
    int d = *(ivec3.begin());
    cout << a << b << c << d << endl;

    /*9.26*/
    int ia[] = {0,1,1,2,3,5,8,13,21,55,89};
    vector<int> ivec4;
    list<int> ilist4;
    ivec4.assign(ia, ia+11);
    ilist4.assign(ia, ia+11);

    for (auto i = ilist4.begin(); i != ilist4.end(); ) {
        if ((*i % 2) != 0) 
            i = ilist4.erase(i);
        else
            ++i;
    }
    for (auto i : ilist4) 
        cout << i << "\t";
    cout << endl;

    for (auto i = ivec4.begin(); i != ivec4.end();) {
        if ((*i % 2) == 0) 
            i = ivec4.erase(i);
        else
            ++i;
    }
    for (auto i : ivec4) 
        cout << i << "\t";
    cout << endl;
        
    /*9.27*/
    forward_list<int> flist = {0,1,2,3,4,5};    
    for (auto curr = flist.begin(), prev = flist.before_begin(); curr != flist.end();) {
        if (*curr % 2) {
            curr = flist.erase_after(prev);
        } else {
            prev = curr;
            ++curr;
        }
    }
    for (auto i : flist)
        cout << i << "\t";
    cout << endl;

    /*9.28*/
    forward_list<string> flist1 = {"aa", "bb", "cc", "dd"};
    string s1 = "aa", s2 = "ab";
    inserts(flist1, s1, s2);
    for (auto i : flist1) {
        cout << i << "\t";
    }
    cout << endl;

}

