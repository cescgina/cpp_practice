#include <vector>

typedef std::vector<std::vector<int>> board_matrix;
class Board{
    public:
        Board(int width, int height);
        void printBoard();
        void stepBoard();
    private:
        board_matrix board;
        board_matrix alt_board;
        int board_width;
        int board_height;
        void setRandomBoard();
        int countNeighbors(int row, int col);
};
