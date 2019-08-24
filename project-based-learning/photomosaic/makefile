CC=g++
#CFLAGS=-Wall -g -I/usr/include/ImageMagick-6 -fopenmp -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -lMagickCore-6.Q16
CFLAGS=-Wall -g `Magick++-config --cppflags --cxxflags --ldflags --libs` -I image_processing

test_image:
	$(CC) $(CFLAGS) -o image_processing/test_image.o image_processing/test_image.cpp image_processing/image_processing.cpp
	image_processing/test_image

main:
	$(CC) $(CFLAGS) -o photomosaic.o photomosaic.cpp image_processing/image_processing.cpp

crop:
	$(CC) $(CFLAGS) -o crop_photos.o crop_photos.cpp image_processing/image_processing.cpp

clean:
	rm image_processing/test_image.o
