#include <vector>
#include <exception>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "board.h"

MATCHER_P(IntPointwise, tol, "Out of range") {
    return (std::get<0>(arg)==std::get<1>(arg));
}

namespace {
    TEST(BoardTests, test1){
        board_matrix expected_array = {{1, 0}, {1, 0}};
        board_matrix testing_array = {{1, 0}, {1, 0}};
        for (std::size_t i=0; i < testing_array.size(); i++){
            EXPECT_THAT(testing_array[i], testing::Pointwise(IntPointwise(0), expected_array[i]));
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
