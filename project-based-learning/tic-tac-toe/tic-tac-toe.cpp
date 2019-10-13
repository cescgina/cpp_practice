#include <iostream>
#include <string>
#include <unistd.h>
#include "board.h"

void print_args(){
    std::cerr << "Usage is: ./game_of_life.o [-s size_string]" << std::endl;
    std::cerr << "Input parameters description:" << std::endl;
    std::cerr << "\t-s: Board size ( written as heightxwidth)" << std::endl;
}

int main(int argc, char** argv){
   int width = 3, height = 3, c;
   std::string size_str = "";
   size_t pos = 0;
   while ((c = getopt (argc, argv, "hs:")) != -1){
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
        }
   }
   Board game = Board(height, width);
   bool finishGame = false;
   while (!finishGame){
       game.printBoard();
       finishGame = game.gameTurn();
       if (!finishGame and !game.hasMoves()){
            game.printTie();
            break;
       }
   }
}
