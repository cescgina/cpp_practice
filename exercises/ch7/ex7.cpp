#include <iomanip>
#include <iostream>

int main(){
    for (int i=32; i<=127; i++){
        std::cout << std::dec << i << " " << (char)i << " " << std::hex << i << std::endl;
    }
}
