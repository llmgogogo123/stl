#include <cassert>
#include <cstdio>
#include "mini_vector.h"

int main() {
    MiniVector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i);

    v.pop_back();
    assert(v.size() == 4 && v[3] == 3);

    v.resize(2);
    assert(v.size() == 2 && v[1] == 1);

    v.resize(5);
    assert(v.size() == 5);
    assert(v[2] == 0 && v[4] == 0);

    bool threw = false;
    try {
        v.at(5);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::size_t cap = v.capacity();
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == cap);

    std::puts("interface OK");
}