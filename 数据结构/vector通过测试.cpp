#include<iostream>

#define MAXSIZE 100

/*
initList����Ϊ˳����ʼ��
getElem����Ϊ˳���ȡֵ��ȡ����Ӧ��ŵ�Ԫ�ص�ֵ������Ǵ�1��ʼ���������±겻һ����
locateElem����Ϊ˳���İ�ֵ����,����˳������Ƿ����Ҫ���ҵ�Ԫ�ص�ֵ��������ڷ��������
listInsert����Ϊ˳������Ԫ��
listDelete����Ϊ˳���ɾ��Ԫ��
*/

namespace mystl {

struct vector {
	int* elem;
	int length;
};

void initList(vector& vec) {
	vec.elem = new int[MAXSIZE];
	vec.length = 0;
}

int locateElem(vector& vec, int e) {
	for (int i = 0; i < vec.length; ++i) {
		if (vec.elem[i] == e) return i + 1;
	}
	return 0;
}
//getElem(v1, 66, e);
void getElem(vector& vec, int pos, int& e) {
	if (pos < 1 || pos > vec.length) {
		std::cout << "������Ԫ�ز��ڵ�ǰ���Ա�ķ�Χ�ڣ�Խ��" << std::endl;
		return;
	}
	e = vec.elem[pos - 1];
}
//listInsert(v1, 5, e);
//1 2 3
//1 2 44 3
void listInsert(vector& vec, int pos, int e) {
	if (pos < 1 || pos > vec.length + 1) {
		std::cout << "����λ�ò�����Խ��" << std::endl;
		return;
	}
	if (vec.length == 100) {
		std::cout << "��ǰ�洢�ռ�����" << std::endl;
		return;
	}
	for (int j = vec.length - 1; j >= pos - 1; --j) {
		vec.elem[j + 1] = vec.elem[j];
	}
	vec.elem[pos - 1] = e;
	vec.length++;
}
//listDelete(v1, 7);
//1 2 3 4
//1 2 4
void listDelete(vector& vec, int pos) {
	if (pos < 1 || pos > vec.length) {
		std::cout << "ɾ��λ�ò�����Խ��" << std::endl;
		return;
	}
	for (int j = pos - 1; j < vec.length - 1; ++j) {
		vec.elem[j] = vec.elem[j + 1];
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