#include<string>
#include<vector>
#include<iterator>
#include<iostream>
#include<algorithm>


template<typename pref, typename match>
bool isPrefix(pref prefix, match matching){
    auto differingPositions = std::mismatch(std::begin(prefix), std::end(prefix), std::begin(matching), std::end(matching));
    return differingPositions.first == std::end(prefix);
}


void testIsPrefix(){
    std::string s1="AB", s2="HGGAE", s3="ABCD";
    std::vector<int> v1={1, 2}, v2={3, 4, 5, 6}, v3={1, 2, 3, 4, 5};
    std::cout << "Testing isPrefix" << std::endl;
    std::cout << "Should be false " << isPrefix(s1, s2) << std::endl;
    std::cout << "Should be true " << isPrefix(s1, s3) << std::endl;
    std::cout << "Should be false " << isPrefix(v1, v2) << std::endl;
    std::cout << "Should be true " << isPrefix(v1, v3) << std::endl;
}

template <typename T>
void print_vector(std::vector<T> const & v){
    for (const auto el: v){
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main(){
    testIsPrefix();
}
