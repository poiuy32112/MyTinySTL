#include<iostream>

struct Node {
	int data{ 0 };
	struct Node* next{ nullptr };

	Node(int val) : data(val) {}
};

struct Stack {
	Node* top{ nullptr };
	int size{ 0 };
};

using LinkStack = Stack;

//构造一个空栈s，栈顶指针置空
void initStack(LinkStack& s) {
	s.top = nullptr;
}

//在栈顶插入元素e
void push(LinkStack& s, int e) {
	Node* p = new Node(e);
	p->next = s.top;
	s.top = p;
	s.size++;
}

//删除s的栈顶元素，用e返回其值
void pop(LinkStack& s, int& e) {
	if (s.top == nullptr) {
		std::cout << "栈空，不能执行pop操作" << std::endl;
		return;
	}
	e = s.top->data;
	Node* p = s.top; 
	s.top = s.top->next;
	delete p;
	s.size--;
}

//返回s的栈顶元素，不修改栈顶指针
int getTop(LinkStack& s) {
	if (s.top) {
		return s.top->data;
	}
}

//销毁栈s
void destroyStack(LinkStack& s) {
	Node* p{ nullptr };
	while (s.top) {
		p = s.top;
		s.top = s.top->next;
		delete p;
	}
}

//若栈s为空栈，返回true，否则返回false
bool stackEmpty(LinkStack& s) {
	return s.size == 0;
}

//返回s的元素个数，即栈的长度
int stackLength(LinkStack& s) {
	return s.size;
}

//从栈顶到栈底依次打印出s的每个数据元素
void stackTraverse(LinkStack& s) {
	for (auto it = s.top; it != nullptr; it = it->next) {
		std::cout << it->data << " ";
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
	stackTraverse(s); //5 4 3 2 1

	int e{ 0 };
	pop(s, e);
	std::cout << e << std::endl; //5
	std::cout << getTop(s) << std::endl; //4

	destroyStack(s);
	pop(s, e);

	Stack s1;
	initStack(s1);
	push(s1, 1);
	push(s1, 2);
	std::cout << stackLength(s1) << std::endl; //2
	std::cout << stackEmpty(s1) << std::endl; //false
	pop(s1, e);
	pop(s1, e);
	std::cout << stackLength(s1) << std::endl; //0
	std::cout << stackEmpty(s1) << std::endl; //true
	return 0;
}

//initStack //构造一个空栈s
//push //插入元素e为新的栈顶元素
//pop //删除s的栈顶元素，用e返回其值
//getTop //返回s的栈顶元素，不修改栈顶指针
//destroyStack //销毁栈s
//stackEmpty //若栈s为空栈，返回true，否则返回false
//stackLength //返回s的元素个数，即栈的长度
//stackTraverse //从栈顶到栈底依次打印出s的每个数据元素

