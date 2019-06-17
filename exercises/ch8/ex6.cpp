#include <iostream>

int main(){
    int a[10];
    int * foo = new int[10];
    for (int i=0; i<10; i++){
        a[i]=0;
    }
    std::cout << "Accessing element 11 (out of bounds) " << a[11] << std::endl;
    std::cout << "Accessing element 110 (out of bounds) " << a[2000] << std::endl;
    a[11] = 0;
    a[110] = 0;
    for (int i=0; i<10; i++){
        foo[i]=0;
    }
    std::cout << "Accessing element 11 (out of bounds) " << foo[11] << std::endl;
    std::cout << "Accessing element 110 (out of bounds) " << foo[2000] << std::endl;
    foo[11] = 0;
    foo[110] = 0;
    delete[] foo;
}
