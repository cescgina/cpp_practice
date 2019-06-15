#include <iostream>
#include <string>

class Person{
    public:
        int age;
        std::string name;
        Person(int age_in=0, std::string name_in=""){
            name = name_in;
            age = age_in;
        }
};

std::ostream & operator<<(std::ostream & os, const Person& person){
    os << "Hello person named " << person.name << " of age " << person.age << std::endl;
    return os;
}

std::istream & operator>>(std::istream& is, Person & person){
    is >> person.name >> person.age;
    return is;
}

int main(){
    Person person;
    std::cout << "Write the name and age of several persons:" << std::endl;
    while(!std::cin.eof()){
        std::cin >> person;
        std::cout << person;
    }
}
