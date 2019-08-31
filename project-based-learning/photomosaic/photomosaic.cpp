#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Magick++.h"
#include "utilities.h"
#include "image_processing.h"

int main(int argc, char** argv){
    if (argc < 4) {
        // TODO: Finish cli description
        std::cout << "Unsufficient number of arguments!!" << std::endl;
        std::cout << "Usage is: ./photomosaic.o input_image resolution source_images output_image" << std::endl;
        std::cout << "Input parameters description:" << std::endl; 
        std::cout << "\tinput_image: path to the base image for the mosaic" << std::endl;
        std::cout << "\tresolution: Size of the blocks to split the base image" << std::endl;
        std::cout << "\tsource_images: path to the source image for the mosaic" << std::endl;
        std::cout << "\toutput_image: path to store the resulting mosaic" << std::endl;
        return -1;
    }
    Magick::InitializeMagick(*argv);
    std::string input_file(argv[1]);
    Magick::Image input_img(input_file);
    int resolution_block = std::stoi(std::string(argv[2]));
    std::string source_path(argv[3]);
    std::string output_image(argv[4]);
    size_t width = input_img.columns(), heigth = input_img.rows();
    auto new_resolutions = calculate_resolutions(resolution_block, heigth, width);
    size_t res_x = new_resolutions.first;
    size_t res_y = new_resolutions.second;
    auto avg_pixels = preprocess_image(input_img, res_x, res_y);
    /*
    // TODO: this part is just a test, will not be necessary for the final
    // program
    Magick::Image average_image = input_img;
    average_image.modifyImage();
    paint_image(avg_pixels, average_image, res_x, res_y);
    average_image.write("images/average_image.jpg");
    */
    // characterize source photos
    std::list<std::string> photos = get_list_photos(source_path);
    sources_map source_colors;
    for (std::list<std::string>::iterator i=photos.begin(); i!=photos.end(); i++){
        Magick::Image source_img;
        try{
            source_img.read(*i);
            size_t width_src = source_img.columns(), heigth_src = source_img.rows();
            source_colors[*i] = preprocess_image(source_img, heigth_src, width_src)[0][0];
        }
        catch (Magick::ErrorCorruptImage& my_error) { 
            std::cout << "a Magick++ error occurred in file " << *i << ": " << my_error.what() << std::endl;
        }
    }
    auto matched_files = match_sources_files(avg_pixels, source_colors);
    Magick::Image output_img = input_img;
    construct_image_from_files(output_img, matched_files, res_x, res_y);
    output_img.write(output_image);
}
