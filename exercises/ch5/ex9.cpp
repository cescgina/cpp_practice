#include <fstream>


int main(){
    std::ofstream file("numbers.txt", std::ofstream::out);
    for (int i=0; i < 200; i++){
        file << i << std::endl;
    }
}
