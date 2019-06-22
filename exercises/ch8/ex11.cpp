#include <set>
#include <string>
#include <iostream>


int main(){
    std::set<std::string> words;
    std::string value="";
    std::cout << "Insert your words" << std::endl;
    std::cin >> value;
    while (value != "Quit"){
        words.insert(value);
        std::cin >> value;
    }
    for (auto el: words){
        std::cout << el << std::endl;
    }
}
