#include <iostream>


int main(){
    int a[5]={0, 1, 2, 3, 4};
    int* p1=&a[2];
    int* p2=&a[2];
    std::cout << p2-p1 << std::endl;
}
