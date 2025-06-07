#include<iostream>

namespace mystl {

struct LNode {
	int data{ 0 };
	struct LNode* next{ nullptr };
};

using LinkList = LNode*;

void initList(LinkList& L) {
	L = new LNode();
}

void getElem(LinkList L, int i, int& e) {
	LNode* p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (!p || j > i) {
		std::cout << "getElem函数中的i值不合法" << std::endl;
		return;
	}
	e = p->data;
}

LNode* locateElem(LinkList L, int e) {
	LNode* p = L->next;
	while (p && p->data != e) {
		p = p->next;
	}
	if (!p) {
		std::cout << "未找到值为e的元素" << std::endl;
		return nullptr;
	}
	return p;
}

void listInsert(LinkList L, int i, int e) {
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) {
		std::cout << "listInsert函数中的i值不合法" << std::endl;
		return;
	}
	LNode* s = new LNode();
	s->data = e;
	s->next = p->next;
	p->next = s;
}

void listDelete(LinkList L, int i) {
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) {
		std::cout << "listDelete函数中的i值不合法" << std::endl;
		return;
	}
	LNode* q = p->next;
	p->next = q->next;
	delete q;
}

void createListForward(LNode** L, int n) {
	for (int i = 0; i < n; ++i) {
		LNode* p = new LNode();
		std::cin >> p->data;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

void createListBack(LinkList& L, int n) {
	L = new LNode();
	LNode* r = L;
	for (int i = 0; i < n; ++i) {
		LNode* p = new LNode();
		std::cin >> p->data;
		r->next = p;
		r = p;
	}
}

void Print(LinkList L) {
	LNode* p = L->next;
	while (p) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

}

int main() {
	mystl::LNode* head{ nullptr };
	initList(head);
	createListForward(&head, 3); //输入1 2 3
	Print(head);
	int e{ 0 };
	getElem(head, 6, e);
	getElem(head, 3, e);

	mystl::LNode* p{ nullptr };
	e = -1;
	p = locateElem(head, e);
	e = 2;
	p = locateElem(head, e);
	std::cout << p->data << std::endl;

	e = 333;
	listInsert(head, 0, e);
	listInsert(head, 1, e);
	Print(head);

	listDelete(head, 7);
	listDelete(head, 1);
	Print(head);

	mystl::LNode* head1{ nullptr };
	createListBack(head1, 3); //输入1 2 3
	Print(head1);
	return 0;
}