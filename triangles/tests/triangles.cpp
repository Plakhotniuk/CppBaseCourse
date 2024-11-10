#include <cassert>
#include <iostream>
#include <Triangles3D.hpp>


using namespace triangles3D;

int main()
{
    // write from file, check with result
    const Triangle3D tr1{{1, 1, 2}, {1, 1, 2}, {2, 2, 2}};
    const Triangle3D tr2{{1, 1, 1}, {1, 5, 1}, {5, 1, 1}};

    bool result = tr1.is_intersect(tr2);

    std::cout << result << std::endl;
    std::cout << "result" << std::endl;
}
