#include <vector>
#include <utility>
#include <iostream>
#include <Magick++.h>
#include "image_processing.h"

std::pair<int, int> calculate_resolutions(int original_res, int rows, int cols){
    int res_x = original_res, res_y = original_res;
    while (rows % res_y != 0){
        res_y--;
    }
    while (cols % res_x != 0){
        res_x--;
    }
    return std::pair<int, int>(res_x, res_y);
}

pixels_array preprocess_image(Magick::Image & image, size_t res_x, size_t res_y) {
    size_t width = image.columns(), height = image.rows();
    int pixels_block = res_x*res_y;
    size_t row_blocks = height/res_y, col_blocks = width/res_x;
    pixels_array average(row_blocks, std::vector<std::vector<float>>(col_blocks, std::vector<float>(3, 0))); 
    image.modifyImage();
    for (size_t i=0; i<height; i++){
        for (size_t j=0; j<width; j++){
            Magick::ColorRGB px = image.pixelColor(j, i);
            average[i/res_y][j/res_x][0] += px.red();
            average[i/res_y][j/res_x][1] += px.green();
            average[i/res_y][j/res_x][2] += px.blue();
        }
    }
    for (size_t i=0; i<row_blocks; i++){
        for (size_t j=0; j<col_blocks; j++){
            average[i][j][0] /= pixels_block;
            average[i][j][1] /= pixels_block;
            average[i][j][2] /= pixels_block;
        }
    }
    return average;
}

void paint_image(pixels_array& pixels, Magick::Image& img, size_t res_x, size_t res_y){
    size_t width = img.columns(), height = img.rows();
    /* Important reminder, Magick++ considers the x the horizontal axis,
     * opposite to row-major order, so acces using (column, row) 
     */
    for (size_t i=0; i<height; i++){
        for (size_t j=0; j<width; j++){
            img.pixelColor(j, i, Magick::ColorRGB(pixels[i/res_y][j/res_x][0], pixels[i/res_y][j/res_x][1], pixels[i/res_y][j/res_x][2]));
        }
    }
    img.syncPixels();
}
