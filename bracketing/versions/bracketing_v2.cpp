#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char **argv){
    srand(time(NULL));
    int num = rand() % 100 + 1;
    int guess, n_guess=0;
    while (true){
        cout << "SHOW ME WHAT YOU GOT!" << endl;
        std::cin >> guess;
        n_guess++;
        if (guess == num){
            cout << "You good, it only took you " << n_guess << " guesses!" << endl;
            break;
        }
        else if (guess > num) cout << "Too high" << endl;
        else if (guess < num) cout << "Too low" << endl;
    }
}
