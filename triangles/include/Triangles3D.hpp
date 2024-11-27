#pragma once

#include "Primitives3D.hpp"
#include <array>
#include <set>

namespace triangles3D {

using Vec3 = primitives3D::Vec3;
using Plane = primitives3D::Plane;


class Triangle3D {
public:

    Triangle3D() = default;

    Triangle3D(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3): points_{vec1, vec2, vec3} {};

    [[nodiscard]] std::array<Vec3, 2> getTwoOtherPoints(size_t num) const;

    [[nodiscard]] bool is_intersect(const Triangle3D& otherTriangle) const;

    Plane toPlane(const size_t point_ind) const;

    void setPoint(size_t ind, const Vec3& val);

    friend std::istream &operator >> (std::istream &in, Triangle3D& triangle){
        in >> triangle.points_[0] >> triangle.points_[1] >> triangle.points_[2];
        return in;
    };

private:

    Plane constructPlane(size_t thirdPointInd) const;

private:

    std::array<Vec3, 3> points_;

};

std::set<size_t> getIntersectTriangles(const std::vector<Triangle3D>& triangles);

}
