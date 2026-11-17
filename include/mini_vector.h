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
    MiniVector(MiniVector&& o) noexcept;
    ~MiniVector();
    MiniVector& operator=(const MiniVector& o);
    MiniVector& operator=(MiniVector&& o) noexcept;
    void push_back(const T& value);
    void push_back( T&& value);
    void reserve(std::size_t NewCap);
    void swap(MiniVector& o) noexcept;
    bool empty() const {return size_==0;}
    void pop_back();
    void resize(std::size_t n);
    void clear() noexcept;
    T& at(std::size_t i);
    const T& at(std::size_t i) const;
    std::size_t size() const { return size_;}
    std::size_t capacity () const {return cap_;}
    T& operator[](std::size_t i){return data_[i];}
    const T& operator[](std::size_t i) const {return data_[i];}
    T* data() noexcept {return data_;}
    const T* data()const noexcept {return data_;}
    private:
    void reallocate(std::size_t NewCap);
    void destroy_all() noexcept;
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
    destroy_all();
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
    if(NewCap>cap_) reallocate(NewCap);
}
template<typename T>
void MiniVector<T>::destroy_all() noexcept{
    for(std::size_t i=0;i<size_;i++) data_[i].~T();
    ::operator delete(data_);
    data_=nullptr;
    size_=0;
    cap_=0;
}
template<typename T>
MiniVector<T>::MiniVector(const MiniVector& o){
    if(o.size_==0) return;
    data_=static_cast<T*>(::operator new(o.size_*sizeof(T)));
    cap_=o.size_;
    try{
        for( ;size_<o.size_;size_++){
            new(data_+size_)  T(o.data_[size_]);
        }
    }catch(...){
        for(std::size_t i=0;i<size_;i++) data_[i].~T();
        ::operator delete(data_);
        throw;
    }
}
template<typename T>
MiniVector<T>& MiniVector<T>::operator=(const MiniVector& o) {
    if (this != &o) {
        MiniVector tmp(o);
        swap(tmp);
    }
    return *this;
}
template<typename T>
MiniVector<T>::MiniVector(MiniVector&& o) noexcept :data_(o.data_),size_(o.size_),cap_(o.cap_){
    o.data_=nullptr;
    o.size_=0;
    o.cap_=0;
}
template<typename T>
MiniVector<T>& MiniVector<T>::operator=(MiniVector&& o) noexcept{
    if(this!=&o){
        destroy_all();
        data_=o.data_;
        cap_=o.cap_;
        size_=o.size_;
        o.data_=nullptr;
        o.size_=0;
        o.cap_=0;
    }
    return *this;
}
template<typename T>
void MiniVector<T>::swap(MiniVector& o) noexcept{
    std::swap(data_,o.data_);
    std::swap(size_,o.size_);
    std::swap(cap_,o.cap_);
}
template<typename T>
void MiniVector<T>::pop_back(){
    size_--;
    data_[size_].~T();
}
template<typename T>
void MiniVector<T> ::clear() noexcept{
    while(size_>0){
        size_--;
        data_[size_].~T();
    }
}
template<typename T>
void MiniVector<T> ::resize(std::size_t n){
    if(n>size_){
        reserve(n);
        for( ;size_<n;size_++)
        new(data_+size_) T();
    }
    else{
        while(size_>n){
            size_--;
            data_[size_].~T();
        }
    }
}
template<typename T>
T& MiniVector<T>::at(std::size_t i){
    if(i>=size_) throw std::out_of_range("MiniVector::at");
    return data_[i];
}
template<typename T>
const T& MiniVector<T>::at(std::size_t i) const {
    if(i>=size_) throw std::out_of_range("MiniVector::at");
    return data_[i];
}