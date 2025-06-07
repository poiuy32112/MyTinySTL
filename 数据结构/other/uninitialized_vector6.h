#pragma once

#include "construct_vector6.h"

namespace mystl {

inline void uninitialized_fill(int* first, int* last, const int value) {
	int* cur = first;
	for (; cur != last; ++cur) {
		mystl::construct(cur, value);
	}
}

inline void uninitialized_copy(int* first, int* last, int* result) {
	int* cur = result;
	for (; first != last; ++first, ++cur) {
		mystl::construct(cur, *first);
	}
}




}