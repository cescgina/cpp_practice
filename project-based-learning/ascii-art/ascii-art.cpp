#include <map>
#include <list>
#include <string>
#include <vector>
#include <chrono>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unistd.h>
#include "Magick++.h"
#include "utilities.h"
#include "image_processing.h"

void print_args(){
    std::cerr << "Usage is: ./ascii-art.o input_image" << std::endl;
    std::cerr << "Input parameters description:" << std::endl; 
    std::cerr << "\tinput_image: Path to the base image for the mosaic" << std::endl;
}

int main(int argc, char** argv){
    if (argc < 2) {
        // TODO: Finish cli description
        std::cerr << "Unsufficient number of arguments!!" << std::endl;
        print_args();
        return -1;
    }
    int c;
    while ((c = getopt (argc, argv, "h")) != -1){
        switch (c){
          case 'h':
            print_args();
            return -1;
        }
    }
    Magick::InitializeMagick(*argv);
    std::string input_file(argv[optind]);
    Magick::Image input_img(input_file);
    input_img.resize("100x100");
    auto start = std::chrono::steady_clock::now();
    auto avg_pixels = preprocess_image(input_img);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    auto time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to process input image" << std::endl;;

    start = std::chrono::steady_clock::now();
    construct_ascii_art(avg_pixels);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::steady_clock::now() - start);
    time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " s to construct image" << std::endl;;
}
