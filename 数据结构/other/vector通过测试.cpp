#include<iostream>

#define MAXSIZE 100

/*
initList函数为顺序表初始化
getElem函数为顺序表取值，取出对应序号的元素的值（序号是从1开始，与数组下标不一样）
locateElem函数为顺序表的按值查找,查找顺序表中是否存在要查找的元素的值，如果存在返回其序号
listInsert函数为顺序表插入元素
listDelete函数为顺序表删除元素
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
		std::cout << "被访问元素不在当前线性表的范围内，越界" << std::endl;
		return;
	}
	e = vec.elem[pos - 1];
}
//listInsert(v1, 5, e);
//1 2 3
//1 2 44 3
void listInsert(vector& vec, int pos, int e) {
	if (pos < 1 || pos > vec.length + 1) {
		std::cout << "插入位置不合理，越界" << std::endl;
		return;
	}
	if (vec.length == 100) {
		std::cout << "当前存储空间已满" << std::endl;
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
		std::cout << "删除位置不合理，越界" << std::endl;
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