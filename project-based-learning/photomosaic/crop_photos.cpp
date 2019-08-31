#include <list>
#include <string>
#include <iostream>
#include "Magick++.h"
#include "utilities.h"
#include "image_processing.h"

int main(int argc, char** argv){
    Magick::InitializeMagick(*argv);
    std::string input_path(argv[1]);
    std::string output_path = input_path + "_cropped";
    create_folder(output_path);
    std::list<std::string> photos = get_list_photos(input_path);
    for (std::list<std::string>::iterator i=photos.begin(); i!=photos.end(); i++){
        Magick::Image input_img;
        try{
            input_img.read(*i);
            std::string file_name = get_filename(*i);
            crop_photo(input_img, output_path, file_name);    
        }
        catch (Magick::ErrorCorruptImage& my_error) { 
            std::cout << "a Magick++ error occurred: " << my_error.what() << std::endl;
        }
    }
}
