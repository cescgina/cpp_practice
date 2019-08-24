#include <string>
#include <iostream>
#include "Magick++.h"
#include "image_processing.h"

int main(int argc, char** argv){
    Magick::InitializeMagick(*argv);
    std::string input_file(argv[1]);
    Magick::Image input_img(input_file);
    int resolution_block = std::stoi(std::string(argv[2]));
    size_t width = input_img.columns(), heigth = input_img.rows();
    auto new_resolutions = calculate_resolutions(resolution_block, heigth, width);
    size_t res_x = new_resolutions.first;
    size_t res_y = new_resolutions.second;
    auto avg_pixels = preprocess_image(input_img, res_x, res_y);
    // TODO: this part is just a test, will not be necessary for the final
    // program
    Magick::Image average_image = input_img;
    average_image.modifyImage();
    paint_image(avg_pixels, average_image, res_x, res_y);
    average_image.write("images/average_image.jpg");

}
