#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "colour/colour.h"
#include "image/image.h"
#include "lodepng.h"
#include "output/png_saver.h"

TEST_CASE("a PNG file holds the pixels row by row, from the top", "[png]") {
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1, 0.5, 0));

    PngSaver saver;
    saver.save(image, "test_png_saver.png");

    std::vector<unsigned char> bytes;
    unsigned width = 0;
    unsigned height = 0;
    unsigned error = lodepng::decode(bytes, width, height, "test_png_saver.png", LCT_RGB);

    REQUIRE(error == 0);
    REQUIRE(width == 2);
    REQUIRE(height == 2);

    std::vector<int> actual(bytes.begin(), bytes.end());
    std::vector<int> expected = {0, 0, 0, 255, 128, 0, 0, 0, 0, 0, 0, 0};
    REQUIRE(actual == expected);
}
