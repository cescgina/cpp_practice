#include <list>
#include <string>
#include <vector>
#include <chrono>
#include <utility>
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
    auto start = std::chrono::steady_clock::now();
    auto new_resolutions = calculate_resolutions(resolution_block, heigth, width);
    size_t res_x = new_resolutions.first;
    size_t res_y = new_resolutions.second;
    auto avg_pixels = preprocess_image(input_img, res_x, res_y);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    auto time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to process input image" << std::endl;;
    // characterize source photos
    start = std::chrono::steady_clock::now();
    std::list<std::string> photos = get_list_photos(source_path);
    sources_map source_colors;
    std::vector<float> averages(3, 0), rounded_averages(3, 0);
    for (std::list<std::string>::iterator i=photos.begin(); i!=photos.end(); i++){
        Magick::Image source_img;
        try{
            source_img.read(*i);
            size_t width_src = source_img.columns(), heigth_src = source_img.rows();
            averages = preprocess_image(source_img, heigth_src, width_src)[0][0];
            rounded_averages = round_averages(averages);
            int key = encode_averages(rounded_averages);
            if (source_colors.find(key) == source_colors.end()){
                source_colors[key] = {std::make_pair(*i, averages)};
            }
            else{
                source_colors[key].push_back(std::make_pair(*i, averages));
            }
        }
        catch (Magick::ErrorCorruptImage& my_error) { 
            std::cout << "a Magick++ error occurred in file " << *i << ": " << my_error.what() << std::endl;
        }
    }
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to process source images" << std::endl;;
    start = std::chrono::steady_clock::now();
    auto matched_files = match_sources_files(avg_pixels, source_colors);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to match files to image" << std::endl;;
    Magick::Image output_img = input_img;
    start = std::chrono::steady_clock::now();
    construct_image_from_files(output_img, matched_files, res_x, res_y);
    output_img.write(output_image);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to construct image" << std::endl;;
}
