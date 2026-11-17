#include "mini_unordered_map.h"
#include <cassert>
#include <cstdio>
#include <random>
#include <unordered_map>
using namespace std;

int main() {
    MiniUnorderedMap<int, int> mine;
    unordered_map<int, int> ref;

    mt19937 rng(12345);
    uniform_int_distribution<int> keyDist(0, 999);
    uniform_int_distribution<int> valDist(0, 1000000);
    uniform_int_distribution<int> opDist(0, 3);

    for (int step = 0; step < 100000; ++step) {
        int key = keyDist(rng);
        int op = opDist(rng);

        if (op == 0) {
            // 插入或覆盖
            int val = valDist(rng);
            mine[key] = val;
            ref[key] = val;
        } else if (op == 1) {
            // 删除
            bool a = mine.erase(key);
            bool b = ref.erase(key) > 0;
            assert(a == b);
        } else if (op == 2) {
            // 查询是否存在
            assert(mine.contains(key) == (ref.find(key) != ref.end()));
        } else {
            // 查询值
            auto it = ref.find(key);
            if (it != ref.end()) {
                assert(mine.contains(key));
                assert(mine.at(key) == it->second);
            } else {
                assert(!mine.contains(key));
            }
        }

        // 每一步都比元素个数
        assert(mine.size() == ref.size());
    }

    // 最后把 ref 里每个 key 再对一遍
    for (const auto& kv : ref) {
        assert(mine.contains(kv.first));
        assert(mine.at(kv.first) == kv.second);
    }

    printf("fuzz OK: 100000 ops, final size=%zu\n", mine.size());
}