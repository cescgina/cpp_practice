#include <iostream>
#include <cstring>

void rev(char* str){
    int l = std::strlen(str);
    char b;
    for (int i=0; i<l/2; i++){
        b = *(str+l-i-1);
        *(str+l-i-1) = *(str+i);
        *(str+i) = b;
    }
}


int main(){
    char a[] = "alefjaio";
    std::cout << a;
    rev(a);
    std::cout << " reversed is " << a << std::endl;
    char b[] = "123456789";
    std::cout << b;
    rev(b);
    std::cout << " reversed is " << b << std::endl;
}
