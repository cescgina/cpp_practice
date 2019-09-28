#include <string>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include "Magick++.h"
#include "utilities.h"
#include "image_processing.h"

void print_args(){
    std::cerr << "Usage is: ./ascii-art.o input_image" << std::endl;
    std::cerr << "Input parameters description:" << std::endl; 
    std::cerr << "\tinput_image: Path to the base image for the mosaic" << std::endl;
    std::cerr << "\t-s: dimensions to resize image in format widthxheight (default 60x60)" << std::endl;
    std::cerr << "\t-b: function to calculate the pixel brightness (options are average, lightness and luminosity; default is average)" << std::endl;
}

int main(int argc, char** argv){
    if (argc < 2) {
        // TODO: Finish cli description
        std::cerr << "Unsufficient number of arguments!!" << std::endl;
        print_args();
        return -1;
    }
    int c;
    std::string size_str = "60x60";
    std::string brightness_option = "average";
    while ((c = getopt (argc, argv, "hs:b:")) != -1){
        switch (c){
          case 'h':
            print_args();
            return -1;
          case 's':
            size_str = optarg;
            break;
          case 'b':
            brightness_option = optarg;
        }
    }
    Magick::InitializeMagick(*argv);
    std::string input_file(argv[optind]);
    Magick::Image input_img(input_file);
    input_img.resize(size_str);
    ImageProcesser img_proc = ImageProcesser(brightness_option);
    auto start = std::chrono::steady_clock::now();
    auto avg_pixels = img_proc.preprocess_image(input_img);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                        (std::chrono::steady_clock::now() - start);
    auto time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " ms to process input image" << std::endl;;

    start = std::chrono::steady_clock::now();
    construct_ascii_art(avg_pixels);
    duration = std::chrono::duration_cast<std::chrono::microseconds>
                        (std::chrono::steady_clock::now() - start);
    time_elapsed = duration.count();
    std::cout << "Took " << time_elapsed/1000.0 << " ms to construct image" << std::endl;;
}
