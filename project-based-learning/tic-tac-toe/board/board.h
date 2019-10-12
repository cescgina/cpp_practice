#include <string>
#include <vector>
#include <exception>
#include <ncurses.h>

typedef std::vector<std::vector<int>> board_matrix;

class FileNotFoundException : public std::exception {
 public:
    virtual char const* what () const noexcept;
};

class FileTooBigException : public std::exception {
 public:
    virtual char const* what () const noexcept;
};

class FileTooSmallException : public std::exception {
 public:
    virtual char const* what () const noexcept;
};

class Board{
    public:
        Board(int width, int height);
        Board(board_matrix& new_board);
        Board(const std::string& path_file);
        void printBoard();
        bool gameTurn();
        void setBoard(board_matrix& b);
        void setBoard(const std::string& path_file);
        void saveBoard(const std::string& path_file);
        board_matrix getBoard();
        int getWidth();
        int getHeight();
        bool hasMoves();
    private:
        board_matrix board;
        char player_1;
        char player_2;
        bool has_printed;
        int board_width;
        int board_height;
        bool checkVictory(int x, int y, int player);
        bool makeMove(int x, int y, int player);
        //WINDOW * win;
};
