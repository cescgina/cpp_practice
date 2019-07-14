#include <string>
#include <iostream>

enum Seasons{winter, spring, summer, autumm};

std::ostream& operator<<(std::ostream & os, Seasons& season){
    os << "Season is ";
    switch(season){
        case winter:
            os << "winter" << std::endl;
            break;
        case spring:
            os << "spring" << std::endl;
            break;
        case summer:
            os << "summer" << std::endl;
            break;
        case autumm:
            os << "autumm" << std::endl;
            break;
    }
    return os;
}

std::istream& operator>>(std::istream & is, Seasons& season ){
    std::string temp;
    std::getline(is, temp);
    if (temp == "winter") season = winter;
    else if (temp == "spring") season = spring;
    else if (temp == "summer") season = summer;
    else if (temp == "autumm") season = autumm;
    return is;
}

Seasons& operator++(Seasons& season){
    if (season == autumm) season=winter;
    else season = static_cast<Seasons>(season+1);
    return season;
}

Seasons operator++(Seasons& season, int){
    Seasons temp=season;
    ++season;
    return temp;
}

Seasons& operator--(Seasons& season){
    if (season == winter) season=autumm;
    else season = static_cast<Seasons>(season-1);
    return season;
}

Seasons operator--(Seasons& season, int){
    Seasons temp=season;
    --season;
    return temp;
}
int main(){
    Seasons s;
    std::cout << "What season should we start with?" << std::endl;
    std::cin >> s;
    std::cout << "Let's go forward, " << s << std::endl;
    for (int i=0; i<7; i++){
        s++;
        std::cout << s << std::endl;
    }
    std::cout << "Now let's go back, " << s << std::endl;
    for (int i=0; i<7; i++){
        s--;
        std::cout << s << std::endl;
    }
}
