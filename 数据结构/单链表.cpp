#include<iostream>

struct LNode {
	int data{ 0 };
	struct LNode* next{ nullptr };
};

using LinkList = LNode*;

void initList(LinkList& L) { //��ʼ��
	L = new LNode;
	L->next = nullptr;
}

//�ڴ�ͷ�ڵ�ĵ�����L�и������i���Ԫ�ص�ֵ����e����L�е�i������Ԫ�ص�ֵ
void getElem(LinkList L, int i, int& e) {
	LNode* p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) {
		std::cout << "getElem�����е�iֵ���Ϸ�" << std::endl;
		return;
	}
	e = p->data;
}

//�ڴ�ͷ�ڵ�ĵ�����L�в���ֵΪe��Ԫ��
LNode* locateElem(LinkList L, int e) {
	LNode* p = L->next;
	while (p && p->data != e) {
		p = p->next;
	}
	if (p == nullptr) {
		std::cout << "δ�ҵ�ֵΪe��Ԫ��" << std::endl;
		return nullptr;
	}
	return p;
}

//�ڴ�ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
void listInsert(LinkList& L, int i, int e) {
	LNode* p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p || j > i - 1) {
		std::cout << "listInsert�����е�iֵ���Ϸ�" << std::endl;
		return;
	}
	LNode* s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
}

//�ڴ�ͷ���ĵ�����L�У�ɾ����i��Ԫ��
void listDelete(LinkList& L, int i) {
	LNode* p = L;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		j++;
	}
	if (!p->next || j > i - 1) {
		std::cout << "listDelete�����е�iֵ���Ϸ�" << std::endl;
		return;
	}
	LNode* q = p->next;
	p->next = q->next;
	delete q;
}

//ǰ�巨������������λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
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

//��巨������������λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
void createListBack(LinkList& L, int n) {
	L = new LNode;
	L->next = nullptr;
	LNode* r = L; //βָ��rָ��ͷ���
	for (int i = 0; i < n; ++i) {
		LNode* p = new LNode;
		std::cin >> p->data;
		p->next = nullptr;
		r->next = p;
		r = p;
	}
}

//��ӡԪ��ֵ
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
	createListForward(&head, 3); //����1 2 3
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
	createListBack(head1, 3); //����1 2 3
	Print(head1);
	return 0;
}

//initList //��ʼ��
//getElem //�ڴ�ͷ�ڵ�ĵ�����L�и������i���Ԫ�ص�ֵ����e����L�е�i������Ԫ�ص�ֵ
//locateElem //�ڴ�ͷ�ڵ�ĵ�����L�в���ֵΪe��Ԫ��
//listInsert //�ڴ�ͷ���ĵ�����L�е�i��λ�ò���ֵΪe���½��
//listDelete //�ڴ�ͷ���ĵ�����L�У�ɾ����i��Ԫ��
//createListForward //ǰ�巨������������λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
//createListBack //��巨������������λ������n��Ԫ�ص�ֵ��������ͷ���ĵ�����L
//Print //��ӡԪ��ֵ