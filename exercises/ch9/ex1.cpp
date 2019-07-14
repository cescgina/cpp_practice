#include <iostream>
// compile with  g++ -g -Wall -Werror -Wpadded ex1.cpp -o ans to get warning
// of padding

int main(){
    //struct A {long double ld; double dou; long lo; int in; bool bo; char ch;};
    struct A {long double ld; long lo; double dou; int in; char ch; bool bo;};
    struct B {long double ld; bool bo; char ch; int in; long lo; double dou;};
    struct C {double a; int b;};
    std::cout << "Size of long double " << sizeof(long double) << std::endl;
    std::cout << "Size of double " << sizeof(double) << std::endl;
    std::cout << "Size of long " << sizeof(long) << std::endl;
    std::cout << "Size of int " << sizeof(int) << std::endl;
    std::cout << "Size of char " << sizeof(char) << std::endl;
    std::cout << "Size of bool " << sizeof(bool) << std::endl;
    std::cout << "Size of struct A " << sizeof(struct A) << std::endl;
    std::cout << "Size of struct B " << sizeof(struct B) << std::endl;
    std::cout << "Size of struct C " << sizeof(struct C) << std::endl;
}
