#include <iostream>
// generate readable assembly code with g++ -g -c -fverbose-asm -Wa,-adhln ex9.cpp > ex9.lst

void f(char c){
    std::cout << c << std::endl;
}

void g(char& c){
    std::cout << c << std::endl;
} 
void h(const char& c){
    std::cout << c  << std::endl;
}

int main(){
    char a = 'a';
    char& a_ref = a;
    f(a);
    g(a_ref);
    h(a_ref);
    std::cout << std::endl;
    
    // int b = 49;
    // int& b_ref = b;
    // f(b);
    // g(b_ref);
    // h(b_ref);
    // std::cout << std::endl;

    // int c = 3300;
    // int& c_ref = c;
    // f(c);
    // g(c_ref);
    // h(c_ref);
    // std::cout << std::endl;
    
    //char c = 'c';
    //f(c);
    //g(c);
    //h(c);
    //std::cout << std::endl;

    unsigned char uc = 'c';
    f(uc);
    // g(uc);
    h(uc);
    std::cout << std::endl;
    
    signed char sc = 'c';
    signed char& sc_ref = sc;
    f(sc);
    // g(sc_ref);
    h(sc_ref);
    std::cout << std::endl;
}
