#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char** argv){
    std::string name, surname;
    std::cout << "input your name" << std::endl;
    std::cin >> name;
    std::cout << "input your last name" << std::endl;
    std::cin >> surname;
    name.push_back(' ');
    name.append(surname);
    surname = name;
    std::cout << "your full name is " << name << std::endl;
    for (std::string::iterator it=name.begin(); it != name.end(); it++){
        if (*it == 'a' || *it == 'e' || *it == 'i' || *it == 'o' || *it == 'u') *it = 'z';
    }
    std::cout << "your modified full name is " << name << std::endl;
    std::reverse(surname.begin(), surname.end());
    std::cout << "your reversed full name is " << surname << std::endl;
}
