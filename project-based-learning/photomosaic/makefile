CC=g++
#CFLAGS=-Wall -g -I/usr/include/ImageMagick-6 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -lMagickCore-6.Q16
CFLAGS=-Wall -O2 -Wpedantic -Wextra `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing -I utilities
debug_CFLAGS=-Wall -g -Wpedantic -Wextra `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing -I utilities
LDLIBS=-lstdc++fs

test_image:
	$(CC) $(CFLAGS) -o image_processing/test_image.o image_processing/test_image.cpp image_processing/image_processing.cpp
	image_processing/test_image

main:
	$(CC) $(CFLAGS) -o photomosaic.o photomosaic.cpp image_processing/image_processing.cpp utilities/utilities.cpp $(LDLIBS)

debug:
	$(CC) $(debug_CFLAGS) -o photomosaic.o photomosaic.cpp image_processing/image_processing.cpp utilities/utilities.cpp $(LDLIBS)

crop:
	$(CC) $(CFLAGS) -o crop_photos.o crop_photos.cpp image_processing/image_processing.cpp utilities/utilities.cpp $(LDLIBS)

clean:
	rm image_processing/test_image.o

run: main
	# ./photomosaic.o images/input.jpg 10 images/test_pokemon-tcg-images_cropped/ output_mosaic_small_test.jpg
	./photomosaic.o images/input.jpg 50 images/kaggle-one-shot-pokemon/pokemon-tcg-images_cropped/ images/output_mosaic_kaggle_pokemon-tcg-images.jpg
