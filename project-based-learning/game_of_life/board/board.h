#include <string>
#include <vector>

typedef std::vector<std::vector<int>> board_matrix;
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
