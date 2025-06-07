#include<iostream>

struct DNode {
	int data{ 0 };
	struct DNode* prev{ nullptr };
	struct DNode* next{ nullptr };
};

using DLinkList = DNode*;

void initList(DLinkList& L) {
	L = new DNode;
}

void pushBack(DLinkList L, int e) {
	DNode* p = L;
	while (p->next) {
		p = p->next;
	}
	p->next = new DNode;
	p->next->prev = p;
	p->next->data = e;
}

void listInsert(DLinkList L, int i, int e) {
	DNode* p = L;
	int j = 0;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || i < 1) {
		std::cout << "listInsert函数中的i值不合法" << std::endl;
		return;
	}

	DNode* s = new DNode;
	s->data = e;
	s->prev = p->prev;
	p->prev->next = s;
	s->next = p;
	p->prev = s;
}

void listDelete(DLinkList L, int i) {
	DNode* p = L;
	int j = 0;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || i < 1) {
		std::cout << "listDelete函数中的i值不合法" << std::endl;
		return;
	}

	p->prev->next = p->next;
	if (p->next) {
		p->next->prev = p->prev;
	}
	delete p;
}

void Print(DLinkList L) {
	DNode* p = L->next;
	while (p) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << std::endl;
}



int main() {
	DNode* head{ nullptr };
	initList(head);
	pushBack(head, 1);
	pushBack(head, 2);
	pushBack(head, 3); //1 2 3
	Print(head);

	listInsert(head, 0, 22);
	listInsert(head, 1, 22);
	listInsert(head, 3, 222); //22 1 222 2 3
	Print(head);

	listDelete(head, 0);
	listDelete(head, 5); //22 1 222 2
	listDelete(head, 2); //22 222 2
	pushBack(head, 3); // 22 222 2 3
	Print(head);

	return 0;
}