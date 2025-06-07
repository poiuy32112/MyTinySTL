#pragma once

#include<iostream>
#include <vector>
#include "uninitialized_vector6.h"

namespace mystl {

class vector {
protected:
	int* m_start{ nullptr };
	int* m_finish{ nullptr };
	int* m_cap{ nullptr };
	int extend_ratio{ 2 };

public:
	// ��������������
	vector();
	vector(int n);
	vector(int n, int value);
	vector(const vector& vec);
	vector(std::initializer_list<int> rhs);
	~vector() { delete[] m_start; }

	// ��������ز���
	int* begin() noexcept { return m_start; }
	const int* begin() const noexcept { return m_start; }
	int* end() noexcept { return m_finish; }
	const int* end() const noexcept { return m_finish; }

	//��������
	void extendCap();

	// ������ز���
	int size() const { return m_finish - m_start; }
	int capacity() const { return m_cap - m_start; }
	bool empty() const { return m_start == m_finish; }

	// ������ز���
	int& front() { return *m_start; }
	const int& front() const { return *m_start; }
	int& back() { return *(m_finish - 1); }
	const int& back() const { return *(m_finish - 1); }
	int& operator[](int n) { return *(m_start + n); }
	const int& operator[](int n) const { return *(m_start + n); }

	// �޸������Ĳ���
	void push_back(const int& value);
	void pop_back();
	int* insert(int* pos, int value);
	int* erase(int* pos);
	void resize(int n, int value);
	void clear() { m_start = m_finish = nullptr; }

	//��ӡ
	void printVector();
};

void vector::extendCap() {
	int old_size = size();
	int* old_start = m_start;
	int new_cap = capacity() * extend_ratio;
	int* tmp = m_start;
	m_start = new int[new_cap];
	//for (int i = 0; i < old_size; ++i) {
	//	m_start[i] = tmp[i];
	//}
	std::copy(old_start, old_start + old_size, m_start);
	delete[] tmp;
	m_finish = m_start + old_size;
	m_cap = m_start + new_cap;
}

vector::vector() {
	m_start = new int[16];
	m_finish = m_start + 16;
	m_cap = m_start + 16;
}

vector::vector(int n) {
	m_start = new int[n];
	//for (int i = 0; i < n; ++i) {
	//	m_start[i] = 0;
	//}
	m_finish = m_start + n;
	mystl::uninitialized_fill(m_start, m_finish, 0);
	m_cap = m_start + n;
}

vector::vector(std::initializer_list<int> rhs) {
	m_start = new int[rhs.size()];
	//int pos{ 0 };
	//for (auto it = rhs.begin(); it != rhs.end(); ++it) {
	//	m_start[pos++] = *it;
	//}
	std::copy(rhs.begin(), rhs.end(), m_start);
	m_finish = m_start + rhs.size();
	m_cap = m_start + rhs.size();
}

vector::vector(const vector& vec) {
	m_start = new int[vec.size()];
	//for (int i = 0; i < vec.size(); ++i) {
	//	m_start[i] = vec.m_start[i];
	//}
	std::copy(vec.begin(), vec.end(), m_start);
	m_finish = m_start + vec.size();
	m_cap = m_start + vec.size();
}

vector::vector(int n, int value) {
	m_start = new int[n];
	for (int i = 0; i < n; ++i) {
		m_start[i] = value;
	}
	m_finish = m_start + n;
	mystl::uninitialized_fill(m_start, m_finish, value);
	m_cap = m_start + n;
}

void vector::push_back(const int& value) {
	if (size() == capacity()) {
		extendCap();
	}
	*m_finish = value;
	m_finish++;
}

void vector::pop_back() {
	if (size() == 0) {
		std::cout << "��ǰvectorû��Ԫ�أ�����ִ��pop_back()" << '\n';
		return;
	}
	m_finish--;
}

int* vector::insert(int* pos, int value) {
	int n = pos - m_start;
	if (n < 0 || n >= size()) {
		std::cout << "Խ�磬����ִ��insert()" << '\n';
		return nullptr;
	}
	if (size() == capacity()) {
		extendCap();
	}
	for (int i = size() - 1; i >= n; --i) {
		m_start[i + 1] = m_start[i];
	}
	*(m_start + n) = value;
	m_finish++;
}

int* vector::erase(int* pos) {
	int n = pos - m_start;
	if (n < 0 || n >= size()) {
		std::cout << "Խ�磬����ִ��erase()" << '\n';
		return 0;
	}
	if (size() == 0) {
		std::cout << "��ǰvectorû��Ԫ�أ�����ִ��erase()" << '\n';
		return 0;
	}
	int* iterator = m_start + n;
	for (int i = n; i < size() - 1; ++i) {
		m_start[i] = m_start[i + 1];
	}
	m_finish--;
	return iterator;
}

void vector::resize(int n, int value) {
	if (!m_start || n < 0) {
		std::cout << "�쳣������ִ��resize()" << '\n';
		return;
	}
	if (n > capacity()) {
		int cur_cap = capacity();
		extendCap();
		for (int i = size(); i < n; ++i) {
			m_start[i] = value;
		}
	} else if (n > size()) {
		for (int i = size(); i < n; ++i) {
			m_start[i] = value;
		}
	}
	m_finish = m_start + n;
}

void vector::printVector() {
	for (auto it = begin(); it != end(); ++it) {
		std::cout << *it << "	";
	}
	std::cout << '\n';
}

}