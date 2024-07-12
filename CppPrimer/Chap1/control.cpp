#include <iostream>

int main() {
    
    /*1.9*/
    int sum = 0, i = 50;
    while (i <= 100) {
        sum += i;
        i++;
    }
    std::cout << "Sum = " << sum << std::endl;
    
    /*1.10*/
    i = 10;
    while (i >= 0) {
        std::cout << i << "\t";
        i--;
    }
    std::cout << std::endl;

    /*1.11*/
    int begin = 0, end = 0;
    std::cout << "Please enter 2 integers:" << std::endl;
    std::cin >> begin >> end;
    if (begin > end) {
        i = begin;
        begin = end;
        end = i;
    }
    while (begin <= end) {
        std::cout << begin << "\t";
        begin++;
    }
    std::cout << std::endl;

    /*1.12*/
    sum = 0;
    for (i = 50; i <= 100; i++) {
        sum += i;
    }
    std::cout << "Sum = " << sum << std::endl;

    for (i = 10; i >= 0; i--) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::cout << "Please enter 2 integers:" << std::endl;
    std::cin >> begin >> end;
    if (begin > end) {
        i = begin;
        begin = end;
        end = i;
    }
    for (i = begin; i <= end; i++) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    /*1.16*/
    std::cout << "Please enter some integers:" << std::endl;
    sum = 0;
    while (std::cin >> i) {
        sum += i;
    }
    std::cout << "Sum = " << sum << std::endl;

    return 0;

}