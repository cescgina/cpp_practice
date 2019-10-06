#include <vector>
#include <exception>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "board.h"

MATCHER_P(IntPointwise, tol, "Out of range") {
    return (std::get<0>(arg)==std::get<1>(arg));
}

namespace {
    TEST(BoardTests, test_all_dead){
        board_matrix expected_array = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        board_matrix initial_array = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        Board game = Board(initial_array);
        game.stepBoard();
        board_matrix result = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_dead_to_alive){
        board_matrix initial_array = {{0, 0, 1}, {0, 1, 1}, {0, 0, 0}};
        board_matrix expected_array = {{0, 1, 1}, {0, 1, 1}, {0, 0, 0}};
        Board game = Board(initial_array);
        game.stepBoard();
        board_matrix result = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_alive_to_dead){
        board_matrix initial_array = {{1, 1, 1}, {1, 1, 1}, {0, 0, 0}};
        board_matrix expected_array = {{1, 0, 1}, {1, 0, 1}, {0, 1, 0}};
        Board game = Board(initial_array);
        game.stepBoard();
        board_matrix result = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_alive_1_neighbor){
        board_matrix initial_array = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}};
        board_matrix expected_array = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        Board game = Board(initial_array);
        game.stepBoard();
        board_matrix result = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_alive_0_neighbor){
        board_matrix initial_array = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
        board_matrix expected_array = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        Board game = Board(initial_array);
        game.stepBoard();
        board_matrix result = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }
    TEST(BoardTests, general_test){
        Board game = Board("tests/test_board.txt");
        game.stepBoard();
        board_matrix result = game.getBoard();
        Board golden_game = Board("tests/out_board.txt");
        board_matrix expected_array = game.getBoard();
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_count_neigbors){
        Board game = Board("tests/iteration_8_test.txt");
        board_matrix result = game.getNeighborsCount();
        board_matrix expected_array = {{0,1,0,1,0,2,2,4,4,3}, {1,1,0,1,1,2,3,5,6,4}, {1,1,0,0,0,0,1,3,5,4},
                                       {0,1,0,1,1,1,0,1,3,2}, {1,1,0,2,1,2,0,0,1,1}, {0,0,0,2,1,2,0,0,1,1},
                                       {0,0,0,1,1,1,0,0,1,0}, {1,1,0,0,0,0,0,0,1,1}, {1,2,1,1,2,3,3,2,2,1}, 
                                       {2,1,1,1,1,2,2,1,2,0}};
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, test_general_iteration){
        Board game = Board("tests/iteration_8_test.txt");
        game.stepBoard();
        board_matrix result = game.getBoard();
        board_matrix expected_array = {{0,0,0,0,0,0,1,0,0,1}, {0,0,0,0,0,0,1,0,0,0}, {0,0,0,0,0,0,0,1,0,0},
                                       {0,0,0,0,0,0,0,0,1,1}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0},
                                       {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,1,1,0,0,0}, 
                                       {0,0,0,0,0,1,1,0,0,0}};
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }
    TEST(BoardTests, test_file_constructor){
        Board game = Board("tests/test_board.txt");
        board_matrix result = game.getBoard();
        board_matrix expected_array = {{1,1,0,1,0,0,0,0,0,0}, {0,0,1,0,1,1,1,1,0,0}, {0,1,0,1,0,0,1,1,1,1},
                                       {0,0,1,1,1,1,1,1,0,0}, {0,1,0,0,0,1,1,1,1,0}, {0,0,0,1,1,1,1,1,1,0},
                                       {0,0,1,1,1,1,1,1,1,0}, {0,0,0,1,1,1,1,1,1,0}, {1,1,1,1,1,1,1,1,1,0}, 
                                       {1,0,0,0,0,1,0,0,0,1}};
        for (std::size_t i=0; i < expected_array.size(); i++){
            EXPECT_THAT(result[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
        }
    }

    TEST(BoardTests, too_small_file){
        Board game = Board(14, 14);
        EXPECT_THROW(game.setBoard("tests/test_board.txt"), FileTooSmallException);
    }
    TEST(BoardTests, too_big_file){
        Board game = Board(3, 3);
        EXPECT_THROW(game.setBoard("tests/test_board.txt"), FileTooBigException);
    }
    TEST(BoardTests, non_existing_file){
        Board game = Board(10, 10);
        EXPECT_THROW(game.setBoard("t_board.txt"), FileNotFoundException);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
