#include <vector>
#include <exception>
#include "Magick++.h"
#include "utilities.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "image_processing.h"

// taken from https://stackoverflow.com/questions/28768359/comparison-of-floating-point-arrays-using-google-test-and-google-mock
MATCHER_P(FloatNearPointwise, tol, "Out of range") {
    return (std::get<0>(arg)>std::get<1>(arg)-tol && std::get<0>(arg)<std::get<1>(arg)+tol);
}

namespace {
    TEST(ImageTests, avg_brightness){
        // RGB values (0.0509804, 0.443137, 0.105882), (0, 0.0745098, 0), (0.933333, 1, 0.917647), (0.972549, 0.980392, 0.937255)
        Magick::Image test_img("tests/test_img_4_pixels.jpg");
        float res = 0.000001;
        ImageProcesser img_proc = ImageProcesser("average");
        auto avg_pixels = img_proc.preprocess_image(test_img);
        pixels_array expected_array = {{0.1999998, 0.0248366}, {0.9503267, 0.963399}};
        for (std::size_t i=0; i < avg_pixels.size(); i++){
            EXPECT_THAT(avg_pixels[i], testing::Pointwise(FloatNearPointwise(res), expected_array[i]));
        }
    }
    TEST(ImageTests, lightness){
        Magick::Image test_img("tests/test_img_4_pixels.jpg");
        float res = 0.000001;
        ImageProcesser img_proc = ImageProcesser("lightness");
        auto avg_pixels = img_proc.preprocess_image(test_img);
        pixels_array expected_array = {{0.2470587, 0.0372548}, {0.9588235, 0.9588235}};
        for (std::size_t i=0; i < avg_pixels.size(); i++){
            EXPECT_THAT(avg_pixels[i], testing::Pointwise(FloatNearPointwise(res), expected_array[i]));
        }
    }
    TEST(ImageTests, luminosity){
        Magick::Image test_img("tests/test_img_4_pixels.jpg");
        float res = 0.000001;
        ImageProcesser img_proc = ImageProcesser("luminosity");
        auto avg_pixels = img_proc.preprocess_image(test_img);
        pixels_array expected_array = {{0.33717626, 0.05364706}, {0.98023522, 0.97572538}};
        for (std::size_t i=0; i < avg_pixels.size(); i++){
            EXPECT_THAT(avg_pixels[i], testing::Pointwise(FloatNearPointwise(res), expected_array[i]));
        }
    }
    TEST(ImageTests, inexisting){
        Magick::Image test_img("tests/test_img_4_pixels.jpg");
        EXPECT_THROW(ImageProcesser("inexisting"), std::invalid_argument);
    }
}

int main(int argc, char **argv) {
    Magick::InitializeMagick(*argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
