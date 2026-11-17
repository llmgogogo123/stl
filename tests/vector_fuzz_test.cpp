
#include "mini_vector.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;
static void check_same(const MiniVector<int>& a,const vector<int>& b,int step,int op){
    if(a.size()!=b.size()){
        printf("size mismatch at step=%d op=%d: %zu vs %zu\n",
               step, op, a.size(), b.size());
        abort();
    }
        for (size_t i = 0; i < b.size(); ++i) {
        if (a[i] != b[i]) {
            printf("value mismatch at step=%d op=%d index=%zu: %d vs %d\n",
                   step, op, i, a[i], b[i]);
            abort();
        }
    }
    if (a.capacity() < a.size() || b.capacity() < b.size()) {
        printf("capacity < size at step=%d op=%d\n", step, op);
        abort();
    }
}

int main() {
    MiniVector<int> mine;
    vector<int> ref;

    mt19937 rng(20261117);
    uniform_int_distribution<int> opDist(0, 6);
    uniform_int_distribution<int> valDist(-1000, 1000);
    uniform_int_distribution<size_t> sizeDist(0, 60);
    uniform_int_distribution<size_t> capDist(0, 256);
    uniform_int_distribution<size_t> idxDist(0, 1000);

    for (int step = 0; step < 100000; ++step) {
        int op = opDist(rng);

        if (op == 0) {
            int val = valDist(rng);
            mine.push_back(val);
            ref.push_back(val);
        } else if (op == 1) {
            if (!ref.empty()) {
                mine.pop_back();
                ref.pop_back();
            }
        } else if (op == 2) {
            size_t n = sizeDist(rng);
            mine.resize(n);
            ref.resize(n);
        } else if (op == 3) {
            size_t n = capDist(rng);
            mine.reserve(n);
            ref.reserve(n);
            if (mine.capacity() < n || ref.capacity() < n) {
                printf("reserve failed at step=%d: n=%zu, mine=%zu, ref=%zu\n",
                       step, n, mine.capacity(), ref.capacity());
                return 1;
            }
        } else if (op == 4) {
            if (!ref.empty()) {
                size_t i = idxDist(rng) % ref.size();
                int val = valDist(rng);
                mine[i] = val;
                ref[i] = val;
            }
        } else if (op == 5) {
            if (!ref.empty()) {
                size_t i = idxDist(rng) % ref.size();
                if (mine.at(i) != ref.at(i)) {
                    printf("at mismatch at step=%d index=%zu\n", step, i);
                    return 1;
                }
            }
        } else {
            mine.clear();
            ref.clear();
        }

        check_same(mine, ref, step, op);
    }

    bool threw = false;
    try {
        mine.at(mine.size());
    } catch (const out_of_range&) {
        threw = true;
    }
    if (!threw) {
        printf("at(size) did not throw\n");
        return 1;
    }

    printf("vector fuzz OK: 100000 ops, final size=%zu\n", ref.size());
    return 0;
}