#include <vector>
#include <Magick++.h>
#include "utilities.h"
#include "image_processing.h"
using namespace Magick;

pixels_array preprocess_image(const Magick::Image & image) {
    size_t width = image.columns(), height = image.rows();
    float conversion = (float)QuantumRange*3;
    pixels_array average(height, std::vector<float>(width, 0));
    for (size_t i=0; i<height; i++){
        const Magick::PixelPacket* pixels = image.getConstPixels(0, i, width, 1); 
        for (size_t j=0; j<width; j++){
            average[i][j] = (pixels[j].red + pixels[j].green + pixels[j].blue)/conversion;
        }
    }
    return average;
}
