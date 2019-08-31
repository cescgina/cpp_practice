#include <unordered_map>
#include <Magick++.h>
#include "utilities.h"

typedef std::vector<std::vector<std::vector<float>>> pixels_array;

pixels_array preprocess_image(Magick::Image & image, size_t res_x, size_t res_y);
void paint_image(pixels_array& pixels, Magick::Image& img, size_t res_x, size_t res_y);
void crop_photo(Magick::Image & image, std::string& output_folder, std::string& image_name);
void construct_image_from_files(Magick::Image& image, files_array& files, size_t res_x, size_t res_y);
