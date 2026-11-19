#include <catch2/catch_test_macros.hpp>
#include "colour/colour.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "math/vector.h"
#include "render/trace.h"
#include "test_helpers.h"

TEST_CASE("trace gives the sphere's colour when the ray hits it", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));
    requireColoursEqual(trace(ray, sphere), Colour(1, 0, 0));
}

TEST_CASE("trace gives black when the ray misses the sphere", "[trace]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Colour(1, 0, 0));
    requireColoursEqual(trace(ray, sphere), Colour(0, 0, 0));
}
