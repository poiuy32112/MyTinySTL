#pragma once

#include <memory>
#include <iostream>

// 自定义分配器，用于跟踪内存分配和释放
template <typename T>
class tracking_allocator
{
public:
    typedef T                       value_type;
    typedef T*                      pointer;
    typedef const T*                const_pointer;
    typedef T&                      reference;
    typedef const T&                const_reference;
    typedef size_t                  size_type;
    typedef ptrdiff_t               difference_type;

    // 静态变量用于跟踪分配统计
    static size_t allocations;
    static size_t deallocations;
    static size_t total_allocated;

    // 重绑定模板
    template <typename U>
    struct rebind
    {
        typedef tracking_allocator<U> other;
    };

    // 构造函数
    tracking_allocator() = default;

    template <typename U>
    tracking_allocator(const tracking_allocator<U>&) {}

    // 分配内存
    pointer allocate(size_type n)
    {
        if (n == 0) return nullptr;

        pointer p = static_cast<pointer>(std::malloc(n * sizeof(T)));
        if (!p)
        {
            throw std::bad_alloc();
        }

        allocations++;
        total_allocated += n;
        std::cout << "[Allocator] 分配 " << n << " 个 " << typeid(T).name()
            << " 元素，地址: " << p << std::endl;
        return p;
    }

    // 释放内存
    void deallocate(pointer p, size_type n)
    {
        if (p)
        {
            deallocations++;
            std::cout << "[Allocator] 释放 " << n << " 个 " << typeid(T).name()
                << " 元素，地址: " << p << std::endl;
            std::free(p);
        }
    }

    // 比较操作符
    template <typename U>
    bool operator==(const tracking_allocator<U>&) const { return true; }

    template <typename U>
    bool operator!=(const tracking_allocator<U>&) const { return false; }

    // 重置统计信息
    static void reset_stats()
    {
        allocations = 0;
        deallocations = 0;
        total_allocated = 0;
    }

    // 打印统计信息
    static void print_stats()
    {
        std::cout << "[Allocator Stats] 分配次数: " << allocations
            << ", 释放次数: " << deallocations
            << ", 总分配元素数: " << total_allocated << std::endl;
    }
};

// 静态成员变量定义
template <typename T>
size_t tracking_allocator<T>::allocations = 0;

template <typename T>
size_t tracking_allocator<T>::deallocations = 0;

template <typename T>
size_t tracking_allocator<T>::total_allocated = 0;
