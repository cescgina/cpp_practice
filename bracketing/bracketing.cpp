#include <iostream>
#include <string>
using std::cout;
using std::endl;

int main(int argc, char **argv){
    int guess=50, n_guess=0, high=101, low=1;
    std::string ans;
    cout << "Think of a number between 1 and 100 and prepare your mind to be blown!" << endl;
    while (true){
        cout << "Is your number " << guess << " ?[L if too low, H if too high, K if correct]" << endl;
        std::cin >> ans;
        n_guess++;
        if (ans == "H"){
            high = guess;
            guess = (low+high)/2;
        }
        if (ans == "L"){
            low = guess;
            guess = (low+high)/2+1;
        }
        if (ans == "K"){
            cout << "HA, it only took me " << n_guess << " guesses!" << endl;
            break;
        }
    }
}
