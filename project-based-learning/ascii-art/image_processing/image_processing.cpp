#include <vector>
#include <algorithm>
#include <exception>
#include <Magick++.h>
#include "image_processing.h"
using namespace Magick;

ImageProcesser::ImageProcesser(std::string brightness_mode_str){
    brightness_mode = brightness_mode_str;
    if (brightness_mode == "average"){
        conversion_factor = (float)QuantumRange*3;
    }
    else if (brightness_mode == "lightness"){
        conversion_factor = (float)QuantumRange*2;
    }
    else if (brightness_mode == "luminosity"){
        conversion_factor = (float)QuantumRange;
    }
    else{
        throw std::invalid_argument("Specified mode " + brightness_mode +" not found!!");
    }
}

pixels_array ImageProcesser::preprocess_image(const Magick::Image & image) {
    size_t width = image.columns(), height = image.rows();
    pixels_array average(height, std::vector<float>(width, 0));
    for (size_t i=0; i<height; i++){
        const Magick::PixelPacket* pixels = image.getConstPixels(0, i, width, 1); 
        for (size_t j=0; j<width; j++){
            average[i][j] = calculate_brightness(pixels[j]);
        }
    }
    return average;
}

float ImageProcesser::calculate_brightness(const Magick::PixelPacket& pixel){
    if (brightness_mode == "average"){
        return average_brightness(pixel);
    }
    else if (brightness_mode == "lightness"){
        return lightness(pixel);
    }
    else if (brightness_mode == "luminosity"){
        return luminosity(pixel);
    }
    else{
        throw std::invalid_argument("Specified mode " + brightness_mode +" not found!!");
    }
}

float ImageProcesser::average_brightness(const Magick::PixelPacket& pixel){
    return (pixel.red + pixel.green + pixel.blue)/conversion_factor;
}

float ImageProcesser::luminosity(const Magick::PixelPacket& pixel){
    return (-0.21*pixel.red + 0.72*pixel.green + 0.07*pixel.blue)/conversion_factor;
}

float ImageProcesser::lightness(const Magick::PixelPacket& pixel){
    auto values = std::minmax({pixel.red, pixel.green, pixel.blue});
    return (values.first + values.second)/conversion_factor;
}
