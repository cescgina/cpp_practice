#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <Magick++.h>
#include "utilities.h"
#include "image_processing.h"
using namespace Magick;

pixels_array preprocess_image(Magick::Image & image, size_t res_x, size_t res_y, int image_fractions) {
    size_t width = image.columns(), height = image.rows();
    int block_res = std::sqrt(image_fractions);
    std::div_t res = std::div(res_x, block_res);
    int x_blk=(res.quot)+(res.rem != 0), rem_x, rem_y; 
    res = std::div(res_y, block_res);
    int y_blk=(res.quot)+(res.rem != 0);
    size_t row_blocks = height/res_x, col_blocks = width/res_y, k;
    pixels_array average(row_blocks, std::vector<std::vector<float>>(col_blocks, std::vector<float>(image_fractions*3, 0)));
    pixels_array pixel_nums(row_blocks, std::vector<std::vector<float>>(col_blocks, std::vector<float>(image_fractions, 0))); 
    image.modifyImage();
    for (size_t i=0; i<height; i++){
        const Magick::PixelPacket* pixels = image.getConstPixels(0, i, width, 1); 
        rem_x = i % res_x;
        for (size_t j=0; j<width; j++){
            rem_y = j % res_y;
            k = block_res*(rem_x/x_blk) + (rem_y/y_blk);
            average[i/res_x][j/res_y][3*k] += pixels[j].red/(float)QuantumRange;
            average[i/res_x][j/res_y][3*k+1] += pixels[j].green/(float)QuantumRange;
            average[i/res_x][j/res_y][3*k+2] += pixels[j].blue/(float)QuantumRange;
            pixel_nums[i/res_x][j/res_y][k] += 1;
        }
    }
    for (size_t i=0; i<row_blocks; i++){
        for (size_t j=0; j<col_blocks; j++){
            for (size_t k=0; k<image_fractions*(size_t)3; k++){
                average[i][j][k] /= pixel_nums[i][j][k/3];
            }
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
    size_t width = image.columns();
    image_map sources_cache;
    for (size_t i=0; i < rows; i++){
        Magick::PixelPacket *pixel_cache = image.getPixels(0, i*res_x, width, res_x);
        for (size_t j=0; j < cols; j++){
            Magick::Image src_img;
            if (sources_cache.find(files[i][j]) == sources_cache.end()){
                src_img.read(files[i][j]);
                src_img.resize(Magick::Geometry(res_y, res_x));
                sources_cache[files[i][j]] = src_img;
            }
            else{
                src_img = sources_cache[files[i][j]];
            }
            src_img.resize(Magick::Geometry(res_y, res_x));
            src_img.modifyImage();
            image.modifyImage();
            const Magick::PixelPacket *src_pixel_cache = src_img.getConstPixels(0, 0, res_y, res_x);
            for (size_t k=0; k < res_x; k++){
                for (size_t l=0; l < res_y; l++){
                    pixel_cache[l+k*width+j*res_y] = src_pixel_cache[l+k*res_y];
                }
            }
        }
        image.syncPixels(); 
    }
}
