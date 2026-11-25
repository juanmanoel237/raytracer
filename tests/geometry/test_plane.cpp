#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <optional>
#include "colour/colour.h"
#include "geometry/hit.h"
#include "geometry/plane.h"
#include "geometry/ray.h"
#include "material/material.h"
#include "math/vector.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

// The floor and the line 3x + 4y = 24 of the domain model, in 3D, with z = 0.
TEST_CASE("a ray going down hits the floor", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(3, -4, 0));
    std::optional<Hit> hit = floor.hit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(6, 0, 0));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
    requireColoursEqual(hit->material.colour(), Colour(0, 1, 0));
}

TEST_CASE("a plane gives a unit normal, even when it was made with a longer one", "[plane]") {
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(-8, 0, 0), Vector(4, 3, 0));
    std::optional<Hit> hit = plane.hit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 6, 0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0));
}

TEST_CASE("a ray parallel to a plane misses it", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(5, 0, 0));
    REQUIRE_FALSE(floor.hit(ray).has_value());
}

TEST_CASE("a plane behind the ray's origin is missed", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), Material(Colour(0, 1, 0)));
    Ray ray(Vector(0, 8, 0), Vector(3, 4, 0));
    REQUIRE_FALSE(floor.hit(ray).has_value());
}
