#include<iostream>

struct Node {
	int data{ 0 };
	struct Node* next{ nullptr };
};

struct LinkQueue {
	Node* front{ nullptr };
	Node* rear{ nullptr };
	int size{ 0 };
};

void initQueue(LinkQueue& q) {
	q.front = new Node;
	q.rear = q.front;
}

int queueLength(LinkQueue& q) {
	if (q.front == nullptr) {
		std::cout << "队列没有被构造，不能返回元素个数" << std::endl;
		exit(1);
	}
	return q.size;
}

void enQueue(LinkQueue& q, int e) {
	Node* p = new Node;
	p->data = e;
	q.rear->next = p;
	q.rear = p;
	q.size++;
}

void deQueue(LinkQueue& q, int& e) {
	if (q.front == q.rear) {
		std::cout << "队空，不能删除元素" << std::endl;
		return;
	}
	Node* p = q.front->next;
	e = p->data;
	q.front->next = p->next;
	if (p == q.rear) {
		q.rear = q.front;
	}
	delete(p);
	q.size--;
}

int getHead(LinkQueue& q) {
	if (q.front != q.rear) {
		return q.front->next->data;
	}
}

void destroyQueue(LinkQueue& q) {
	Node* p{ nullptr };
	while (q.front) {
		p = q.front;
		q.front = q.front->next;
		delete(p);
	}
}

bool queueEmpty(LinkQueue& q) {
	return q.front == q.rear;
}

void queueTraverse(LinkQueue& q) {
	for (auto it = q.front->next; it != nullptr; it = it->next) {
		std::cout << it->data << " ";
	}
	std::cout << std::endl;
}

int main() {
	LinkQueue que;
	initQueue(que);
	enQueue(que, 1);
	enQueue(que, 2);
	enQueue(que, 3);
	enQueue(que, 4);
	enQueue(que, 5);
	queueTraverse(que); //1 2 3 4 5

	int e{ 0 };
	deQueue(que, e);
	std::cout << e << std::endl; //1
	std::cout << getHead(que) << std::endl; //2
	queueTraverse(que); //2 3 4 5
	std::cout << "-------------------" << std::endl;

	LinkQueue que1;
	initQueue(que1);
	deQueue(que1, e);
	enQueue(que1, 1);
	enQueue(que1, 2);
	std::cout << queueLength(que1) << std::endl; //2
	std::cout << queueEmpty(que1) << std::endl; //false
	deQueue(que1, e);
	deQueue(que1, e);
	std::cout << queueLength(que1) << std::endl; //0
	std::cout << queueEmpty(que1) << std::endl; //true
	std::cout << "-------------------" << std::endl;

	enQueue(que1, 1);
	std::cout << queueLength(que1) << std::endl; //1
	destroyQueue(que1);
	std::cout << queueLength(que1) << std::endl;
	return 0;
}