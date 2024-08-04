#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <forward_list>
#include <fstream>
#include <stack>

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
/*9.43*/
void fix_string(string &s, const string &oldVal, const string &newVal) {
    int count = 0;
    if (s.size() < oldVal.size())
        return;
    for (auto i = s.begin(); i != s.end(); i++) {
        count = 0;
        for (auto j : oldVal) {
            if (*(i+count) == j)
                ++count;
            else   
                break;
        }
        if (count == oldVal.size()) {
            i = s.erase(i, i+count);
            i = s.insert(i, newVal.begin(), newVal.end());
            i += (newVal.size() - 1);
        }
    }
    return;
}
/*9.44*/
void fix_string2(string &s, const string &oldVal, const string &newVal) {
    int count = 0;
    if (s.size() < oldVal.size())
        return;
    for (int i = 0; i < s.size(); ++i) {
        count = 0;
        for (auto j : oldVal) {
            if (s[i+count] == j)
                ++count;
            else   
                break;
        }
        if (count == oldVal.size()) {
            s.replace(i, oldVal.size(), newVal);
            i += (newVal.size() - 1);
        }
         
    }
    return;
} 
/*9.45*/
string &add_string(string &s, const string &pre, const string &post) {
    auto index = s.begin();
    index = s.insert(index, pre.begin(), pre.end());
    s.append(post);
    return s;
}

/*9.46*/
string &add_string2(string &s, const string &pre, const string &post) {
    
    s.insert(0, pre);
    s.insert(s.size(), post);
    return s;
}
/*9.47*/
void find_char(const string &s, const string &target) {
    string::size_type pos = 0;
    while(((pos = s.find_first_of(target, pos)) != string::npos) ) {
        cout << s[pos] << " : " << pos << "\t";
        ++pos;
    }
    cout << endl;
}
void find_n_char(const string &s, const string &target) {
    string::size_type pos = 0;
    while(((pos = s.find_first_not_of(target, pos)) != string::npos) ) {
        cout << s[pos] << " : " << pos << "\t";
        ++pos;
    }
    cout << endl;
}
/*9.51*/

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;

public:
    Date(const string &s) {
        vector<string> Smonth = {"January", "Faburary", "March", "April", "May", 
                                 "June", "July", "August", "September", 
                                 "October", "November", "December", 
                                 "Jan", "Feb", "Mar", "Apr", 
                                 "May", "Jun", "Jul", "Aug", 
                                 "Sep", "Oct", "Nov", "Dec"};
        string numbers = "0123456789";     
        string sday, smonth, syear;   
        string::size_type pos = 0;
        for (auto i = Smonth.begin(); i != Smonth.end(); ++i) {
            if (s.find(*i) != string::npos) {
                month = ((i - Smonth.begin()) % 12) + 1;
                /*截取Day string*/
                if ( (pos = s.find_first_of(numbers)) != string::npos ) {
                    sday = s[pos++];
                    if ( numbers.find(s[pos]) != string::npos ) {
                        sday.append(1, s[pos++]);
                    }
                    day = stoi(sday);
                    /*截取Year string*/
                    pos = s.find_first_of(numbers, pos);
                    string syear = s.substr(pos, 4);
                    year = stoi(syear);
                    cout << "year " << year << " month " << month << " day " << day << endl;
                    return;
                }
                else {
                    cout << "Input error. " << endl;
                    return;
                }
            }
        }
         if ((pos = s.find("/")) != string::npos) {
            sday = s.substr(0, pos);
            day = stoi(sday);
            pos++;
            string::size_type pos_day = pos;
            if ( (pos = s.find("/", pos)) != string::npos ){
                smonth = s.substr(pos_day, pos - pos_day);
                month = stoi(smonth);
                pos++;
                syear = s.substr(pos, 4);
                year = stoi(syear);
                cout << "year " << year << " month " << month << " day " << day << endl;
                return;
            } else {
                cout << "Input error. " << endl;
                return;
            }
        }
        cout << "Failed to match." << endl;
        return;
    }
};
/*9.52*/

void calc(stack<char> &stk, char c) {
    string sa(1,c), sb;
    int a = stoi(sa);
    char cal = stk.top();
    stk.pop();
    sb = stk.top();
    int b = stoi(sb);
    stk.pop();
    if (cal == '+') {
        stk.push((char)((a+b)+48));
    } else if (cal == '-') {
        stk.push((char)((b-a)+48));

    } else {}

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

    /*9.41*/
    vector<char> cvec = {'a', 'b', 'c', 'd'};
    string sss(cvec.data(), cvec.size());
    
    /*9.43*/
    string str = "bbaaabbaabaaaaabb", str1 = "bb", str2 = "ccd";
    fix_string(str, str1, str2);
    cout << str << endl;
    /*9.44*/
    str = "bbaaabbaabaaaaabb";
    fix_string2(str, str1, str2);
    cout << str << endl;

    /*9.45*/
    string s3 = "Stella", s_pre = "Ms", s_post = "III";
    s3 = add_string(s3, s_pre, s_post);
    cout << s3 << endl;

    /*9.46*/
    s3 = "Stella";
    s3 = add_string2(s3, s_pre, s_post);
    cout << s3 << endl;

    /*9.47*/
    string s4 = "ab2c3d7R4E6";
    string numbers = "01234567890";
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    find_char(s4, numbers);
    find_char(s4, characters);
    find_n_char(s4, characters);
    find_n_char(s4, numbers);

    /*9.49*/
    fstream is("words");
    string word, longest;
    if (is) {
        while(is >> word) {
            if ((word.find_first_of("bdfghijklpqty") == string::npos) && (word.size() > longest.size())) {
                longest = word;
            }
        }
        cout << longest << endl;
    }
    is.close();

    /*9.50*/
    vector<string> vecs = {"+6", "2.2", "33", "-55"};
    //int sum = 0;
    double sum = 0;
    for (auto i : vecs) {
        //sum += stoi(i);
        sum += stod(i);
    }
    cout << sum << endl;

    /*9.51*/
    Date test1("January 21, 1900");
    Date test2("Sep 30 1900");
    Date test3("31/12/1990");

    /*9.52*/
    stack<char> stk;
    string exp = "(2+(1+2)-1+(3-2)+1)";
    for (auto i = 0; i < exp.size(); i++) {
        if (exp[i] == '(') {
            stk.push(exp[i]);
        } else if ((exp[i] == '+') || (exp[i] == '-')) {
            stk.push(exp[i]);
        } else if (exp[i] == ')') {
            char v = stk.top();
            stk.pop();
            stk.pop();
            if ((!stk.empty()) && (stk.top() != '(')) {
                calc(stk, v);
            } else {
                stk.push(v);
            }
        } else {
            if (stk.empty() || stk.top() == '(')
                stk.push(exp[i]);
            else 
                calc(stk, exp[i]);
        }
    }
    cout << stk.top() << endl;

}
 