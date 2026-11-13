#pragma once
#include<cstddef>
#include<stdexcept>
#include<utility>
#include<new>
template<typename T>
class MiniVector{
    public:
    MiniVector()=default;
    MiniVector(const MiniVector& o);
    ~MiniVector();
    void push_back(const T& value);
    void push_back( T&& value);
    void reserve(std::size_t NewCap);
    std::size_t size() const { return size_;}
    std::size_t capacity () const {return cap_;}
    private:
    void reallocate(std::size_t NewCap);
    T* data_=nullptr;
    std::size_t size_=0;
    std::size_t cap_=0;
};
template<typename T>
void MiniVector<T> ::reallocate(std::size_t NewCap){
    T* Newdata=static_cast<T*>(::operator new(sizeof(T)*NewCap));
    std::size_t built=0;
    try{
        for( ;built<size_;built++){
            new(Newdata+built) T(std::move_if_noexcept(data_[built]));
        }
    }catch(...){
        for(std::size_t i=0;i<built;i++){
            Newdata[i].~T();
        }
        ::operator delete(Newdata);
        throw;
    }
    for(std::size_t i=0;i<size_;i++){
        data_[i].~T();
    }
    ::operator delete(data_);
    data_=Newdata;
    cap_=NewCap;
}
template<typename T>
 MiniVector<T>::~MiniVector(){
    for(std::size_t i=0;i<size_;i++){
        data_[i].~T();
    }
    ::operator delete(data_);
}
template<typename T>
void MiniVector<T>::push_back(const T& value){
    if(cap_==size_) reallocate(cap_==0 ? 1:cap_*2);
    new(data_+size_) T(value);
    size_++;
}
template<typename T>
void MiniVector<T>::push_back( T&& value){
    if(size_==cap_) reallocate(cap_==0 ? 1:cap_*2);
    new(data_+size_) T(std::move(value));
    size_++;
}
template<typename T>
void MiniVector<T>::reserve(std::size_t NewCap){
    if(size_>cap_) reallocate(NewCap);
}