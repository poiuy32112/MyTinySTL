#include<iostream>

#define MAXSIZE 5
struct Queue {
	int* base{ nullptr };
	int front{ 0 };
	int rear{ 0 };
};

void initQueue(Queue& q) {
	q.base = new int[MAXSIZE];
}

int queueLength(Queue& q) {
	if (q.base == nullptr) {
		std::cout << "队列没有被构造，不能返回元素个数" << std::endl;
		exit(1);
	}
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

void enQueue(Queue& q, int e) {
	if ((q.rear + 1) % MAXSIZE == q.front) {
		std::cout << "队列已满，不能添加新元素" << std::endl;
		return;
	}
	q.base[q.rear] = e;
	q.rear = (q.rear + 1) % MAXSIZE;
}

void deQueue(Queue& q, int& e) {
	if (q.rear == q.front) {
		std::cout << "队空，不能删除元素" << std::endl;
		return;
	}
	e = q.base[q.front];
	q.front = (q.front + 1) % MAXSIZE;
}

int getHead(Queue& q) {
	if (q.rear != q.front) {
		return q.base[q.front];
	}
}

void destroyQueue(Queue& q) {
	delete(q.base);
	q.base = nullptr;
}

void clearQueue(Queue& q) {
	q.front = 0;
	q.rear = 0;
}

bool queueEmpty(Queue& q) {
	return q.front == q.rear;
}

void queueTraverse(Queue& q) {
	for (int i = q.front; i != q.rear; i = (i + 1) % MAXSIZE) {
		std::cout << q.base[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	Queue que;
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

	clearQueue(que);
	deQueue(que, e);
	std::cout << "-------------------" << std::endl;

	Queue que1;
	initQueue(que1);
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
	std::cout << queueLength(que1) << std::endl; //0
	return 0;
}