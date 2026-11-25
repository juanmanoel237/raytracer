#include <catch2/catch_test_macros.hpp>
#include "colour/colour.h"
#include "material/material.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a surface facing the light gets its whole colour", "[material]") {
    Material material(Colour(1, 0.5, 0));
    Colour colour = material.shade(Vector(0, 0, -1), Vector(0, 0, -1));
    requireColoursEqual(colour, Colour(1, 0.5, 0));
}

TEST_CASE("a surface lit at an angle gets the cosine of that angle", "[material]") {
    Material material(Colour(1, 0.5, 0));
    Colour colour = material.shade(Vector(0, 0, -1), Vector(0.6, 0, -0.8));
    requireColoursEqual(colour, Colour(0.8, 0.4, 0));
}

TEST_CASE("a surface the light grazes is black", "[material]") {
    Material material(Colour(1, 0.5, 0));
    Colour colour = material.shade(Vector(0, 0, -1), Vector(1, 0, 0));
    requireColoursEqual(colour, Colour(0, 0, 0));
}

TEST_CASE("a surface facing away from the light is black, not negative", "[material]") {
    Material material(Colour(1, 0.5, 0));
    Colour colour = material.shade(Vector(0, 0, -1), Vector(0, 0, 1));
    requireColoursEqual(colour, Colour(0, 0, 0));
}
