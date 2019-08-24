#include <string>
#include <iostream>
#include "Magick++.h"
#include "image_processing.h"

int main(int argc, char** argv){
    Magick::InitializeMagick(*argv);
    std::string input_path(argv[1]);
