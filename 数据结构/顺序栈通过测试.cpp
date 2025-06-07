#include<iostream>

#define MAXSIZE 4

struct Stack {
	int* base{ nullptr };
	int* top{ nullptr };
	int stack_size{ 0 };
	int stack_length{ 0 };
};

void initStack(Stack& s) {
	s.base = new int[MAXSIZE];
	s.top = s.base;
	s.stack_size = MAXSIZE;
}

void push(Stack& s, int e) {
	if (s.top - s.base == s.stack_size) {
		std::cout << "栈已满，不能再插入新的栈顶元素" << std::endl;
		return;
	}
	*s.top = e;
	s.top++;
	s.stack_length++;
}

void pop(Stack& s, int& e) {
	if (s.top - s.base == 0) {
		std::cout << "栈空，不能执行pop操作" << std::endl;
		return;
	}
	s.top--;
	e = *s.top;
	s.stack_length--;
}

int getTop(Stack& s) {
	return *(s.top - 1);
}

void destroyStack(Stack& s) {
	s.top = nullptr;
	delete(s.base);
	s.base = nullptr;
}

void clearStack(Stack& s) {
	s.top = s.base;
	s.stack_length = 0;
}

bool stackEmpty(Stack& s) {
	return s.stack_length == 0;
}

int stackLength(Stack& s) {
	return s.stack_length;
}

void stackTraverse(Stack& s) {
	for (auto it = s.base; it != s.top; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

int main() {
	Stack s;
	initStack(s);
	push(s, 1);
	push(s, 2);
	push(s, 3);
	push(s, 4);
	push(s, 5);
	stackTraverse(s); //1 2 3 4

	int e{ 0 };
	pop(s, e);
	std::cout << e << std::endl; //4
	std::cout << getTop(s) << std::endl; //3

	destroyStack(s);
	pop(s, e);

	Stack s1;
	initStack(s1);
	push(s1, 1);
	push(s1, 2);
	std::cout << stackLength(s1) << std::endl; //2
	std::cout << stackEmpty(s1) << std::endl; //false
	clearStack(s1);
	std::cout << stackLength(s1) << std::endl; //0
	std::cout << stackEmpty(s1) << std::endl; //true
	return 0;
}