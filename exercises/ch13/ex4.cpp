#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv){
    if (argc == 1){
        return 1;
    }
    for (int i=1; i<argc; i++){
        std::ifstream file(*(argv+i));
        if (file.is_open()){
            std::string line;
            while( getline(file, line)){
                std::cout << line << std::endl;
            }
        }
    }
}
