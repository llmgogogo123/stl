#include "mini_unordered_map.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    MiniUnorderedMap<string, int> m;

    assert(m.size() == 0);
    assert(m.empty());
    assert(m.bucket_count() == 8);
    assert(!m.contains("apple"));

    printf("hash smoke OK: size=%zu buckets=%zu load=%.3f\n",
           m.size(), m.bucket_count(), m.load_factor());
}