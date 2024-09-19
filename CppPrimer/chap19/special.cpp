
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;
/*19.3*/
class A {
public:
    A() = default;
    virtual ~A(){}
};
class B : virtual public A {
public:
    B() = default;
    virtual ~B(){}
};
class C : public B {
public:    
    C() = default;
    virtual ~C(){}
};
class D : public B, virtual public A {
public:    
    D() = default;
    virtual ~D(){}
};
/*19.6*/
class Query_base {
public:
    Query_base() {}
    virtual ~Query_base() {}
};
class BinaryQuery: public Query_base {
public:
    //BinaryQuery() {}
    //virtual ~BinaryQuery() {}    
};
class AndQuery: public BinaryQuery {};

/*19.9*/
class Base {};
class Derived : public Base {};
/*19.10*/
class AA {
public:
     AA() {}
     virtual ~AA() {}

};
class BB : public AA {};
class CC : public BB {};

/*19.11*/
class Screen{
public:
    typedef string::size_type pos;
    char get_cursor() const {return contents[cursor];}
    char get() const;
    char get(pos ht, pos wd) const;

    typedef char (Screen::*p1)() const;
    typedef char (Screen::*p2)(pos, pos) const;

private:
    string contents;
    pos cursor;
    pos height, width;
    pos Screen::* p = & Screen::cursor;
};

/*19.18*/
int count(vector<string> svec) {
    auto f = mem_fn(&string::empty);
    return count_if(svec.begin(), svec.end(), f);
}

/*19.21*/
class Token {
public:
    Token(): tok(INT), ival(0) {}
    Token(const Token& t) : tok(t.tok) {copyUnion(t);}
    Token(Token&&t);
    Token &operator=(Token&&);
    Token &operator=(const Token&);
    ~Token() {if (tok==STR) sval.~string();}
    Token &operator=(const string&);
    Token &operator=(char);
    Token &operator=(int);
    Token &operator=(double);
private:
    enum {INT, CHAR, DBL, STR} tok;
    union {
        char cval;
        int ival;
        double dval;
        string sval;
    };
    void copyUnion(const Token&);
};
Token &Token::operator=(int i)
{
    if (tok==STR) sval.~string();
    ival = i;
    tok = INT;
    return *this;
}
Token &Token::operator=(char c)
{
    if (tok==STR) sval.~string();
    cval = c;
    tok = CHAR;
    return *this;
}
Token &Token::operator=(double d)
{
    if (tok==STR) sval.~string();
    dval = d;
    tok = DBL;
    return *this;
}
Token &Token::operator=(const string &s) {
    if (tok==STR)
        sval = s;
    else
        new (&sval) string(s);
    tok = STR;
    return *this;    
}
void Token::copyUnion(const Token &t) {
    switch(t.tok) {
        case INT: ival = t.ival; break;
        case CHAR: cval = t.cval; break;
        case DBL: dval = t.dval; break;
        case STR: new(&sval) string(t.sval); break;
    }
}
Token &Token::operator=(const Token &t) {
    if (tok==STR && t.tok != STR) sval.~string();
    if (tok==STR && t.tok == STR)
        sval = t.sval;
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
}
Token::Token(Token &&t) : tok(t.tok){
    switch(tok) {
        case STR: new(&sval) string(std::move(t.sval));break;
        case INT: ival = t.ival; break;
        case CHAR: cval = t.cval; break;
        case DBL: dval = t.dval; break;
    }
    t.tok = INT;
    t.ival = 0;
}
Token &Token::operator=(Token &&t) {
    if (this!=&t) {
        if (tok == STR) sval.~string();
        tok = t.tok;
        switch(tok) {
            case STR: new(&sval) string(std::move(t.sval));break;
            case INT: ival = t.ival; break;
            case CHAR: cval = t.cval; break;
            case DBL: dval = t.dval; break;
        }
        t.tok = INT;
        t.ival = 0;
    }
    return *this;
}

int main() {
/*19.4*/
    A *pa = new A;
    try {
        C &c = dynamic_cast<C&>(*pa);
    }catch (std::bad_cast &bc){
        std::cout << "dynamic_cast failed" << std::endl;
    }
    
    /*19.6*/
    Query_base* qb = new AndQuery;
    if (dynamic_cast<AndQuery*>(qb) != NULL) {
        cout <<"success"<<endl;
    }else {
        cout << "fail"<<endl;
    }

    /*19.7*/
    Query_base* qb1 = new AndQuery;
    try {
        dynamic_cast<AndQuery&>(*qb1);
        cout<<"success"<<endl;
    }catch(bad_cast &bc) {
        cout<<"fail"<<endl;
    }
    
    /*19.8*/
    Query_base* qb2 = new AndQuery;
    Query_base* qb3 = new BinaryQuery;
    if (typeid(*qb2) == typeid(*qb3)) 
        cout<<"same"<<endl;
    else    
        cout<<"not same"<<endl;
    if (typeid(*qb2) == typeid(AndQuery)) 
        cout<<"same"<<endl;
    else    
        cout<<"not same"<<endl;

    /*19.9*/
    Base b, *pb;
    pb = NULL;
    Derived d;
    cout << typeid(int).name() << endl
        << typeid(unsigned).name() << endl
        << typeid(long).name() << endl
        << typeid(unsigned long).name() << endl
        << typeid(char).name() << endl
        << typeid(unsigned char).name() << endl
        << typeid(float).name() << endl
        << typeid(double).name() << endl
        << typeid(string).name() << endl
        << typeid(Base).name() << endl
        << typeid(b).name() << endl
        << typeid(pb).name() << endl
        << typeid(Derived).name() << endl
        << typeid(d).name() << endl
        << typeid(type_info).name() << endl;
    /*19.10*/
    AA *paa = new CC;
    cout << typeid(paa).name()<<endl;
    CC cobj;
    AA& ra = cobj;
    cout << typeid(ra).name()<<endl;
    BB *px = new BB;
    AA& raa = *px;
    cout<<typeid(raa).name();

    /*19.21*/


    return 0;


}