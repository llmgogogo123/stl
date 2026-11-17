#include "mini_unordered_map.h"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>
#include<map>
using namespace std;

using Clock = chrono::steady_clock;

static double ms(Clock::duration d) {
    return chrono::duration<double, milli>(d).count();
}

template <typename Map>
void bench(const char* name, const vector<int>& keys) {
    Map m;
    long long sum = 0;

    auto t0 = Clock::now();
    for (int k : keys) m[k] = k;
    auto t1 = Clock::now();

    for (int k : keys) sum += m.at(k);
    auto t2 = Clock::now();

    for (int k : keys) m.erase(k);
    auto t3 = Clock::now();

    printf("%-20s %10.1f %10.1f %10.1f   (sum=%lld, size=%zu)\n",
           name, ms(t1 - t0), ms(t2 - t1), ms(t3 - t2),
           sum, m.size());
}

int main() {
    const int N = 1000000;

    vector<int> keys(N);
    iota(keys.begin(), keys.end(), 0);

    mt19937 rng(12345);
    shuffle(keys.begin(), keys.end(), rng);

    printf("%-20s %10s %10s %10s\n",
           "container", "insert_ms", "find_ms", "erase_ms");

    bench<unordered_map<int, int>>("std::unordered_map", keys);
    bench<MiniUnorderedMap<int, int>>("MiniUnorderedMap", keys);
    bench<std::map<int,int>>("std::map",keys);
}