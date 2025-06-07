#include<iostream>

#define MAXQSIZE 5
struct Queue {
	int* base{ nullptr };
	int front{ 0 };
	int rear{ 0 };
};

//构造一个空队列
void initQueue(Queue& Q) {
	Q.base = new int[MAXQSIZE];
}

//返回Q的元素个数
int queueLength(Queue& Q) {
	if (Q.base == nullptr) {
		std::cout << "队列没有被构造，不能返回元素个数" << std::endl;
		exit(1);
	}
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//插入元素e为Q的新的队尾元素
void enQueue(Queue& Q, int e) {
	if ((Q.rear + 1) % MAXQSIZE == Q.front) {
		std::cout << "队列已满，不能再添加新元素" << std::endl;
		return;
	}
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}

//删除Q的队头元素，用e返回其值
void deQueue(Queue& Q, int& e) {
	if (Q.front == Q.rear) {
		std::cout << "队空，不能删除元素" << std::endl;
		return;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}

//返回Q的队头元素，不修改队头指针
int getHead(Queue& Q) {
	if (Q.front != Q.rear) {
		return Q.base[Q.front];
	}
}

//销毁队列Q
void destroyQueue(Queue& Q) {
	delete(Q.base);
	Q.base = nullptr;
}

//清空队列Q
void clearQueue(Queue& Q) {
	Q.front = 0;
	Q.rear = 0;
}

bool queueEmpty(Queue& Q) {
	return Q.front == Q.rear;
}

void queueTraverse(Queue& Q) {
	for (int i = Q.front; i != Q.rear; i = (i + 1) % MAXQSIZE) {
		std::cout << Q.base[i] << " ";
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

//initQueue //构造一个空队列
//queueLength //返回Q的元素个数
//enQueue //插入元素e为Q的新的队尾元素
//deQueue //删除Q的队头元素，用e返回其值
//getHead //返回Q的队头元素，不修改队头指针
//destroyQueue //销毁队列Q
//clearQueue //清空队列Q
//queueEmpty
//queueTraverse


