#include <iostream>


int main(){
    char a[5]="abcd";
    char* p1=&a[0];
    char* p2=&a[2];
    std::cout << p2-p1 << std::endl;
}
