#pragma once

#include <cstddef>
#include <new>
#include <vector>

class FixedPool {
public:
    explicit FixedPool(std::size_t chunkSize, std::size_t chunksPerBlock = 1024)
        : chunkSize_(chunkSize < sizeof(void*) ? sizeof(void*) : chunkSize),
          chunksPerBlock_(chunksPerBlock == 0 ? 1 : chunksPerBlock) {}

    FixedPool(const FixedPool&) = delete;
    FixedPool& operator=(const FixedPool&) = delete;

    ~FixedPool() {
        for (void* b : blocks_) ::operator delete(b);
    }

    void* allocate() {
        if (!free_) grow();
        void* p = free_;
        free_ = *static_cast<void**>(p);
        return p;
    }

    void deallocate(void* p) {
        *static_cast<void**>(p) = free_;
        free_ = p;
    }

private:
    void grow() {
        char* block = static_cast<char*>(
            ::operator new(chunkSize_ * chunksPerBlock_));
        blocks_.push_back(block);

        for (std::size_t i = 0; i < chunksPerBlock_; ++i) {
            void* p = block + i * chunkSize_;
            *static_cast<void**>(p) = free_;
            free_ = p;
        }
    }

    std::size_t chunkSize_;
    std::size_t chunksPerBlock_;
    void* free_ = nullptr;
    std::vector<void*> blocks_;
};