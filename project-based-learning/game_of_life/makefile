CC=g++
CFLAGS=-Wall -O2 -Wpedantic -Wextra -lncurses -I board
debug_CFLAGS=-Wall -g -Wpedantic -Wextra -lncurses -I board
TEST_CFLAGS=-Wall -g -Wpedantic -Wextra -lgtest -lgmock -lncurses -lpthread -I board

main:
	$(CC) $(CFLAGS) -o game_of_life.o game_of_life.cpp board/board.cpp

debug:
	$(CC) $(debug_CFLAGS) -o game_of_life.o game_of_life.cpp board/board.cpp

test:
	$(CC) $(TEST_CFLAGS) -o test.o tests/test.cpp board/board.cpp
	./test.o

run: main
	./game_of_life.o -s 10x10 -n 10
