#include <vector>
#include <iostream>
#include <algorithm>
#include <Magick++.h>
#include "utilities.h"
#include "image_processing.h"

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

void crop_photo(Magick::Image& image, std::string& output_folder, std::string& image_name){
    size_t width = image.columns(), height = image.rows(), final_size;
    final_size = std::min(height, width);
    image.crop(Magick::Geometry(final_size, final_size));
    image.write(output_folder+"/"+image_name);
}


void construct_image_from_files(Magick::Image& image, files_array& files, size_t res_x, size_t res_y){
    size_t rows = files.size(), cols = files[0].size();
    for (size_t i=0; i < rows; i++){
        for (size_t j=0; j < cols; j++){
            Magick::Image src_img(files[i][j]);
            src_img.resize(Magick::Geometry(res_y, res_x));
            //image.type(Magick::TrueColorType);
            //src_img.type(Magick::TrueColorType);
            src_img.modifyImage();
            image.modifyImage();
            Magick::PixelPacket *pixel_cache = image.getPixels(j*res_y, i*res_x, res_y, res_x);
            Magick::PixelPacket *src_pixel_cache = src_img.getPixels(0, 0, res_y, res_x);
            for (size_t k=0; k < res_y; k++){
                for (size_t l=0; l < res_x; l++){
                    pixel_cache[l+k*res_x] = src_pixel_cache[l+k*res_x];
                }
            }
            image.syncPixels(); 
        }
    }
}
