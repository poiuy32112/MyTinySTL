#include<iostream>
#include <vector>

namespace mystl {

class vector {
private:
	int* m_elem{ nullptr };
	int m_size{ 0 };
	int m_cap{ 10 };
	int extend_ratio{ 2 };

public:
	// ��������������
	vector() { m_elem = new int[m_cap]; }
	vector(int n);
	vector(int n, int value);
	vector(const vector& vec);
	vector(std::initializer_list<int> rhs);
	~vector() { delete[] m_elem; }

	//��������
	void extendCap();

	int size() { return m_size; }
	int capacity() { return m_cap; }
	int& front() { return m_elem[0]; }
	int& back() { return m_elem[m_size - 1]; }

	int& operator[](int n) { return m_elem[n]; }

	void push_back(const int& value);
	void pop_back();
	void insert(int pos, int value);
	int erase(int pos);
	void resize(int n, int value);
	void clear() { m_size = 0; }

	bool empty() { return m_size == 0; }

	//��ӡ
	void printVector();
};

void vector::extendCap() {
	int new_cap = capacity() * extend_ratio;
	int* tmp = m_elem;
	m_elem = new int[new_cap];
	for (int i = 0; i < size(); ++i) {
		m_elem[i] = tmp[i];
	}
	delete[] tmp;
	m_cap = new_cap;
}

vector::vector(int n) {
	m_elem = new int[n];
	for (int i = 0; i < n; ++i) {
		m_elem[i] = 0;
	}
	m_size = n;
	m_cap = n;
}

vector::vector(std::initializer_list<int> rhs) {
	m_elem = new int[rhs.size()];
	int pos{ 0 };
	for (auto it = rhs.begin(); it != rhs.end(); ++it) {
		m_elem[pos++] = *it;
	}
	m_size = rhs.size();
	m_cap = rhs.size();
}

vector::vector(const vector& vec) {
	m_elem = new int[vec.m_size];
	for (int i = 0; i < vec.m_size; ++i) {
		m_elem[i] = vec.m_elem[i];
	}
	m_size = vec.m_size;
	m_cap = vec.m_size;
}

vector::vector(int n, int value) {
	m_elem = new int[n];
	for (int i = 0; i < n; ++i) {
		m_elem[i] = value;
	}
	m_size = n;
	m_cap = n;
}

void vector::push_back(const int& value) {
	if (m_size == m_cap) {
		extendCap();
	}
	m_elem[m_size] = value;
	m_size++;
}

void vector::pop_back() {
	if (m_size == 0) {
		std::cout << "��ǰvectorû��Ԫ�أ�����ִ��pop_back()" << '\n';
		return;
	}
	m_size--;
}

void vector::insert(int pos, int value) {
	if (pos < 0 || pos >= m_size) {
		std::cout << "����Խ�磬����ִ��insert()" << '\n';
		return;
	}
	if (m_size == m_cap) {
		extendCap();
	}
	for (int i = m_size - 1; i >= pos; --i) {
		m_elem[i + 1] = m_elem[i];
	}
	m_elem[pos] = value;
	m_size++;
}

int vector::erase(int pos) {
	if (pos < 0 || pos >= m_size) {
		std::cout << "����Խ�磬����ִ��erase()" << '\n';
		return 0;
	}
	if (m_size == 0) {
		std::cout << "��ǰvectorû��Ԫ�أ�����ִ��erase()" << '\n';
		return 0;
	}
	int num = m_elem[pos];
	for (int i = pos; i < m_size - 1; ++i) {
		m_elem[i] = m_elem[i + 1];
	}
	m_size--;
	return num;
}

void vector::resize(int n, int value) {
	if (!m_elem || n < 0) {
		std::cout << "�쳣������ִ��resize()" << '\n';
		return;
	}
	if (n > m_cap) {
		int cur_cap = m_cap;
		extendCap();
		for (int i = m_size; i < n; ++i) {
			m_elem[i] = value;
		}
	} else if (n > m_size) {
		for (int i = m_size; i < n; ++i) {
			m_elem[i] = value;
		}
	}
	m_size = n;
}

void vector::printVector() {
	for (int i = 0; i < m_size; ++i) {
		std::cout << m_elem[i] << "	";
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
	v1.insert(3, 222);
	v1.insert(5, 1);
	v1.push_back(5);
	v1.push_back(6);
	v1.pop_back();
	v1.printVector(); //1 2 3 222 4 5

	v1.insert(0, -1);
	v1.erase(7);
	v1.erase(1);
	v1.insert(0, -2); //-2 -1 2 3 222 4 5
	v1.erase(5); //-2 -1 2 3 222 5
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