#include <iostream>
#include <cstring>

int strlen_cust(const char* str){
    int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

void strcpy_cust(char * str1, const char* str2){
    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }
}

int strcmp_cust(const char* str1, const char* str2){
    while (*str1 != '\0') {
        if (*str1 < *str2) return -1;
        else if (*str1 > *str2) return 1;
        str1++;
        str2++;
    }
    return 0;
}
int main(){
    const char* a = "aert";
    char b[5];
    char c[5];
    const char d[] = "alefje";
    strcpy_cust(b, a);
    std::strcpy(c, a);
    std::cout << "Length of 'aert' " << strlen_cust(a) << " std::strlen says " << std::strlen(a) << std::endl;
    std::cout << a << " " << b << std::endl;
    std::cout << a << " " << c << std::endl;
    std::cout << std::strcmp(a, b) << std::endl;
    std::cout << strcmp_cust(a, b) << std::endl;
    std::cout << std::strcmp(a, d) << std::endl;
    std::cout << strcmp_cust(a, d) << std::endl;
}
