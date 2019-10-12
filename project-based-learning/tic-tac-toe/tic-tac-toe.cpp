#include <iostream>
#include "board.h"

int main(int argc, char** argv){
   Board game = Board(3, 3); 
   bool finishGame = false;
   while (!finishGame){
       game.printBoard();
       finishGame = game.gameTurn();
       if (!game.hasMoves()){
            std::cout << "There are no more possible moves, game over!!!" << std::endl;
       }
   }
}
