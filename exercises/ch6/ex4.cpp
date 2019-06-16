#include <random>
#include <vector>
#include <iostream>
#include <functional>

int main(){
    auto random_gen = std::bind(std::normal_distribution<>{15, 5}, std::default_random_engine{});
    std::vector<int> hist(30, 0);
    for (int i=0; i<200; i++){
        ++hist[(int)random_gen()];
    }
    for (std::vector<int>::size_type i=0; i<hist.size(); i++){
        std::cout << i << '\t';
        for (int j=0; j<hist[i]; j++){
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}
