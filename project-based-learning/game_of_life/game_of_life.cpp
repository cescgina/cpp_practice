#include <string>
#include <iostream>
#include <unistd.h>
#include "board.h"


void print_args(){
    std::cerr << "Usage is: ./game_of_life.o width height" << std::endl;
    std::cerr << "Input parameters description:" << std::endl; 
    std::cerr << "\twidth: Board width (in characters)" << std::endl;
    std::cerr << "\theight: Board height (in characters)" << std::endl;
    std::cerr << "\titerations: Number of iterations to run" << std::endl;
}

int main(int argc, char** argv){
    if (argc < 4) {
        // TODO: Finish cli description
        std::cerr << "Unsufficient number of arguments!!" << std::endl;
        print_args();
        return -1;
    }
    int c;
    while ((c = getopt (argc, argv, "h")) != -1){
        switch (c){
          case 'h':
            print_args();
            return -1;
        }
    }
    int width = std::stoi(std::string(argv[optind])), height = std::stoi(std::string(argv[optind+1]));
    int n_iterations = std::stoi(std::string(argv[optind+2]));
    Board game_board = Board(width, height);
    game_board.printBoard();
    for (int i=0; i < n_iterations; i++){
        game_board.stepBoard();
        game_board.printBoard();
    }

}
