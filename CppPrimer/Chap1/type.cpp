#include <iostream>
#include <typeinfo>

int main(){
    #if 0
    int i = 0, &r = i;
    auto a = r;
    const int ci = i, &cr = ci;
    auto b = ci;
    auto c = cr; 
    auto d = &i;
    auto e = &ci;
    const auto f = ci;
    auto &g = ci;
    //auto &h = 42;
    const auto &j = 42;

    /*2.33*/
    a = 42; b = 42; c = 42; //abc均为int，给int赋值
    d = 42; //非法，int给int *赋值
    e = 42; //非法，int给const int *赋值
    g = 42;//非法，int给const int赋值
    #endif

    /*2.35*/
    const int i = 42;
    auto j = i; //j为int
    const auto &k = i; //k为常量引用
    auto *p = &i; //p为const int *
    const auto j2 = i, &k2 = i; //j2为const int, k2为const int引用

    std::cout << typeid(i).name() << std::endl;
    std::cout << typeid(j).name() << std::endl;
    std::cout << typeid(k).name() << std::endl;
    std::cout << typeid(p).name() << std::endl;
    std::cout << typeid(j2).name() << std::endl;
    std::cout << typeid(k2).name() << std::endl;


}