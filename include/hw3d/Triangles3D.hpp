#pragma once

#include "Primitives3D.hpp"
#include <optional>
#include <array>

namespace triangles3D {

using namespace primitives3D;


class Triangle3D {

    std::array<Vec3, 3> points_;

public:

    Triangle3D() {};

    Triangle3D(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3): points_{vec1, vec2, vec3} {};

    std::array<Vec3, 2> getTwoOtherPoints(size_t num) const;

    Plane constructPlane(size_t thirdPoint) const;

    friend  std::istream &operator >> (std::istream &in, Triangle3D& triangle);

    bool is_intersect(const Triangle3D& otherTriangle);

    size_t countIntersections(const std::vector<Triangle3D>& triangles);

};

}
