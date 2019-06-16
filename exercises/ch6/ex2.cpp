#include <chrono>
#include <string>
#include <thread>
#include <iostream>

void greet(std::string s){
    for (int i=0; i<10; i++){
        std::cout << s << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(){
    std::thread t1(greet, "Hello");
    std::thread t2(greet, "world!");
    t1.join();
    t2.join();
}
