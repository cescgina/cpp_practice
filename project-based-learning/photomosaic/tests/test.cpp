#include <vector>
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
    TEST(DintanceTests, Distance){
        // using randomly generated data
        std::vector<float> arr1 = {0.95, 0.474, 0.72};
        std::vector<float> arr2 = {0.859, 0.252, 0.848};
        std::vector<float> arr3 = {1.0, 2.0, 1.0};
        std::vector<float> arr4 = {3.0, 4.0, 0.0};
        EXPECT_FLOAT_EQ(calculate_distance(arr3, arr4), 3.0);
        EXPECT_FLOAT_EQ(calculate_distance(arr1, arr2), 0.271935654);
    }
    TEST(ImageTests, preprocess){
        Magick::Image test_img("tests/test_img_avg.jpg");
        float res = 0.1;
        auto result = preprocess_image(test_img, test_img.rows(), test_img.columns(), 1);
        std::vector<float> expected_array = {0.5333, 0.5255, 0.4941};
        EXPECT_THAT(result[0][0], testing::Pointwise(FloatNearPointwise(res), expected_array));
        result = preprocess_image(test_img, test_img.rows(), test_img.columns(), 4);
        expected_array = {0.592, 0.573, 0.557, 0.565, 0.565, 0.541, 0.427, 0.435, 0.424, 0.502, 0.463, 0.396};
        EXPECT_THAT(result[0][0], testing::Pointwise(FloatNearPointwise(res), expected_array));
        result = preprocess_image(test_img, test_img.rows(), test_img.columns(), 16);
        expected_array = {0.682, 0.671, 0.663, 0.694, 0.753, 0.749, 0.553, 0.616, 0.62, 0.604, 0.675, 0.69, 0.663, 0.643, 0.624, 0.588, 0.478, 0.455, 0.447, 0.392, 0.325, 0.757, 0.741, 0.69, 0.4, 0.443, 0.463, 0.314, 0.302, 0.278, 0.353, 0.302, 0.227, 0.522, 0.471, 0.404, 0.565, 0.6, 0.588, 0.459, 0.502, 0.502, 0.435, 0.416, 0.361, 0.69, 0.667, 0.6};
        EXPECT_THAT(result[0][0], testing::Pointwise(FloatNearPointwise(res), expected_array));
    }
}

int main(int argc, char **argv) {
    Magick::InitializeMagick(*argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
