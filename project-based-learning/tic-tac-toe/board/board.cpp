#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "board.h"

char const* FileTooSmallException::what () const noexcept{
    return "Provided file is too small!";
}

char const* FileTooBigException::what () const noexcept{
    return "Provided file is too big!";
}

char const* FileNotFoundException::what () const noexcept{
    return "Provided file could not be opened!";
}

Board::Board(int width, int height){
    board_width = width;
    board_height = height;
    player_1 = 'X';
    player_2 = 'O';
    board = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    has_printed = false;
}

Board::Board(board_matrix& new_board){
    board_height = new_board.size();
    board_width = new_board[0].size();
    board = std::move(new_board);
    has_printed = false;
    player_1 = 'X';
    player_2 = 'O';
}

Board::Board(const std::string& path_file){
    has_printed = false;
    player_1 = 'X';
    player_2 = 'O';
    board = std::vector<std::vector<int>>();
    std::vector<int> board_row;
    std::ifstream saved_board;
    saved_board.open(path_file);
    if (!saved_board.is_open()){
        throw FileNotFoundException();
    }
    char temp;
    while (saved_board.get(temp)){
        if (temp <= '9' and temp >= '0') {
            board_row.push_back(temp-'0');
        }
        else{
            // whitespace or newline, if we have a line stored, update the
            // board matrix, else do nothing
            if(board_row.size() > 0){
                board.push_back(board_row);
                board_row = {};
            }
        }
    }
    board_height = board.size();
    board_width = board[0].size();
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
/*
void Board::printBoard(){
    if (has_printed){
        wmove(win, 1, 1);
    }
    else{
        win = newwin(board_height+2, board_width+2, 0, 0);
        wmove(win, 0, 0);
        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
        wmove(win, 1, 1);
    }
    for (int i=0; i<board_height; i++){
        if (!has_printed){
            wmove(win, i+1, 1);
        }
        else{
            wmove(win, i+1, 1);
        }
        for (int j=0; j<board_width; j++){
           if (board[i][j] == 0) waddch(win, ' ');
           else waddch(win, '#');
        }
    }
    if (!has_printed){
        has_printed = true;
    }
    wrefresh(win);
} 
*/

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
    //check diagonal match
    int i=lower_row, j=lower_col; 
    while (i<higher_row and j<higher_col){
        if (board[i][j] == player and board[i+1][j+1] == player and board[i+2][j+2] == player){
            return true;
        }
        i++;
        j++;
    }
    return false;
}

void Board::setBoard(board_matrix& new_board){
   board = std::move(new_board);
}

void Board::setBoard(const std::string& path_file){
    std::ifstream saved_board;
    char temp;
    saved_board.open(path_file);
    if (!saved_board.is_open()){
        throw FileNotFoundException();
    }
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
            if (saved_board.eof()){
                throw FileTooSmallException();
            }
            saved_board >> temp;
            board[i][j] = temp-'0';
        }
    }
    int a, c=0;
    while (saved_board){
        saved_board >> a;
        c++;
    }
    // if there were more than one reads possible, then the wrong board dimensions
    // were specified (the last read was the newline)
    if(c > 1){
        throw FileTooBigException();
    }
    saved_board.close();
}

void Board::saveBoard(const std::string& path_file){
    std::ofstream saved_board;
    saved_board.open(path_file);
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
            saved_board << board[i][j];
        }
        saved_board << std::endl;
    }
    saved_board.close();
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
