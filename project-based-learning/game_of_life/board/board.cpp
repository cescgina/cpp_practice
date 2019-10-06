#include <random>
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
    board = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    alt_board = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    setRandomBoard();
    has_printed = false;
}

Board::Board(board_matrix& new_board){
    board_height = new_board.size();
    board_width = new_board[0].size();
    board = std::move(new_board);
    alt_board = std::vector<std::vector<int>>(board_height, std::vector<int>(board_width, 0));
    has_printed = false;
}

Board::Board(const std::string& path_file){
    has_printed = false;
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
    alt_board = std::vector<std::vector<int>>(board_height, std::vector<int>(board_width, 0));
}

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

void Board::setRandomBoard(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> random_gen(0, 1);
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
            if (random_gen(rng) <= 0.5){
                board[i][j] = 1;
            }  
        }
    }
}
void Board::stepBoard(){
    int neighbors=0;
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
           neighbors = countNeighbors(i, j); 
           if (board[i][j] == 1){
               if (neighbors == 2 or neighbors == 3){
                   alt_board[i][j] = 1;
               }
               else {
                   alt_board[i][j] = 0;
               }
           }
           else{
               if (neighbors == 3){
                   alt_board[i][j] = 1;
               }
               else{
                   alt_board[i][j] = board[i][j];
               }
           }
        }
    }
    board.swap(alt_board);
}

int Board::countNeighbors(int row, int col){
    if (row == 0){
        if (col == 0){
            return board[row][col+1]+board[row+1][col+1]+board[row+1][col];
        }
        if (col == board_width-1){
            return board[row][col-1]+board[row+1][col-1]+board[row+1][col];
        } 
        else if (col != board_width-1){
            return board[row][col-1]+board[row+1][col-1]+board[row+1][col]+board[row][col+1]+board[row+1][col+1];
        }
    }
    else if (row == board_height-1){
        if (col == 0){
            return board[row][col+1]+board[row-1][col+1]+board[row-1][col];
        }
        if (col == board_width-1){
            return board[row][col-1]+board[row-1][col-1]+board[row-1][col];
        } 
        else if (col != board_width-1){
            return board[row][col-1]+board[row-1][col-1]+board[row-1][col]+board[row][col+1]+board[row-1][col+1];
        }
    }
    else{
        if (col == 0){
            return board[row][col+1]+board[row-1][col+1]+board[row-1][col]+board[row+1][col]+board[row+1][col+1];
        }
        if (col == board_width-1){
            return board[row][col-1]+board[row-1][col-1]+board[row-1][col]+board[row+1][col]+board[row+1][col-1];
        } 
        else if (col != board_width-1){
            return board[row][col-1]+board[row][col+1]+board[row-1][col]+board[row-1][col+1]+board[row-1][col-1]+board[row+1][col]+board[row+1][col+1]+board[row+1][col-1];
        }
    }
    return 0;
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
board_matrix Board::getNeighborsCount(){
    board_matrix result = std::vector<std::vector<int>>(board_height, std::vector<int>(board_width, 0));
    for (int i=0; i<board_height; i++){
        for (int j=0; j<board_width; j++){
            result[i][j] = countNeighbors(i, j);
        }
    }
    return result;
}
