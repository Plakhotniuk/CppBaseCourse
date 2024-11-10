#pragma once

#include "Primitives3D.hpp"
#include <array>

namespace triangles3D {

using Vec3 = primitives3D::Vec3;
using Plane = primitives3D::Plane;


class Triangle3D {

    std::array<Vec3, 3> points_;

public:

    Triangle3D() {};

    Triangle3D(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3): points_{vec1, vec2, vec3} {};

    std::array<Vec3, 2> getTwoOtherPoints(size_t num) const;

    Plane constructPlane(size_t thirdPoint) const;

    bool is_intersect(const Triangle3D& otherTriangle) const;

    size_t countIntersections(const std::vector<Triangle3D>& triangles) const;

};

}
