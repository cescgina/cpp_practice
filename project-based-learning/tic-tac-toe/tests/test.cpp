#include <vector>
#include <exception>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "board.h"

MATCHER_P(IntPointwise, tol, "Out of range") {
    return (std::get<0>(arg)==std::get<1>(arg));
}

namespace {
    TEST(BoardTests, victory_reverse_diagonal){
        board_matrix initial_array = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};
        Board game = Board(initial_array);
        EXPECT_TRUE(game.checkVictory(0, 2, 1));
    }
    TEST(BoardTests, victory_main_diagonal){
        board_matrix initial_array = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        Board game = Board(initial_array);
        EXPECT_TRUE(game.checkVictory(0, 2, 1));
    }
    TEST(BoardTests, victory_horizontal){
        board_matrix initial_array = {{1, 1, 1}, {0, 0, 0}, {1, 0, 0}};
        Board game = Board(initial_array);
        EXPECT_TRUE(game.checkVictory(0, 2, 1));
    }
    TEST(BoardTests, victory_vertical){
        board_matrix initial_array = {{1, 0, 0}, {1, 0, 0}, {1, 0, 0}};
        Board game = Board(initial_array);
        EXPECT_TRUE(game.checkVictory(0, 0, 1));
    }
    TEST(BoardTests, victory_vertical_4x3){
        board_matrix initial_array = {{0, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}};
        Board game = Board(initial_array);
        EXPECT_TRUE(game.checkVictory(1, 0, 1));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
