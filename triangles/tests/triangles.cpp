#include <cassert>
#include <iostream>
#include <Triangles3D.hpp>


using namespace triangles3D;

int main()
{
    Triangle3D tr1;
    Triangle3D tr2;
    std::cin >> tr1 >> tr2;
    assert (std::cin.good());

    bool result = tr1.is_intersect(tr2);
    std::cout << result << std::endl;
}
