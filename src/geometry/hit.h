#pragma once
#include "material/material.h"
#include "math/vector.h"

// Where a ray meets a surface: how far along the ray, the point, the unit normal there, and the material.
struct Hit {
    double t;
    Vector point;
    Vector normal;
    Material material;
};
