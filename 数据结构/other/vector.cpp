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
		std::cout << "存储分配失败";
		std::cout << std::endl;
		return;
	}
	vec.length = 0;
}

void getElem(vector& vec, int i, ElemType& e) {
	if (i < 1 || i > vec.length) {
		std::cout << "被访问元素不在当前线性表元素的范围内,越界";
		std::cout << std::endl;
		return;
	}
	e = vec.elem[i - 1];
}

int locateElem(vector& vec, ElemType e) { //在顺序表vec中查找值为e的数据元素， 返回其序号
	for (int i = 0; i < vec.length; ++i) {
		if (vec.elem[i] == e) {
			return i + 1; //查找成功， 返回序号 i+l
		}
	}
	return 0; //查找失败， 返回 0           
}

void listInsert(vector& vec, int i, ElemType e) {
	//在顺序表 vec 中第 i 个位置之前插入新的元素 e, i值的合法范围是 1...i...vec.length+l
	if (i < 1 || i > vec.length + 1) {
		std::cout << "插入位置不合理,越界";
		std::cout << std::endl;
		return;
	}
	if (vec.length == MAXSIZE) {
		std::cout << "当前存储空间已满"; 
		std::cout << std::endl;
		return;
	}
	for (int j = vec.length - 1; j >= i - 1; --j) {
		vec.elem[j + 1] = vec.elem[j]; //插入位置及之后的元素后移
	}
	vec.elem[i - 1] = e; //将新元素e放入第1个位置
	++vec.length; //表长加1
}

void listDelete(vector& vec, int i) {
	//在顺序表vec中删除第i个元素，i值的合法范围是1到1 + vec.length
	if (i < 1 || i > vec.length) {
		std::cout << "删除位置不合理，越界";
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