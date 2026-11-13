#include<iostream>
#include<string>
using namespace std;
template <typename T>
T myMax(const T& a,const T& b){
    return a>b ? a:b;
}
int main(){
  cout<<  myMax(3,4)<<endl;;
  cout<<  myMax(3.5,5.6)<<endl;
  cout<<  myMax(std::string("abc"),std::string("bcd"))<<endl;;
}