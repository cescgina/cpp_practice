#include "iostream"
#include "vector"
#include "algorithm"
#include "tuple"
using std::cout;
using std::endl;

int main(int argc, char **argv){
    std::vector<std::tuple<int, int>> numbers(10);
    int n;
    for (int i=0; i<10; i++){
        cout << "Please enter the amount of pancakes eaten by person " << i+1 << endl;
        std::cin >> n;
        numbers[i] = std::make_tuple(n, i);
    }
    std::sort(numbers.begin(), numbers.end(), std::greater<std::tuple<int, int>>());
    for (std::vector<std::tuple<int, int>>::iterator it=numbers.begin(); it != numbers.end(); it++){
        cout << "Person " << std::get<1>(*it) << " ate " << std::get<0>(*it) << " pancakes" << endl;
    }
}
