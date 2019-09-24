CC=g++
#CFLAGS=-Wall -g -I/usr/include/ImageMagick-6 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -lMagickCore-6.Q16
CFLAGS=-Wall -O2 -Wpedantic -Wextra `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing -I utilities
debug_CFLAGS=-Wall -g -Wpedantic -Wextra `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing -I utilities
TEST_CFLAGS=-Wall -g -Wpedantic -Wextra -lgtest -lgmock -lpthread `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing -I utilities

main:
	$(CC) $(CFLAGS) -o ascii-art.o ascii-art.cpp image_processing/image_processing.cpp utilities/utilities.cpp

debug:
	$(CC) $(debug_CFLAGS) -o ascii-art.o ascii-art.cpp image_processing/image_processing.cpp utilities/utilities.cpp

test:
	$(CC) $(TEST_CFLAGS) -o test.o tests/test.cpp image_processing/image_processing.cpp utilities/utilities.cpp
	./test.o

run: main
	./ascii-art.o images/ascii-pineapple.jpg 
