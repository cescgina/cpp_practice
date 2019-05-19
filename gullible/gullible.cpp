#include "iostream"
using std::cout;
using std::endl;

int main(int argc, char **argv){
    int i=0, choice;
    while (true){
        cout << "Please enter any number other than " << i << endl;
        std::cin >> choice;
        if (choice == i){
            cout << "You betrayed me!!!" << endl;
            break;
        }
        i++;
        if (i == 10){
            cout << "Wow, you're more patient then I am, you win." << endl;
            break;
        }

    }
}
