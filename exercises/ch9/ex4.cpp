#include <string>
#include <iostream>

struct Date{int day; int month; int year;};

std::ostream& operator<<(std::ostream & os, struct Date& date){
    os << "Date is " << date.day << "/" << date.month << "/" << date.year << std::endl;
    return os;
}

std::istream& operator>>(std::istream & is, struct Date& date ){
    std::string temp;
    std::getline(is, temp, '/');
    date.day = std::stoi(temp);
    std::getline(is, temp, '/');
    date.month = std::stoi(temp);
    std::getline(is, temp);
    date.year = std::stoi(temp);
    return is;
}

int main(){
    Date d = {12, 3, 1456};
    std::cout << d << std::endl;
    std::cout << "Your turn, input your birthday in the same format and I'll print it back to you" << std::endl;
    std::cin >> d;
    std::cout << d << std::endl;
}
