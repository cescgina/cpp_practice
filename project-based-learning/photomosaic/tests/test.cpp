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
        auto result = preprocess_image(test_img, test_img.rows(), test_img.columns(), 1);
        std::vector<float> expected_array = {0.5333, 0.5255, 0.4941};
        EXPECT_THAT(result[0][0], testing::Pointwise(FloatNearPointwise(1e-8), expected_array));
    }
}

int main(int argc, char **argv) {
    Magick::InitializeMagick(*argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
