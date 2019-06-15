#include <vector>
#include <string>
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
    std::vector<std::string> test_vector = {"Kant", "Plato", "Aristotle", "Kierkegard", "Hume"};
    print_vector(test_vector);
    std::sort(test_vector.begin(), test_vector.end());
    print_vector(test_vector);
}
