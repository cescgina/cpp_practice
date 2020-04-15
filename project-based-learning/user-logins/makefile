CC=g++
CFLAGS=-Wall -O2 -Wpedantic -Wextra -lcrypt -I backend
debug_CFLAGS=-Wall -g -Wpedantic -Wextra -lcrypt -I backend
TEST_CFLAGS=-Wall -g -Wpedantic -Wextra -lcrypt -lgtest -lgmock -lpthread -I backend

main:
	$(CC) $(CFLAGS) -o access.o access.cpp backend/backend.cpp

debug:
	$(CC) $(debug_CFLAGS) -o access.o access.cpp backend/backend.cpp

test:
	$(CC) $(TEST_CFLAGS) -o test.o tests/test.cpp backend/backend.cpp
	./test.o

run: main
	./access.o

run_debug: debug
	./access.o
