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

//����һ����ջs��ջ��ָ���ÿ�
void initStack(LinkStack& s) {
	s.top = nullptr;
}

//��ջ������Ԫ��e
void push(LinkStack& s, int e) {
	Node* p = new Node(e);
	p->next = s.top;
	s.top = p;
	s.size++;
}

//ɾ��s��ջ��Ԫ�أ���e������ֵ
void pop(LinkStack& s, int& e) {
	if (s.top == nullptr) {
		std::cout << "ջ�գ�����ִ��pop����" << std::endl;
		return;
	}
	e = s.top->data;
	Node* p = s.top; 
	s.top = s.top->next;
	delete p;
	s.size--;
}

//����s��ջ��Ԫ�أ����޸�ջ��ָ��
int getTop(LinkStack& s) {
	if (s.top) {
		return s.top->data;
	}
}

//����ջs
void destroyStack(LinkStack& s) {
	Node* p{ nullptr };
	while (s.top) {
		p = s.top;
		s.top = s.top->next;
		delete p;
	}
}

//��ջsΪ��ջ������true�����򷵻�false
bool stackEmpty(LinkStack& s) {
	return s.size == 0;
}

//����s��Ԫ�ظ�������ջ�ĳ���
int stackLength(LinkStack& s) {
	return s.size;
}

//��ջ����ջ�����δ�ӡ��s��ÿ������Ԫ��
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

//initStack //����һ����ջs
//push //����Ԫ��eΪ�µ�ջ��Ԫ��
//pop //ɾ��s��ջ��Ԫ�أ���e������ֵ
//getTop //����s��ջ��Ԫ�أ����޸�ջ��ָ��
//destroyStack //����ջs
//stackEmpty //��ջsΪ��ջ������true�����򷵻�false
//stackLength //����s��Ԫ�ظ�������ջ�ĳ���
//stackTraverse //��ջ����ջ�����δ�ӡ��s��ÿ������Ԫ��

