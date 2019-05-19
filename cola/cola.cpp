#include "iostream"
using std::cout;
using std::endl;

int main(int argc, char **argv){
    int choice;
    cout << "Please select your drink from 1-5" << endl;
    std::cin >> choice;
    switch (choice){
        case 1:
            cout << "You have selected number 1" << endl;
            break;
        case 2:
            cout << "You have selected number 2" << endl;
            break;
        case 3:
            cout << "You have selected number 3" << endl;
            break;
        case 4:
            cout << "You have selected number 4" << endl;
            break;
        case 5:
            cout << "You have selected number 5" << endl;
            break;
        default:
            cout << "Error. choice was not valid, here is your money back." << endl;
            break;
            
    }

}
