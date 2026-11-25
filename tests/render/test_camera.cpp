#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <string>
#include <vector>
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "material/material.h"
#include "math/vector.h"
#include "render/camera.h"
#include "scene/scene.h"
#include "test_helpers.h"

// The one pixel of a 1 by 1 image is the centre of the screen.
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

// A grid 5 wide and 3 high, on a screen 5 wide: one pixel is 1 across.
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
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, Material(Colour(1, 0, 0))));
    Image image = camera.render(scene, 5, 3);
    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

// The sun is behind the eye. 'O' faces it, and '#' is at the 3-4-5 angle: a cosine of 0.8.
TEST_CASE("render shades the pixels whose ray hits the sphere: a plus", "[camera]") {
    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, Material(Colour(1, 0, 0))));
    Image image = camera.render(scene, 5, 3);

    std::vector<std::string> expected = {
        "..#..",
        ".#O#.",
        "..#..",
    };

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 5; column++) {
            if (expected[row][column] == 'O') {
                requireColoursEqual(image.pixel(column, row), Colour(1, 0, 0));
            } else if (expected[row][column] == '#') {
                requireColoursEqual(image.pixel(column, row), Colour(0.8, 0, 0));
            } else {
                requireColoursEqual(image.pixel(column, row), Colour(0, 0, 0));
            }
        }
    }
}
