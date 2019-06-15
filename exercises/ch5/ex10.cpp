#include <fstream>
#include <iostream>


int main(){
    std::ifstream file("numbers.txt", std::ofstream::in);
    int i;
    while (!file.eof()){
        file >> i;
        std::cout << i << std::endl;
    }
}
