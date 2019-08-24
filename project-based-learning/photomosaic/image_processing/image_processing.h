#include <Magick++.h>

typedef std::vector<std::vector<std::vector<float>>> pixels_array;

std::pair<int, int> calculate_resolutions(int original_res, int rows, int cols);
pixels_array preprocess_image(Magick::Image & image, size_t res_x, size_t res_y);
void paint_image(pixels_array& pixels, Magick::Image& img, size_t res_x, size_t res_y);
