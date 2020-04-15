#include <string>
#include <iostream>
#include <crypt.h>

int main(){
    std::string pass = "1234";
    std::string salt = "efaifv./";
    char* enc = crypt(pass.c_str(), salt.c_str());
    if (!enc) {
        std::cout << "Something went wrong encrypting " << " " << pass << " " << salt << std::endl;
    }
    else{
        std::cout << pass << " " << salt << " encrypted to " << enc << std::endl;
    }
    salt = "=faifv.<";
    enc = crypt(pass.c_str(), salt.c_str());
    if (!enc) {
        std::cout << "Something went wrong encrypting " << " " << pass << " " << salt << std::endl;
    }
    else{
        std::cout << pass << " " << salt << " encrypted to " << enc << std::endl;
    }
}
