#include <iostream>
#include "Magick++.h"
#include "image_processing.h"

int main(int argc, char** argv) {
    Magick::InitializeMagick(*argv);
    Magick::Image input_img("images/input.jpg");
    int resolution_block = 5;
    size_t width = input_img.columns(), heigth = input_img.rows();
    auto new_resolutions = calculate_resolutions(resolution_block, heigth, width);
    size_t res_x = new_resolutions.first;
    size_t res_y = new_resolutions.second;
    auto avg_pixels = preprocess_image(input_img, res_x, res_y);
    Magick::Image average_image = input_img;
    // average_image.type(Magick::TrueColorType);
    average_image.modifyImage();
    paint_image(avg_pixels, average_image, res_x, res_y);
    average_image.write("images/average_image.jpg");
    Magick::Image second = input_img;
    Magick::Image third = input_img;
    Magick::Image fourth = input_img;
    std::cout << "Width is " << width << " and height is " << heigth << std::endl;
    input_img.resize(Magick::Geometry(width/2, heigth/2));
    input_img.write("images/resize_input.jpg");
    second.rotate(180);
    second.write("images/rotate_input.jpg");
    third.strokeColor("red"); // line color of the drawings
    third.draw(Magick::DrawableRectangle(0, 0, 300, 150));
    third.annotate("What a monkey boiiii!!!!", Magick::NorthGravity);
    third.write("images/rectangle_input.jpg");
    fourth.blur(2, 5.5);
    fourth.write("images/blurred_input.jpg");
}
