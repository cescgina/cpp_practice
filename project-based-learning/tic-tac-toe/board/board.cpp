#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "board.h"

Board::Board(int width, int height){
    board_width = width;
    board_height = height;
    player_1 = 'X';
    player_2 = 'O';
    board = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

Board::Board(board_matrix& new_board){
    board_height = new_board.size();
    board_width = new_board[0].size();
    board = std::move(new_board);
    player_1 = 'X';
    player_2 = 'O';
}

void Board::printBoard(){
    std::cout << "  ";
    for (int i=0; i<board_width; i++){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i=0; i<2*board_width; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i=0; i<board_height; i++){
        std::cout << i << "|";
        for (int j=0; j<board_width; j++){
            if (board[i][j]==1){
                std::cout << player_1;
            }
            else if (board[i][j]==2){
                std::cout << player_2;
            }
            else {
                std::cout << " ";
            }
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "  ";
    for (int i=0; i<2*board_width; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
}

bool Board::gameTurn(){
    int x, y;
    bool validMove = false;
    while (!validMove){
        std::cout << "Player 1, enter the x y coordinates for your next move:" << std::endl; 
        std::cin >> x >> y;
        validMove = makeMove(x, y, 1);
        if (checkVictory(x, y, 1)){
            printBoard();
            std::cout << "Congratulations Player 1! You win!!" << std::endl;
            return true;
        }
    }
    if (!hasMoves()){
        printTie();
        return true;
    }
    printBoard();
    validMove = false;
    while (!validMove){
        std::cout << "Player 2, enter the x y coordinates for your next move:" << std::endl; 
        std::cin >> x >> y;
        validMove = makeMove(x, y, 2);
        if (checkVictory(x, y, 2)){
            printBoard();
            std::cout << "Congratulations Player 2! You win!!" << std::endl;
            return true;
        }
    }
    return false;
}

bool Board::hasMoves(){
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
            if (board[i][j] == 0) return true;
        }
    }
    return false;
}

bool Board::makeMove(int x, int y, int player){
    if (x < 0 or x >= board_height or y < 0 or y >= board_width){
        std::cout << "The move you entered is outside the board, please input another one" << std::endl;     
        return false;
    }
    if (board[x][y] != 0){
        std::cout << "The specified position is already filled, please input another one" << std::endl;
        return false;
    }
    board[x][y] = player;
    return true;
}

bool Board::checkVictory(int x, int y, int player){
    int lower_row = std::max(x-2, 0);
    int higher_row = std::min(x+2, board_height-2);
    int lower_col = std::max(y-2, 0);
    int higher_col = std::min(y+2, board_width-2);
    //check horizontal match
    for (int i=lower_col; i< higher_col; i++){
        if (board[x][i] == player and board[x][i+1] == player and board[x][i+2] == player){
            return true;
        }
    } 
    //check vertical match
    for (int i=lower_row; i< higher_row; i++){
        if (board[i][y] == player and board[i+1][y] == player and board[i+2][y] == player){
            return true;
        }
    } 
    //check main diagonal match
    int i=lower_row, j=lower_col; 
    while (i<higher_row and j<higher_col){
        if (board[i][j] == player and board[i+1][j+1] == player and board[i+2][j+2] == player){
            return true;
        }
        i++;
        j++;
    }
    //check reverse diagonal match
    i=higher_row+1, j=lower_col;
    while (i>=lower_row and j<higher_col){
        if (board[i][j] == player and board[i-1][j+1] == player and board[i-2][j+2] == player){
            return true;
        }
        i--;
        j++;
    }
    return false;
}

void Board::setBoard(board_matrix& new_board){
   board = std::move(new_board);
}

board_matrix Board::getBoard(){
    return board;
}

int Board::getWidth(){
   return board_width;
}

int Board::getHeight(){
   return board_height;
}

void Board::printTie(){
    std::cout << "There are no more possible moves, game over!!!" << std::endl;
}
