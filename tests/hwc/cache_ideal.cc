#include <cassert>
#include <iostream>

#include "../../src/CppBaseCourse/hwc/Ideal.h"

// slow get page imitation
int slow_get_page_int(int key) { return key; }

int main() {
    int hits = 0;
    int n;
    size_t m;

    std::cin >> m >> n;
    assert(std::cin.good());
    caches::cache_ideal<int> c{m};

    std::vector<int> input;
    input.reserve(n);

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        input.push_back(q);
    }

    for (int i = 0; i < n; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int, input, i))
            hits += 1;
    }
    std::cout << hits << std::endl;
}

