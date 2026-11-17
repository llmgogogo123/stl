#pragma once
#include<cstddef>
#include<functional>
#include<stdexcept>
#include<new>
#include"fixed_pool.h"
template<typename K,typename V,typename Hash=std::hash<K>>
class MiniUnorderedMap{
    private:
    struct Node
    {
        K key;
        V value;
        Node* next;
    };
    public:
    MiniUnorderedMap(std::size_t initialBucket =8):
    buckets_(nullptr),
    bucketCount_(initialBucket==0 ? 8:initialBucket),
    size_(0),
    hash_{},
    pool_(sizeof(Node))
    {
        buckets_=new Node*[bucketCount_]();
    }
    ~MiniUnorderedMap(){
        destroy_all();
        delete[] buckets_;
    }
    MiniUnorderedMap(const MiniUnorderedMap&)=delete;
    MiniUnorderedMap& operator=(const MiniUnorderedMap&)=delete;
    std::size_t size() const noexcept {return size_;}
    bool empty() const noexcept {return size_==0;}
    std::size_t bucket_count() const noexcept {return bucketCount_;}
    double load_factor() const noexcept {
        return static_cast<double> (size_)/bucketCount_;
    }
    bool contains(const K& key) const {
        return find_node(key)!=nullptr;
    }
    V& operator[](const K& key){
        std::size_t idx=index_for(key);
        for(Node* p=buckets_[idx];p!=nullptr;p=p->next){
            if(p->key==key)
            return p->value;
        }
        if(size_+1>bucketCount_){
            rehash(bucketCount_*2);
            idx=index_for(key);
        }
        Node* n=static_cast<Node*>(pool_.allocate());
        new(n) Node{key,V{},nullptr};
        n->next=buckets_[idx];
        buckets_[idx]=n;
        size_++;
        return n->value;
    }
    bool erase(const K& key){
        std::size_t idx=index_for(key);
        Node** pp=&buckets_[idx];
        while(*pp!=nullptr){
            Node* cur = *pp;
            if(cur->key==key){
                *pp=cur->next;
                cur->~Node();
                pool_.deallocate(cur);
                size_--;
                return true;
            }
            pp=&cur->next;
        }
        return false;
    }
    V& at(const K& key){
        Node* p=find_node(key);
        if(p==nullptr)
        throw std::out_of_range("MiniUnorderedMap::at");
        return p->value;
    }
     const V& at(const K& key) const {
        Node* p=find_node(key);
        if(p==nullptr)
        throw std::out_of_range("MiniUnorderedMap::at");
        return p->value;
    }
    void clear(){
        destroy_all();
    }
    private:
    std::size_t index_for(const K& key) const {
        return hash_(key)%bucketCount_;
    }
    Node* find_node(const K& key) const {
        std::size_t idx=index_for(key);
        for(Node* p=buckets_[idx];p!=nullptr;p=p->next){
            if(p->key==key) return p;
        }
        return nullptr;
    }
    void destroy_all(){
        for(std::size_t i=0;i<bucketCount_;i++){
            Node* p=buckets_[i];
            while(p!=nullptr){
                Node* next=p->next;
               p->~Node();
               pool_.deallocate(p);
                p=next;
            }
            buckets_[i]=nullptr;
        }
        size_=0;
    }
    void rehash(std::size_t newCount){
        if(newCount<8) newCount=8;
        Node** newBuckets=new Node*[newCount]();
        for(std::size_t i=0;i<bucketCount_;i++){
            Node* p=buckets_[i];
            while(p!=nullptr){
                Node* next=p->next;
                std::size_t newIdx=hash_(p->key)%newCount;
                p->next=newBuckets[newIdx];
                newBuckets[newIdx]=p;
                p=next;
            }
        }
        delete[] buckets_;
        buckets_=newBuckets;
        bucketCount_=newCount;
    }
    Node** buckets_;
    std::size_t bucketCount_;
    std::size_t size_;
    Hash hash_;
    FixedPool pool_;
};