#include <limits>
#include <iostream>

int main(){
    std::cout << "Min value for bool " << std::numeric_limits<bool>::min() << std::endl;
    std::cout << "Max value for bool " << std::numeric_limits<bool>::max() << std::endl;

    std::cout << "Min value for char " << (int)std::numeric_limits<char>::min() << std::endl;
    std::cout << "Max value for char " << (int)std::numeric_limits<char>::max() << std::endl;

    std::cout << "Min value for short " << std::numeric_limits<short>::min() << std::endl;
    std::cout << "Max value for short " << std::numeric_limits<short>::max() << std::endl;

    std::cout << "Min value for int " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "Max value for int " << std::numeric_limits<int>::max() << std::endl;

    std::cout << "Min value for long " << std::numeric_limits<long>::min() << std::endl;
    std::cout << "Max value for long " << std::numeric_limits<long>::max() << std::endl;

    std::cout << "Min value for long long " << std::numeric_limits<long long>::min() << std::endl;
    std::cout << "Max value for long long " << std::numeric_limits<long long>::max() << std::endl;

    std::cout << "Min value for float " << std::numeric_limits<float>::min() << std::endl;
    std::cout << "Max value for float " << std::numeric_limits<float>::max() << std::endl;

    std::cout << "Min value for double " << std::numeric_limits<double>::min() << std::endl;
    std::cout << "Max value for double " << std::numeric_limits<double>::max() << std::endl;

    std::cout << "Min value for long double " << std::numeric_limits<long double>::min() << std::endl;
    std::cout << "Max value for long double " << std::numeric_limits<long double>::max() << std::endl;

    std::cout << "Min value for unsigned " << std::numeric_limits<unsigned>::min() << std::endl;
    std::cout << "Max value for unsigned " << std::numeric_limits<unsigned>::max() << std::endl;

    std::cout << "Min value for unsigned long " << std::numeric_limits<unsigned long>::min() << std::endl;
    std::cout << "Max value for unsigned long " << std::numeric_limits<unsigned long>::max() << std::endl;
}
