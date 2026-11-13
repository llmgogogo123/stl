#include <cstdio>
#include "mini_vector.h"

struct Tracked {
    static int ctor, copy, move, dtor;
    int id;

    explicit Tracked(int i = 0) : id(i) { ++ctor; }
    Tracked(const Tracked& o) : id(o.id) { ++copy; }
    Tracked(Tracked&& o) noexcept : id(o.id) { ++move; }
    ~Tracked() { ++dtor; }
};

int Tracked::ctor = 0;
int Tracked::copy = 0;
int Tracked::move = 0;
int Tracked::dtor = 0;

int main() {
    {
        MiniVector<Tracked> v;
        for (int i = 0; i < 10; ++i) v.push_back(Tracked(i));
    }
    std::printf("ctor=%d copy=%d move=%d dtor=%d\n",
                Tracked::ctor, Tracked::copy, Tracked::move, Tracked::dtor);
}