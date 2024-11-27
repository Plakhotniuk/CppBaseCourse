#include <cassert>
#include <iostream>
#include <Triangles3D.hpp>


using namespace triangles3D;

int main()
{
    Triangle3D tr;

    size_t num_of_tr;

    std::cin >> num_of_tr;

    std::vector<Triangle3D> tr_vec;
    tr_vec.reserve(num_of_tr);

    for(size_t i = 0; i < num_of_tr; ++i)
    {
        std::cin >> tr;
        assert (std::cin.good());
        tr_vec.emplace_back(tr);
    }

    const auto result = getIntersectTriangles(tr_vec);
    for (const auto& elem : result)
        std::cout << elem << ' ';
}