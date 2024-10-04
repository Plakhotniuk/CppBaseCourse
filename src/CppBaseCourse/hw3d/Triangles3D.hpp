#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

namespace triangles_3d {

struct point_t {
  double x = NAN, y = NAN, z = NAN;

  void print() const { std::cout << "(" << x << " ; " << y << " ; " << z << ")"; }

  bool valid() const { return !(x!=x || y!=y || z!=z); }

  bool equal(const point_t& rhs) const
  {
      assert(valid() && rhs.valid());
      return (std::abs(x - rhs.x)<std::numeric_limits<double>::epsilon()) &&
             (std::abs(y - rhs.y)<std::numeric_limits<double>::epsilon()) &&
             (std::abs(z - rhs.z)<std::numeric_limits<double>::epsilon());
  }
};

struct line_t{
  point_t p1, p2;

};


}

