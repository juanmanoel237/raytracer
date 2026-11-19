#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "math/vector.h"
#include "render/camera.h"
#include "test_helpers.h"

// The spike's tests: the one pixel of a 1 by 1 image is the centre of the screen.
TEST_CASE("in a 1 by 1 image, the ray goes from the eye to the screen centre", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);
    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("in a 1 by 1 image, the ray has direction screen centre - eye", "[camera]") {
    Camera camera(Vector(1, 2, -1), Vector(4, 6, -1), 2);
    Ray ray = camera.rayThroughPixel(0, 0, 1, 1);
    requireVectorsEqual(ray.origin(), Vector(1, 2, -1));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}

// 5 by 3 grid, on a screen 5 wide: one pixel is 1 across.
TEST_CASE("the centre pixel's ray goes straight ahead", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);
    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
}

TEST_CASE("the top-right pixel's ray goes right and up", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);
    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(2, 1, 1));
}

TEST_CASE("the bottom-left pixel's ray goes left and down", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);
    requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
    requireVectorsEqual(ray.direction(), Vector(-2, -1, 1));
}

TEST_CASE("render gives an image of the size asked for", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Sphere sphere(Vector(0, 0, 6), 5, Colour(1, 0, 0));
    Image image = camera.render(sphere, 5, 3);
    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("render colours the pixels whose ray hits the sphere: a plus", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Sphere sphere(Vector(0, 0, 6), 5, Colour(1, 0, 0));
    Image image = camera.render(sphere, 5, 3);

    std::vector<std::string> expected = {
        "..#..",
        ".###.",
        "..#..",
    };

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            if (expected[row][column] == '#') {
                requireColoursEqual(image.pixel(column, row), Colour(1, 0, 0));
            } else {
                requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
            }
        }
    }
}
