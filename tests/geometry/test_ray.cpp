#include <catch2/catch_test_macros.hpp>
#include "geometry/ray.h"
#include "math/vector.h"
#include "test_helpers.h"

TEST_CASE("a ray gives back its origin and direction", "[ray]") {
    Ray ray(Vector(1, 2, 3), Vector(3, 4, 0));
    requireVectorsEqual(ray.origin(), Vector(1, 2, 3));
    requireVectorsEqual(ray.direction(), Vector(3, 4, 0));
}

TEST_CASE("a ray at t is origin + t times direction", "[ray]") {
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));
    requireVectorsEqual(ray.at(0), Vector(0, 8, 0));
    requireVectorsEqual(ray.at(2), Vector(6, 0, 0));
}
