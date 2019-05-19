#include <iostream>

void salute(int num){
    for(int i=0; i<num; i++){
        std::cout << "Hello" << std::endl;
    }
}

int produce(int a, int b){
    return a*b;
} 

void half(int n){
    if (n <= 0){
        return;
    }
    std::cout << n << std::endl;
    n /= 2;
    half(n);
}

int main(int argc, char** argv){
    //int number;
    //std::cout << "How many times?" << std::endl;
    //std::cin >> number;
    //salute(number);
    half(100);
}
