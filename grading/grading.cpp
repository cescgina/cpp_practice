#include "iostream"
#include "algorithm"
using std::cout;
using std::endl;

int main(int argc, char **argv){
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " score" << endl;
    }
    int score = std::stoi(argv[1]);
    score = std::max(score, 50);
    score /= 10;
    switch (score){
        case 5:
            cout << "Your grade is F" << endl;
            break;
        case 6:
            cout << "Your grade is D" << endl;
            break;
        case 7:
            cout << "Your grade is C" << endl;
            break;
        case 8:
            cout << "Your grade is B" << endl;
            break;
        case 9:
            cout << "Your grade is A" << endl;
            break;
        case 10:
            cout << "Congratulations, you got a perfect score!!" << endl;
            break;
            
    }

}
