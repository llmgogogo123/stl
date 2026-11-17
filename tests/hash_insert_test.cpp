#include "mini_unordered_map.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    MiniUnorderedMap<string, int> m;

    m["apple"] = 1;
    m["banana"] = 2;
    m["cat"] = 3;

    assert(m.size() == 3);
    assert(m.contains("apple"));
    assert(m.contains("banana"));
    assert(m.contains("cat"));
    assert(!m.contains("dog"));

    assert(m["apple"] == 1);
    assert(m["banana"] == 2);
    assert(m["cat"] == 3);

    m["apple"] = 10;          // 已存在，覆盖
    assert(m.size() == 3);    // 不应该变成 4
    assert(m["apple"] == 10);

    printf("insert OK: size=%zu buckets=%zu load=%.3f\n",
           m.size(), m.bucket_count(), m.load_factor());
}