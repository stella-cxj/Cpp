#include <iostream>
#include "Sales_item.h"
int main()
{
    /*1.20*/
    Sales_item book;
    std::cout << "Please enter a Sales item content, end with Ctrl+Z" << std::endl;
    while(std::cin >> book) {
        std::cout << "Your book is: " << book << "\nPlease enter next book:" << std::endl;
    }
    std::cin.clear();

    /*1.21*/
    Sales_item item1, item2;
    std::cout << "Please enter 2 Sales items content:" << std::endl;
    std::cin >> item1 >> item2;
    if (compareIsbn(item1, item2)) {
        std::cout << "Sum is " << item1 + item2 << std::endl;
    }
    else {
        std::cout << "Isbn is not same." << std::endl;
    }
    std::cin.clear();

    /*1.22*/
    Sales_item item, total;
    std::cout << "Please enter Sales items content:" << std::endl;
    if (std::cin >> total) {
        while (std::cin >> item) {
            if (compareIsbn(item, total)) {
                total += item;
            }
            else {
                std::cout << "Isbn is not same." << std::endl;
            }
        }
        std::cout << "Sum is " << total << std::endl;
    }
    else {
        std::cout << "No data." << std::endl;
    }
    std::cin.clear();

    /*1.23*/
    Sales_item book_last, book_new;
    int count = 1;
    std::cout << "Please enter Sales items content:" << std::endl;
    if (std::cin >> book_last) {
        while (std::cin >> book_new) {
            if (book_last.isbn() == book_new.isbn()) {
                count++;
            }
            else {
                std::cout << "Number of " << book_last.isbn() << " is " << count << std::endl;
                count = 1;
                book_last = book_new;
            }
        }
        std::cout << "Number of " << book_last.isbn() << " is " << count << std::endl;
    }
    else {
        std::cout << "No data." << std::endl;
    }
    std::cin.clear();

    /*1.24*/
    /*prompt>class.exe < book_sales*/

    /*1.25*/
    Sales_item sum;
    if (std::cin >> sum) {
        Sales_item trans;
        while (std::cin >> trans) {
            if (sum.isbn() == trans.isbn()) {
                sum += trans;
            }
            else {
                std::cout << sum << std::endl;
                sum = trans;
            }
        }
        std::cout << sum << std::endl;
    }
    else {
        std::cerr << "No Data" << std::endl;
    }
    return 0;
}