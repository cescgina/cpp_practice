#include <iostream>
#include "utilities.h"

void construct_ascii_art(const pixels_array& pixels){
    size_t width = pixels[0].size(), height = pixels.size();
    for (size_t i=0; i<height; i++){
        for (size_t j=0; j<width; j++){
            std::cout << pixel_to_ascii.at((int)(pixels[i][j]*(pixel_to_ascii.size()-1))) << " ";
        }
        std::cout << std::endl;
    }
}
