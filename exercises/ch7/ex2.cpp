#include <limits>
#include <iostream>
#include <type_traits>


int main(){
    bool ans = std::is_same<char, signed char>::value;
    ans = std::numeric_limits<char>::is_signed;
    ans = (char)-1 < 0;
    if (ans) std::cout << "Signed" << std::endl;
    else std::cout << "Unsigned" << std::endl;
}
