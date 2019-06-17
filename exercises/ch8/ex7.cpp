#include <iostream>

void swap_ints_point(int* i1, int* i2){
    int temp=*i1;
    *i1=*i2;
    *i2=temp;
}

void swap_ints_ref(int& i1, int& i2){
    int temp=i1;
    i1=i2;
    i2=temp;
}

int main(){
    int a=1, b=42;
    swap_ints_point(&a, &b);
    std::cout << "a=" << a << " b=" << b << std::endl;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
    swap_ints_ref(a, b);
    std::cout << "a=" << a << " b=" << b << std::endl;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
}
