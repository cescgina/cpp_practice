#include <iostream>
#include <cstring>
#include <string>

std::string* cat(const char* str1, const char* str2){
    int l1 = std::strlen(str1);
    int l2 = std::strlen(str2);
    std::string * result = new std::string();
    result->resize(l1+l2);
    result->insert(0, str1);
    result->insert(l1, str2);
    return result;
}

int main(){
    const char* st1 = "alejfai";
    const char* st2 = "ao3y9";
    std::string* st3 = cat(st1, st2);
    std::cout << st1 << " " << st2 << " " << *st3 << std::endl;
    delete st3;
}
