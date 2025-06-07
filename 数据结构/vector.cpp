#include<iostream>

#define MAXSIZE 100

namespace mystl {

using ElemType = int;

struct vector {
	ElemType* elem;
	int length{ 0 };
};

void initList(vector& vec) {
	vec.elem = new ElemType[MAXSIZE];
	if (!vec.elem) {
		std::cout << "�洢����ʧ��";
		std::cout << std::endl;
		return;
	}
	vec.length = 0;
}

void getElem(vector& vec, int i, ElemType& e) {
	if (i < 1 || i > vec.length) {
		std::cout << "������Ԫ�ز��ڵ�ǰ���Ա�Ԫ�صķ�Χ��,Խ��";
		std::cout << std::endl;
		return;
	}
	e = vec.elem[i - 1];
}

int locateElem(vector& vec, ElemType e) { //��˳���vec�в���ֵΪe������Ԫ�أ� ���������
	for (int i = 0; i < vec.length; ++i) {
		if (vec.elem[i] == e) {
			return i + 1; //���ҳɹ��� ������� i+l
		}
	}
	return 0; //����ʧ�ܣ� ���� 0           
}

void listInsert(vector& vec, int i, ElemType e) {
	//��˳��� vec �е� i ��λ��֮ǰ�����µ�Ԫ�� e, iֵ�ĺϷ���Χ�� 1...i...vec.length+l
	if (i < 1 || i > vec.length + 1) {
		std::cout << "����λ�ò�����,Խ��";
		std::cout << std::endl;
		return;
	}
	if (vec.length == MAXSIZE) {
		std::cout << "��ǰ�洢�ռ�����"; 
		std::cout << std::endl;
		return;
	}
	for (int j = vec.length - 1; j >= i - 1; --j) {
		vec.elem[j + 1] = vec.elem[j]; //����λ�ü�֮���Ԫ�غ���
	}
	vec.elem[i - 1] = e; //����Ԫ��e�����1��λ��
	++vec.length; //����1
}

void listDelete(vector& vec, int i) {
	//��˳���vec��ɾ����i��Ԫ�أ�iֵ�ĺϷ���Χ��1��1 + vec.length
	if (i < 1 || i > vec.length) {
		std::cout << "ɾ��λ�ò�����Խ��";
		std::cout << std::endl;
		return;
	}
	for (int j = i; j <= vec.length - 1; ++j) {
		vec.elem[j - 1] = vec.elem[j];
	}
	vec.length--;
}

}


int main() {
	mystl::vector v1;
	initList(v1);
	v1.length = 4;
	v1.elem[0] = 1, v1.elem[1] = 2, v1.elem[2] = 3, v1.elem[3] = 4;
	
	int e{ 3 };
	std::cout << locateElem(v1, e) << std::endl;
	e = -1;
	std::cout << locateElem(v1, e) << std::endl;
	getElem(v1, 66, e);
	getElem(v1, 2, e);
	std::cout << e << std::endl;
	e = 222;
	listInsert(v1, 5, e);
	listInsert(v1, 10, e);
	for (auto it = v1.elem; it != v1.elem + v1.length; ++it) {
		std::cout << *it << "	";
	}
	std::cout << std::endl;
	v1.length = 100;
	listInsert(v1, 100, e);
	std::cout << std::endl;

	v1.length = 5;
	listDelete(v1, 7);
	listDelete(v1, -1);
	listDelete(v1, 5);
	listDelete(v1, 2);
	for (auto it = v1.elem; it != v1.elem + v1.length; ++it) {
		std::cout << *it << "	";
	}
	std::cout << std::endl;

	return 0;
}