#include "board.h"


int main(int argc, char** argv){
    int w = 10, h = 10;
    Board game_board = Board(w, h);
    game_board.printBoard();
    game_board.stepBoard();
    game_board.printBoard();
}
