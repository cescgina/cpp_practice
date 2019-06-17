#include <iostream>
#include <cstring>

int main(){
    char str[]="a short string";
    std::cout << sizeof(str) << std::endl;
    std::cout << strlen(str) << std::endl;
}
