#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
void print_vector(std::vector<T> const & v){
    for (const auto el: v){
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> test_vector = {5, 9, -1, 200, 0};
    print_vector(test_vector);
    std::sort(test_vector.begin(), test_vector.end());
    print_vector(test_vector);
}
