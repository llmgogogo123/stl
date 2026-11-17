#include <cassert>
#include <cstdio>
#include <utility>
#include "mini_vector.h"
int main(){
    MiniVector<int> a;
    for(int i=0;i<5;i++) a.push_back(i);
    MiniVector<int> b=a;
    assert(b.size()==5);
    assert(b.data()!=a.data());
    b[0]=99;
    assert(a[0]==0 && b[0]==99);
    MiniVector<int> c;
    c=a;
    b=b;
    assert(b.size()==5&&b[0]==99);
    MiniVector<int> d=std::move(a);
    assert(d.size()==5&&d[0]==0);
    assert(a.size()==0&&a.data()==nullptr);
    c=std::move(d);
        assert(c.size() == 5 && c[0] == 0);
    assert(d.size() == 0 && d.data() == nullptr);
    c = c;
    assert(c.size() == 5);
    MiniVector<int> r;
    r.reserve(8);
    assert(r.capacity() >= 8 && r.size() == 0);
    std::puts("copy/move OK");
    return 0;
}