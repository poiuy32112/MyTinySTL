#pragma once

#include <new>

namespace mystl {

inline void construct(int* ptr, const int& value) {
    new (ptr) int(value);
}

inline void construct(int* ptr, int&& value) {
    new (ptr) int(value);
}

inline void construct(int* ptr) {
    new (ptr) int();
}

}
