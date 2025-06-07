#include<iostream>

struct LNode {
	int data{ 0 };
	struct LNode* next{ nullptr };
};

using LinkList = LNode*;

void initList(LinkList& L) { //初始化
	L = new LNode;
	L->next = nullptr;
}

//在带头节点的单链表L中根据序号i获得元素的值，用e返回L中第i个数据元素的值
void getElem(LinkList L, int i, int& e) {
	LNode* p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {
		std::cout << "getElem函数中的i值不合法" << std::endl;
		return;
	}
	e = p->data;
}

//在带头节点的单链表L中查找值为e的元素
LNode* locateElem(LinkList L, int e) {
	LNode* p = L->next;
	while (p && p->data != e) {
		p = p->next;
	}
	if (p == nullptr) {
		std::cout << "未找到值为e的元素" << std::endl;
		return nullptr;
	}
	return p;
}

//在带头结点的单链表L中第i个位置插入值为e的新结点
void listInsert(LinkList& L, int i, int e) {
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
	LNode* s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
}

//在带头结点的单链表L中，删除第i个元素
void listDelete(LinkList& L, int i) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1) {
		std::cout << "listDelete函数中的i值不合法" << std::endl;
		return;
	}
	LNode* q = p->next;
	p->next = q->next;
	delete q;
}

//前插法创建单链表，逆位序输入n个元素的值，建立带头结点的单链表L
void createListForward(LNode** L, int n) {
	*L = new LNode;
	(*L)->next = nullptr;
	for (int i = 0; i < n; ++i) {
		LNode* p = new LNode;
		std::cin >> p->data;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//后插法创建单链表，正位序输入n个元素的值，建立带头结点的单链表L
void createListBack(LinkList& L, int n) {
	L = new LNode;
	L->next = nullptr;
	LNode* r = L; //尾指针r指向头结点
	for (int i = 0; i < n; ++i) {
		LNode* p = new LNode;
		std::cin >> p->data;
		p->next = nullptr;
		r->next = p;
		r = p;
	}
}

//打印元素值
void Print(LinkList L) {
	LNode* p = L->next;
	while (p) {
		std::cout << p->data << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

int main() {
	LNode* head{ nullptr };
	initList(head);
	createListForward(&head, 3); //输入1 2 3
	Print(head);
	int e{ 0 };
	getElem(head, 6, e);
	getElem(head, 3, e);

	LNode* p{ nullptr };
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

	LNode* head1{ nullptr };
	createListBack(head1, 3); //输入1 2 3
	Print(head1);
	return 0;
}

//initList //初始化
//getElem //在带头节点的单链表L中根据序号i获得元素的值，用e返回L中第i个数据元素的值
//locateElem //在带头节点的单链表L中查找值为e的元素
//listInsert //在带头结点的单链表L中第i个位置插入值为e的新结点
//listDelete //在带头结点的单链表L中，删除第i个元素
//createListForward //前插法创建单链表，逆位序输入n个元素的值，建立带头结点的单链表L
//createListBack //后插法创建单链表，正位序输入n个元素的值，建立带头结点的单链表L
//Print //打印元素值