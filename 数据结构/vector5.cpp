#include<iostream>
#include <vector>

namespace mystl {

class vector {
protected:
	int* m_start{ nullptr };
	int* m_finish{ nullptr };
	int* m_cap{ nullptr };
	int extend_ratio{ 2 };

public:
	// 构造与析构函数
	vector();
	vector(int n);
	vector(int n, int value);
	vector(const vector& vec);
	vector(std::initializer_list<int> rhs);
	~vector() { delete[] m_start; }

	// 迭代器相关操作
	int* begin() noexcept { return m_start; }
	const int* begin() const noexcept { return m_start; }
	int* end() noexcept { return m_finish; }
	const int* end() const noexcept { return m_finish; }

	//容器扩容
	void extendCap();

	// 容量相关操作
	int size() const { return m_finish - m_start; }
	int capacity() const { return m_cap - m_start; }
	bool empty() const { return m_start == m_finish; }

	// 访问相关操作
	int& front() { return *m_start; }
	const int& front() const { return *m_start; }
	int& back() { return *(m_finish - 1); }
	const int& back() const { return *(m_finish - 1); }
	int& operator[](int n) { return *(m_start + n); }
	const int& operator[](int n) const { return *(m_start + n); }

	// 修改容器的操作
	void push_back(const int& value);
	void pop_back();
	int* insert(int* pos, int value);
	int* erase(int* pos);
	void resize(int n, int value);
	void clear() { m_start = m_finish = nullptr; }

	//打印
	void printVector();
};

void vector::extendCap() {
	int old_size = size();
	int new_cap = capacity() * extend_ratio;
	int* tmp = m_start;
	m_start = new int[new_cap];
	for (int i = 0; i < old_size; ++i) {
		m_start[i] = tmp[i];
	}
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
	for (int i = 0; i < n; ++i) {
		m_start[i] = 0;
	}
	m_finish = m_start + n;
	m_cap = m_start + n;
}

vector::vector(std::initializer_list<int> rhs) {
	m_start = new int[rhs.size()];
	int pos{ 0 };
	for (auto it = rhs.begin(); it != rhs.end(); ++it) {
		m_start[pos++] = *it;
	}
	m_finish = m_start + rhs.size();
	m_cap = m_start + rhs.size();
}

vector::vector(const vector& vec) {
	m_start = new int[vec.size()];
	for (int i = 0; i < vec.size(); ++i) {
		m_start[i] = vec.m_start[i];
	}
	m_finish = m_start + vec.size();
	m_cap = m_start + vec.size();
}

vector::vector(int n, int value) {
	m_start = new int[n];
	for (int i = 0; i < n; ++i) {
		m_start[i] = value;
	}
	m_finish = m_start + n;
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
		std::cout << "当前vector没有元素，不能执行pop_back()" << '\n';
		return;
	}
	m_finish--;
}

int* vector::insert(int* pos, int value) {
	int n = pos - m_start;
	if (n < 0 || n >= size()) {
		std::cout << "越界，不能执行insert()" << '\n';
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
	return m_start + n;
}

int* vector::erase(int* pos) {
	int n = pos - m_start;
	if (n < 0 || n >= size()) {
		std::cout << "越界，不能执行erase()" << '\n';
		return 0;
	}
	if (size() == 0) {
		std::cout << "当前vector没有元素，不能执行erase()" << '\n';
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
		std::cout << "异常，不能执行resize()" << '\n';
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

int main() {
	mystl::vector v1(4);
	v1[0] = 1, v1[1] = 2, v1[2] = 3, v1[3] = 4;

	std::cout << v1.size() << '\n'; //4
	std::cout << v1.front() << '\n'; //1
	std::cout << v1.back() << '\n'; //4
	std::cout << v1[1] << '\n'; //2
	v1.insert(v1.begin() + 3, 222);
	v1.insert(v1.begin() + 5, 1);
	v1.push_back(5);
	v1.push_back(6);
	v1.pop_back();
	v1.printVector(); //1 2 3 222 4 5

	v1.insert(v1.begin(), -1);
	v1.erase(v1.begin() + 7);
	v1.erase(v1.begin() + 1);
	v1.insert(v1.begin(), -2); //-2 -1 2 3 222 4 5
	v1.erase(v1.begin() + 5); //-2 -1 2 3 222 5
	v1.printVector(); //-2 -1 2 3 222 5

	std::cout << v1.empty() << '\n'; //0
	v1.resize(9, 33);
	v1.printVector(); //-2 -1 2 3 222 5 33 33 33
	std::cout << "----------------------\n";

	mystl::vector v2{ 1,11,23,4,7 };
	v2.printVector(); //1 11 23 4 7

	mystl::vector v3(v2);
	v3.printVector(); //1 11 23 4 7

	return 0;
}

//size_type size()
//reference front()
//reference back()
//reference operator[](size_type n)
//void push_back(const T& value)
//void pop_back()
//iterator insert(iterator position, const T& value)
//iterator erase(iterator position);
//void resize(size_type new_size, const T& value)
//void clear()

//std::vector<int> a(1);
//a.insert(a.begin(), 1);
//for (auto& i : a) {
//	std::cout << i << " ";
//}
//std::cout << '\n';