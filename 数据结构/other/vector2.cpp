#include<iostream>

#define MAXSIZE 100

namespace mystl {

using ElemType = int;

class vector {
public:
	ElemType* m_elem{ nullptr };
	int m_length{ 0 };

	// 构造与析构函数
	vector() : m_elem(nullptr), m_length(0) {}
	vector(int n) {
		m_elem = new int[MAXSIZE];
		for (int i = 0; i < n; ++i) {
			m_elem[i] = 0;
		}
		m_length = n;
	}
	vector(int n, int value) {
		m_elem = new int[MAXSIZE];
		for (int i = 0; i < n; ++i) {
			m_elem[i] = value;
		}
		m_length = n;
	}
	vector(const vector& vec) {
		m_elem = new int[MAXSIZE];
		for (int i = 0; i < vec.m_length; ++i) {
			m_elem[i] = vec.m_elem[i];
		}
		m_length = vec.m_length;
	}
	vector(std::initializer_list<int> rhs) {
		m_elem = new int[MAXSIZE];
		int pos{ 0 };
		for (auto it = rhs.begin(); it != rhs.end(); ++it) {
			m_elem[pos++] = *it;
		}
		m_length = rhs.size();
	}
	~vector() {
		delete(m_elem);
	}

	void initList() {
		m_elem = new ElemType[MAXSIZE];
		if (!m_elem) {
			std::cout << "存储分配失败";
			std::cout << '\n';
			return;
		}
		m_length = 0;
	}

	void getElem(int i, ElemType& e) {
		if (i < 1 || i > m_length) {
			std::cout << "被访问元素不在当前线性表元素的范围内,越界";
			std::cout << '\n';
			return;
		}
		e = m_elem[i - 1];
	}

	//在顺序表vec中查找值为e的数据元素， 返回其序号
	int locateElem(ElemType e) {
		for (int i = 0; i < m_length; ++i) {
			if (m_elem[i] == e) {
				return i + 1; //查找成功， 返回序号 i+l
			}
		}
		return 0; //查找失败， 返回 0           
	}

	//在顺序表 vec 中第 i 个位置之前插入新的元素 e, i值的合法范围是 1...i...m_length+l
	void listInsert(int i, ElemType e) {
		if (i < 1 || i > m_length + 1) {
			std::cout << "插入位置不合理,越界";
			std::cout << '\n';
			return;
		}
		if (m_length == MAXSIZE) {
			std::cout << "当前存储空间已满";
			std::cout << '\n';
			return;
		}
		for (int j = m_length - 1; j >= i - 1; --j) {
			m_elem[j + 1] = m_elem[j]; //插入位置及之后的元素后移
		}
		m_elem[i - 1] = e; //将新元素e放入第1个位置
		++m_length; //表长加1
	}

	//在顺序表vec中删除第i个元素，i值的合法范围是1到1 + m_length
	void listDelete(int i) {
		if (i < 1 || i > m_length) {
			std::cout << "删除位置不合理，越界";
			std::cout << '\n';
			return;
		}
		for (int j = i; j <= m_length - 1; ++j) {
			m_elem[j - 1] = m_elem[j];
		}
		m_length--;
	}

	//打印
	void printVector() {
		for (int i = 0; i < m_length; ++i) {
			std::cout << m_elem[i] << "	";
		}
		std::cout << '\n';
	}
};

}

int main() {
	mystl::vector v1(4);
	v1.m_elem[0] = 1, v1.m_elem[1] = 2, v1.m_elem[2] = 3, v1.m_elem[3] = 4;

	int e{ 3 };
	std::cout << v1.locateElem(e) << '\n'; //3
	e = -1;
	std::cout << v1.locateElem(e) << '\n'; //0
	v1.getElem(66, e);
	v1.getElem(2, e);
	std::cout << e << '\n'; //2
	e = 222;
	v1.listInsert(5, e);
	v1.listInsert(10, e);
	v1.printVector(); //1 2 3 4 222

	v1.m_length = 100;
	v1.listInsert(100, e);
	std::cout << '\n';

	v1.m_length = 5;
	v1.listDelete(7);
	v1.listDelete(-1);
	v1.listDelete(5);
	v1.listDelete(2);
	v1.printVector(); //1 3 4

	mystl::vector v2{ 1,11,23,4,7 };
	v2.printVector(); //1 11 23 4 7

	mystl::vector v3(v2);
	v3.printVector(); //1 11 23 4 7

	return 0;
}