#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

namespace primitives3D {

struct Point {
  double x = NAN, y = NAN, z = NAN;

  void print() const { std::cout << "(" << x << " ; " << y << " ; " << z << ")"; }

  bool valid() const { return !(x!=x || y!=y || z!=z); }

  bool equal(const Point& rhs) const
  {
      assert(valid() && rhs.valid());
      return (std::abs(x - rhs.x)<std::numeric_limits<double>::epsilon()) &&
             (std::abs(y - rhs.y)<std::numeric_limits<double>::epsilon()) &&
             (std::abs(z - rhs.z)<std::numeric_limits<double>::epsilon());
  }
};

struct Vec3 {
    double x, y, z;

    // Constructors
    Vec3() : x(0), y(0), z(0) {}               // Default constructor
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {} // Parameterized constructor

    // Basic vector operations
    Vec3 operator+(const Vec3& other) const {  // Vector addition
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const {  // Vector subtraction
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(double scalar) const {       
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(double scalar) const {       
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    // Dot product
    double dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3 cross(const Vec3& other) const {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        double mag = norm();
        return Vec3(x / mag, y / mag, z / mag);
    }

    // Equality check
    bool operator==(const Vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vec3& other) const {
        return !(*this == other);
    }

    // Utility function to display the vector
    void display() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    }
};

enum class PlaneRelPosition 
{
    UPSIDE,
    DOWNSIDE,
};

struct Plane
{
    
    Vec3 normVec_;
    Vec3 planePoint_;

    Plane(const Vec3& normVec, const Vec3& point): normVec_(normVec), planePoint_(point) {};

    PlaneRelPosition pointPosition(const Vec3& point) const {
        const auto res = (point - planePoint_).dot(normVec_);
        return res > 0 ? PlaneRelPosition::UPSIDE : PlaneRelPosition::DOWNSIDE;
    }

};


}
