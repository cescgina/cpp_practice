#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char **argv){
    srand(time(NULL));
    int num = rand() % 100 + 1;
    int guess;
    while (true){
        cout << "SHOW ME WHAT YOU GOT!" << endl;
        std::cin >> guess;
        if (guess == num){
            cout << "You good!" << endl;
            break;
        }
        else if (guess > num) cout << "Too high" << endl;
        else if (guess < num) cout << "Too low" << endl;
    }
}
