#include "geometry/sphere.h"
#include <cmath>

Sphere::Sphere(const Vector& centre, double radius, const Material& material)
    : _centre(centre), _radius(radius), _material(material) {}

std::optional<Hit> Sphere::hit(const Ray& ray) const {
    Vector O = ray.origin();
    Vector D = ray.direction();
    Vector L = O - _centre;
    double a = D.dot(D);
    double b = 2.0 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return std::nullopt;
    }
    double root = std::sqrt(discriminant);
    double t1 = (-b - root) / (2.0 * a);
    double t2 = (-b + root) / (2.0 * a);
    double t;
    if (t1 > 0.0) {
        t = t1;
    } else if (t2 > 0.0) {
        t = t2;
    } else {
        return std::nullopt;
    }
    Vector point = ray.at(t);
    Vector normal = (1.0 / _radius) * (point - _centre);
    return Hit{t, point, normal, _material};
}
