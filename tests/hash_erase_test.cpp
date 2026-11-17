#include "mini_unordered_map.h"
#include <cassert>
#include <cstdio>
#include <stdexcept>
using namespace std;

int main() {
    MiniUnorderedMap<int, int> m;

    for (int i = 0; i < 10; ++i) {
        m[i] = i * 10;
    }

    assert(m.size() == 10);
    assert(m.at(3) == 30);

    // at 找不到要抛异常
    bool threw = false;
    try {
        m.at(999);
    } catch (const out_of_range&) {
        threw = true;
    }
    assert(threw);

    // 删中间
    assert(m.erase(3));
    assert(!m.contains(3));
    assert(m.size() == 9);

    // 删不存在的
    assert(!m.erase(999));
    assert(m.size() == 9);

    // 删头、删尾
    assert(m.erase(0));
    assert(m.erase(9));
    assert(m.size() == 7);

    // 清空
    m.clear();
    assert(m.empty());
    assert(m.bucket_count() == 16);   // 10 个元素时扩到 16，clear 不缩

    printf("erase/at/clear OK: size=%zu buckets=%zu\n",
           m.size(), m.bucket_count());
}