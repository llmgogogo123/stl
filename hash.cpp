#include<cstdio>
#include<functional>
#include<string>
using namespace std;
int main(){
    printf("hash(42)=%zu\n",hash<int>{}(42));
    printf("hash(apple)=%zu\n",hash<string>{}("apple"));
    printf("hash(apple %% 8=%zu\n)",hash<string>{}("apple")%8);
}