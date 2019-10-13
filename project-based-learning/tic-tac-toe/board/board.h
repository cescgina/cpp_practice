#include <string>
#include <vector>
#include <exception>

typedef std::vector<std::vector<int>> board_matrix;

class Board{
    public:
        Board(int width, int height);
        Board(board_matrix& new_board);
        void printBoard();
        bool gameTurn();
        void setBoard(board_matrix& b);
        board_matrix getBoard();
        int getWidth();
        int getHeight();
        bool hasMoves();
        void printTie();
        bool checkVictory(int x, int y, int player);
        bool makeMove(int x, int y, int player);
    private:
        board_matrix board;
        char player_1;
        char player_2;
        int board_width;
        int board_height;
};
