#include<iostream>
#include<cassert>
#include "hw3d/Triangles3D.hpp"

namespace {

using namespace triangles3D;

int main()
{
    // write from file, check with result
    Triangle3D tr1;
    Triangle3D tr2;
    std::cin >> tr1 >> tr2;
    assert (std::cin.good());

    bool result = tr1.is_intersect(tr2);

    std::cout << result << std::endl;
}

}