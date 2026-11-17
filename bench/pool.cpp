#include<chrono>
#include<cstdio>
#include<new>
#include<vector>
#include"fixed_pool.h"
using namespace std;
struct Node {
    int key;
    int value;
    Node* next;
};
int main(){
    const int N=1000000;
    vector<Node*> nodes(N);
    auto t0=std::chrono::steady_clock::now();
    for(int i=0;i<N;i++) nodes[i]=new Node{i,i,nullptr};
    for(int i=0;i<N;i++) delete nodes[i];
    auto t1=std::chrono::steady_clock::now();
    double newMs=std::chrono::duration<double,std::milli>(t1-t0).count();
    FixedPool pool(sizeof(Node));
    t0=std::chrono::steady_clock::now();
    for(int i=0;i<N;i++)
    nodes[i]=static_cast<Node*>(pool.allocate());
    for(int i=0;i<N;i++)
    pool.deallocate(nodes[i]);
    t1=std::chrono::steady_clock::now();
    double poolMs=std::chrono::duration<double,std::milli>(t1-t0).count();
    printf("new/delete: %.1f ms\npool    : %.1f ms\n",newMs,poolMs);
}