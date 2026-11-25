#include <catch2/catch_test_macros.hpp>
#include "colour/colour.h"
#include "test_helpers.h"

// Compares with plain numbers, not requireColoursEqual:
// this test checks r(), g() and b() themselves.
TEST_CASE("a colour gives back its r, g and b", "[colour]") {
    Colour colour(1, 0.5, 0);
    REQUIRE(colour.r() == 1);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0);
}

TEST_CASE("a number times a colour scales r, g and b", "[colour]") {
    requireColoursEqual(0.5 * Colour(1, 0.5, 0), Colour(0.5, 0.25, 0));
}
