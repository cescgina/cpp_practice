#include <string>
#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include "board.h"

Board create_board(const std::string& input, const int w, const int h){
    if (input != ""){
        return Board(input);
    }
    else{
        return Board(w, h);
    }
}

void print_args(){
    std::cerr << "Usage is: ./game_of_life.o [-s size_string] [-f input_file] [-n iterations]" << std::endl;
    std::cerr << "Input parameters description:" << std::endl; 
    std::cerr << "\t-s: Board size (in characters, written as heightxsize)" << std::endl;
    std::cerr << "\t-f: Input file with board state to start the simulation" << std::endl;
    std::cerr << "\t-n: Number of iterations to run (default is 10)" << std::endl;
    std::cerr << "\t-t: Time to wait between turns (in seconds, default is 0.5)" << std::endl;
}

int main(int argc, char** argv){
    if (argc < 2) {
        std::cerr << "Unsufficient number of arguments!!" << std::endl;
        print_args();
        return -1;
    }
    int c, width = 0, height = 0, n_iterations=10;
    std::string size_str = "", input_file = "";
    size_t pos = 0;
    float speed = 0.5;
    while ((c = getopt (argc, argv, "hs:f:n:t:")) != -1){
        switch (c){
          case 'h':
            print_args();
            return -1;
          case 's':
            size_str = optarg;
            pos = size_str.find(':');
            height = std::stoi(size_str.substr(0, pos));
            width = std::stoi(size_str.substr(pos+1));
            break;
          case 'f':
            input_file = optarg;
            break;
          case 'n':
            n_iterations = std::stoi(optarg);
            break;
          case 't':
            speed = std::stof(optarg);
        }
    }
    if (width*height == 0 && input_file == ""){
        throw std::invalid_argument("One of -s or -f options must be defined!");
    }
    initscr();
    Board game_board = create_board(input_file, height, width);
    game_board.printBoard();
    for (int i=0; i < n_iterations; i++){
        game_board.stepBoard();
        game_board.printBoard();
        usleep(speed*1e6);
    }
    endwin();
}
