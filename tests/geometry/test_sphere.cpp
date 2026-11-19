#include <catch2/catch_test_macros.hpp>
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a ray through the centre of a sphere hits it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("a ray through the side of a sphere hits it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE(sphere.isHitBy(ray));
}

TEST_CASE("a ray that passes beside a sphere misses it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("a sphere behind the ray's origin is missed", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, Colour(1, 0, 0));
    REQUIRE_FALSE(sphere.isHitBy(ray));
}

TEST_CASE("a sphere gives back its colour", "[sphere]") {
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0.5, 0));
    requireColoursEqual(sphere.colour(), Colour(1, 0.5, 0));
}
