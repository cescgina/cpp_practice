#include <iostream>


int main(){
    std::cout << "Size of int " << sizeof(int) << std::endl;
    std::cout << "Size of long " << sizeof(long) << std::endl;
    std::cout << "Size of double " << sizeof(double) << std::endl;
    std::cout << "Size of char " << sizeof(char) << std::endl;
    std::cout << "Size of signed char " << sizeof(signed char) << std::endl;
    std::cout << "Size of unsigned char " << sizeof(unsigned char) << std::endl;
    std::cout << "Size of std::string " << sizeof(std::string) << std::endl;
    std::cout << "Size of int pointer " << sizeof(int*) << std::endl;
    std::cout << "Size of long pointer " << sizeof(long*) << std::endl;
    std::cout << "Size of std::string pointer " << sizeof(std::string*) << std::endl;
    std::cout << "Size of std::string reference " << sizeof(std::string&) << std::endl;
}
