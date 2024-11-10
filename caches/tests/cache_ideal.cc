#include <cassert>
#include <iostream>
#include <span>
#include "Ideal.h"

// slow get page imitation
int slow_get_page_int(int key) { return key; }

int main() {
    int hits = 0;
    int n;
    size_t m;

    std::cin >> m >> n;
    assert(std::cin.good());

    std::vector<int> input;
    input.reserve(n);

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        input.push_back(q);
    }
    caches::cache_ideal c(m);
    hits = c.lookup_update(input);

    std::cout << hits << std::endl;
}

