#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <optional>
#include "colour/colour.h"
#include "geometry/hit.h"
#include "geometry/ray.h"
#include "geometry/sphere.h"
#include "material/material.h"
#include "math/vector.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("a ray through the centre of a sphere hits it head on", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 9), 5, Material(Colour(1, 0, 0)));
    std::optional<Hit> hit = sphere.hit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
    requireColoursEqual(hit->material.colour(), Colour(1, 0, 0));
}

TEST_CASE("a ray through the side of a sphere hits it at an angle", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(3, 0, 9), 5, Material(Colour(1, 0, 0)));
    std::optional<Hit> hit = sphere.hit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

TEST_CASE("a ray that starts inside a sphere hits it on the far side", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, 1), 5, Material(Colour(1, 0, 0)));
    std::optional<Hit> hit = sphere.hit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(7, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 6));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}

TEST_CASE("a ray that passes beside a sphere misses it", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(6, 0, 9), 5, Material(Colour(1, 0, 0)));
    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("a sphere behind the ray's origin is missed", "[sphere]") {
    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));
    Sphere sphere(Vector(0, 0, -11), 5, Material(Colour(1, 0, 0)));
    REQUIRE_FALSE(sphere.hit(ray).has_value());
}
