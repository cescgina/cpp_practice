CC=g++
CFLAGS=-Wall -O2 -Wpedantic -Wextra -I board
debug_CFLAGS=-Wall -g -Wpedantic -Wextra -I board
TEST_CFLAGS=-Wall -g -Wpedantic -Wextra -lgtest -lgmock -lpthread -I board

main:
	$(CC) $(CFLAGS) -o game_of_life.o game_of_life.cpp board/board.cpp

debug:
	$(CC) $(debug_CFLAGS) -o game_of_life.o game_of_life.cpp board/board.cpp

test:
	$(CC) $(TEST_CFLAGS) -o test.o tests/test.cpp board/board.cpp
	./test.o

run: main
	./game_of_life.o 
