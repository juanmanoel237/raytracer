#include <catch2/catch_test_macros.hpp>
#include "colour/colour.h"
#include "image/image.h"
#include "test_helpers.h"

TEST_CASE("an image has the width and height it was made with", "[image]") {
    Image image(5, 3);
    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("a new image is black everywhere", "[image]") {
    Image image(5, 3);
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
        }
    }
}

TEST_CASE("setting a pixel changes that pixel only", "[image]") {
    Image image(5, 3);
    image.setPixel(4, 0, Colour(1, 0, 0));
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            if (column == 4 && row == 0) {
                requireColoursEqual(image.pixel(column, row), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
            }
        }
    }
}
