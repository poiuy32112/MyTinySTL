#include<iostream>

#define MAXSIZE 4

struct Stack {
	int* base{ nullptr };
	int* top{ nullptr };
	int stack_size{ 0 };
	int stack_length{ 0 };
};

//����һ����ջs
void initStack(Stack& s) {
	s.base = new int[MAXSIZE];
	s.top = s.base;
	s.stack_size = MAXSIZE;
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
void push(Stack& s, int e) {
	if (s.top - s.base == s.stack_size) {
		std::cout << "ջ�����������ٲ����µ�ջ��Ԫ��" << std::endl;
		return;
	}
	*s.top = e;
	s.top++;
	s.stack_length++;
}

//ɾ��s��ջ��Ԫ�أ���e������ֵ
void pop(Stack& s, int& e) {
	if (s.top == s.base) {
		std::cout << "ջ�գ�����ִ��pop����" << std::endl;
		return;
	}
	--s.top;
	e = *s.top;
	s.stack_length--;
}

//����s��ջ��Ԫ�أ����޸�ջ��ָ��
int getTop(Stack s) {
	if (s.top != s.base) {
		return *(s.top - 1);
	}
}

//����ջs
void destroyStack(Stack& s) {
	s.top = nullptr;
	delete(s.base);
	s.base = nullptr;
}

//���ջs
void clearStack(Stack& s) {
	s.top = s.base;
	s.stack_length = 0;
}

//��ջsΪ��ջ������true�����򷵻�false
bool stackEmpty(Stack& s) {
	return s.stack_length == 0;
}

//����s��Ԫ�ظ�������ջ�ĳ���
int stackLength(Stack& s) {
	return s.stack_length;
}

//��ջ�׵�ջ�����δ�ӡ��s��ÿ������Ԫ��
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

//initStack //����һ����ջs
//push //����Ԫ��eΪ�µ�ջ��Ԫ��
//pop //ɾ��s��ջ��Ԫ�أ���e������ֵ
//getTop //����s��ջ��Ԫ�أ����޸�ջ��ָ��
//destroyStack //����ջs
//clearStack //���ջs
//stackEmpty //��ջsΪ��ջ������true�����򷵻�false
//stackLength //����s��Ԫ�ظ�������ջ�ĳ���
//stackTraverse //��ջ�׵�ջ�����δ�ӡ��s��ÿ������Ԫ��