#include <chrono>
#include <iostream>


int main(){
    double sum=0;
    std::chrono::high_resolution_clock::time_point t0=std::chrono::high_resolution_clock::now();
    for (int i=0; i<10000000; i++){
        sum += 0.1;
    }
    std::chrono::high_resolution_clock::time_point t1=std::chrono::high_resolution_clock::now();
    std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " milliseconds to complete the loop" << std::endl;
    std::cout << "Final result " << sum << std::endl;
}
