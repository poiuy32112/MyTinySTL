#pragma once

#include "construct_vector6.h"
#include <cstdint>

namespace mystl {

class allocator {
public:
    // ��������ڴ�
    static int* allocate();
    static int* allocate(int n);
    // �����ͷ��ڴ�
    static void deallocate(int* ptr);
    static void deallocate(int*, int n);
    // ���������
    static void construct(int* ptr);
    static void construct(int* ptr, const int& value);
    static void construct(int* ptr, int&& value);
    // ������������
    static void destroy(int* ptr);
    static void destroy(int* first, int* last);
    // ��ȡĳ����ĵ�ַ
    static int* address(int& val);
    // ��ȡ������int���Ͷ���������Ŀ
    static int max_size();

};

int* allocator::allocate() {
    return static_cast<int*>(::operator new(sizeof(int)));
}

int* allocator::allocate(int n) {
    return static_cast<int*>(::operator new(n * sizeof(int)));
}

void allocator::deallocate(int* ptr) {
    if (ptr != nullptr)
        ::operator delete(ptr);
}

void allocator::deallocate(int* ptr, int) {
    if (ptr != nullptr)
        ::operator delete(ptr);
}

void allocator::construct(int* ptr) {
    mystl::construct(ptr);
}

void allocator::construct(int* ptr, const int& value) {
    mystl::construct(ptr, value);
}

void allocator::construct(int* ptr, int&& value) {
    mystl::construct(ptr, std::move(value));
}

void allocator::destroy(int* ptr) {
    mystl::destroy(ptr);
}

void allocator::destroy(int* first, int* last) {
    mystl::destroy(first, last);
}

int* allocator::address(int& val) {
    return (int*)&val;
}

size_t allocator::max_size() {
    return size_t(WINT_MAX / sizeof(int));
}

}