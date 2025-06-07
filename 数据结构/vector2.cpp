#include<iostream>

#define MAXSIZE 100

namespace mystl {

using ElemType = int;

class vector {
public:
	ElemType* m_elem{ nullptr };
	int m_length{ 0 };

	// ��������������
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
			std::cout << "�洢����ʧ��";
			std::cout << '\n';
			return;
		}
		m_length = 0;
	}

	void getElem(int i, ElemType& e) {
		if (i < 1 || i > m_length) {
			std::cout << "������Ԫ�ز��ڵ�ǰ���Ա�Ԫ�صķ�Χ��,Խ��";
			std::cout << '\n';
			return;
		}
		e = m_elem[i - 1];
	}

	//��˳���vec�в���ֵΪe������Ԫ�أ� ���������
	int locateElem(ElemType e) {
		for (int i = 0; i < m_length; ++i) {
			if (m_elem[i] == e) {
				return i + 1; //���ҳɹ��� ������� i+l
			}
		}
		return 0; //����ʧ�ܣ� ���� 0           
	}

	//��˳��� vec �е� i ��λ��֮ǰ�����µ�Ԫ�� e, iֵ�ĺϷ���Χ�� 1...i...m_length+l
	void listInsert(int i, ElemType e) {
		if (i < 1 || i > m_length + 1) {
			std::cout << "����λ�ò�����,Խ��";
			std::cout << '\n';
			return;
		}
		if (m_length == MAXSIZE) {
			std::cout << "��ǰ�洢�ռ�����";
			std::cout << '\n';
			return;
		}
		for (int j = m_length - 1; j >= i - 1; --j) {
			m_elem[j + 1] = m_elem[j]; //����λ�ü�֮���Ԫ�غ���
		}
		m_elem[i - 1] = e; //����Ԫ��e�����1��λ��
		++m_length; //����1
	}

	//��˳���vec��ɾ����i��Ԫ�أ�iֵ�ĺϷ���Χ��1��1 + m_length
	void listDelete(int i) {
		if (i < 1 || i > m_length) {
			std::cout << "ɾ��λ�ò�����Խ��";
			std::cout << '\n';
			return;
		}
		for (int j = i; j <= m_length - 1; ++j) {
			m_elem[j - 1] = m_elem[j];
		}
		m_length--;
	}

	//��ӡ
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