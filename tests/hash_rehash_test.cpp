#include "mini_unordered_map.h"
#include <cassert>
#include <cstdio>

int main() {
    MiniUnorderedMap<int, int> m;

    for (int i = 0; i < 100; ++i) {
        m[i] = i * 2;
    }

    assert(m.size() == 100);

    for (int i = 0; i < 100; ++i) {
        assert(m[i] == i * 2);
    }

    printf("rehash OK: size=%zu buckets=%zu load=%.3f\n",
           m.size(), m.bucket_count(), m.load_factor());
}