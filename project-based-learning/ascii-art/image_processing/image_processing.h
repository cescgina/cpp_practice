#include "utilities.h"
#include <Magick++.h>

class ImageProcesser{
    private:
        std::string brightness_mode;
        float conversion_factor;
        float average_brightness(const Magick::PixelPacket& pixel);
        float lightness(const Magick::PixelPacket& pixel);
        float luminosity(const Magick::PixelPacket& pixel);
        float calculate_brightness(const Magick::PixelPacket& pixel);
    public:
        ImageProcesser(std::string brightness_mode_str);
        pixels_array preprocess_image(const Magick::Image & image);
};
