#include<cstdio>
#include"mini_vector.h"
using namespace std;
int main(){
    MiniVector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
        printf("size=%zu cap=%zu\n",v.size(),v.capacity());
    }
    return 0;
}