#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "math/vector.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("a + b adds each component", "[vector]") {
    requireVectorsEqual(Vector(3, 4, 0) + Vector(4, -3, 0), Vector(7, 1, 0));
    requireVectorsEqual(Vector(3, 4, 1) + Vector(4, -3, 2), Vector(7, 1, 3));
}

TEST_CASE("a - b subtracts each component", "[vector]") {
    requireVectorsEqual(Vector(4, 5, 0) - Vector(1, 1, 0), Vector(3, 4, 0));
    requireVectorsEqual(Vector(4, 5, 6) - Vector(1, 1, 2), Vector(3, 4, 4));
}

TEST_CASE("t * v scales each component", "[vector]") {
    requireVectorsEqual(2.0 * Vector(3, -4, 1), Vector(6, -8, 2));
}

TEST_CASE("O + t * D gives the point on the ray at t", "[vector]") {
    Vector O(0, 8, 0);
    Vector D(3, -4, 0);
    double t = 2;
    requireVectorsEqual(O + t * D, Vector(6, 0, 0));
}

TEST_CASE("dot multiplies in pairs, then adds", "[vector]") {
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, 3, 0)) == 24);
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, -3, 0)) == 0);
    REQUIRE(Vector(3, 4, 12).dot(Vector(4, 3, 1)) == 36);
}

TEST_CASE("length follows Pythagoras", "[vector]") {
    REQUIRE(Vector(3, -4, 0).length() == 5);
    REQUIRE(Vector(3, 4, 12).length() == 13);
}

TEST_CASE("normalised keeps the direction and gives length 1", "[vector]") {
    requireVectorsEqual(Vector(3, -4, 0).normalised(), Vector(0.6, -0.8, 0));
    REQUIRE_THAT(Vector(3, 4, 12).normalised().length(), WithinAbs(1, tolerance));
}
