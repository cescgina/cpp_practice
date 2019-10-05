#include <string>
#include <vector>
#include <exception>

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
        void printBoard();
        void stepBoard();
        void setBoard(board_matrix& b);
        void setBoard(const std::string& path_file);
        void saveBoard(const std::string& path_file);
    private:
        board_matrix board;
        board_matrix alt_board;
        int board_width;
        int board_height;
        void setRandomBoard();
        int countNeighbors(const int row, const int col);
};
