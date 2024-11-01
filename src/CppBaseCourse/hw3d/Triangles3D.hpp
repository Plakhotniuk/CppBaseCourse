#pragma once

#include "Primitives3D.hpp"
#include <optional>
#include <array>

namespace triangles3D {

using namespace primitives3D;


struct Triangle3D {

  std::array<Vec3, 3> points_;

  Triangle3D(const Vec3& vec1, const Vec3& vec2, const Vec3& vec3): points_{vec1, vec2, vec3} {};

  std::array<Vec3, 2> getTwoOtherPoints(size_t num) const {
    return {points_[(num + 1) % 3], points_[(num + 2) % 3]};
  }

  Plane constructPlane(size_t thirdPoint) const {
    const Vec3 A = points_[(thirdPoint + 1) % 3];
    const Vec3 B = points_[(thirdPoint + 2) % 3];
    const Vec3 C = points_[thirdPoint];
    const Vec3 AB = B - A;
    const Vec3 AC = C - A;
    const Vec3 AH = AB.normalize() * AB.dot(AC) / AB.norm();
    Vec3 planeNormVec = (AC - AH).normalize();

    return Plane(planeNormVec, A);
  }

};

bool is_intersect(const Triangle3D& triangle1, const Triangle3D& triangle2) {
  // for point in thisTriangle.points
  for(size_t i = 0; i < 3; ++i) 
  {
    const Plane plane = triangle1.constructPlane(i);
    const PlaneRelPosition thisPointPos = plane.pointPosition(triangle1.points_[i]);

    // for otherPoint in otherTriangle.points
    bool hasPointInHalfSpace = false;
    for(size_t j = 0; j < 3; ++j)
    {
      const PlaneRelPosition otherPointPos = plane.pointPosition(triangle2.points_[j]);
      if(otherPointPos == thisPointPos)
      {
        hasPointInHalfSpace = true;
        break;
      }
    }
    if(!hasPointInHalfSpace) return false;
  }
  return true;
}

size_t countIntersections(const std::vector<Triangle3D>& triangles)
{
  size_t counter = 0;
  const size_t vecSize = triangles.size();
  for(size_t i = 0; i < vecSize - 1; ++i)
  {
    for(size_t j = i + 1; j < vecSize; ++j)
    {
      if(is_intersect(triangles[i], triangles[j])) ++counter;
    }
  }
  return counter;
}


}

