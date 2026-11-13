#include<cstdio>
#include<string>
#include<new>
using namespace std;
int main(){
    void*raw = :: operator new(sizeof(string)*2);
    string* p=static_cast<string*>(raw);
    new(p+0) string("hello");
    new(p+1) string("world");
    printf("%s %s\n",p[0].c_str(),p[1].c_str());
    p[0].~basic_string();
    p[1].~basic_string();
    :: operator delete(raw);
    return 0;
}