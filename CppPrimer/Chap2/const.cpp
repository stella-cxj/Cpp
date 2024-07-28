#include <iostream>

int main() {
    /*2.30*/
    int i=0;
    const int v2 = 0; //v2 顶层const
    int v1 = v2; //v1非常量
    int *p1 = &v1, &r1 = v1;//p1指向v1，r1为v1的引用
    const int *p2 = &v2, *const p3 = &i, &r2 = v2; //p2底层const，指向v2；p3顶层底层都是const，指向i；r2引用v2，底层const。
    /*2.31*/
    r1 = v2; //合法，const对象赋值给普通对象v1
 //   p1 = p2; //不合法，底层const资格不同，p1非const，指向v2则有修改v2的风险
    p2 = p1; //合法，p2虽为const，仍可指向非const对象
  //  p1 = p3; //不合法，底层const资格不同
    p2 = p3; //合法，底层const资格相同


    return 0;
}