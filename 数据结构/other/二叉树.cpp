#include<iostream>
#include <queue>

struct BiNode {
	int val{ 0 };
	struct BiNode* left{ nullptr };
	struct BiNode* right{ nullptr };

	BiNode(int val) : val(val) {}
};

struct BinaryTree {
	BiNode* root{ nullptr };
	int size{ 0 };
};

void initBiTree(BinaryTree& t) {
	t.root = new BiNode(0);
	t.size = 1;
}

//?
void destroyBiNode(BiNode* root) {
	if (root == nullptr) return;
	destroyBiNode(root->left);
	destroyBiNode(root->right);
	delete(root);
}

void destroyBiTree(BinaryTree& t) {
	BiNode* root = t.root;
	destroyBiNode(root);
	t.root = nullptr;
	t.size = 0;
}

bool BiTreeEmpty(BinaryTree& t) {
	return t.size == 0;
}

//��������������
int BiTreeDepth(BiNode* root) {
	if (root == nullptr) return 0;
	int a = BiTreeDepth(root->left);
	int b = BiTreeDepth(root->right);
	return std::max(a, b) + 1;
}

//��������t���ڣ�����t�ĸ�
BiNode* returnRoot(BinaryTree& t) {
	if (t.root) return t.root;
}

//��������t���ڣ�e��t�е�ĳ����㣬�򷵻�e��ֵ
int rootVal(BinaryTree& t, BiNode* e) {
	return e->val;
}

//��������t���ڣ�e��t�е�ĳ����㣬����e��ֵΪvalue
void assign(BinaryTree& t, BiNode* e, int value) {
	e->val = value;
}

BiNode* parentFind(BiNode* root, BiNode* e) {
	if (!root) return nullptr;
	if (root->left == e || root->right == e) return root;
	BiNode* l = parentFind(root->left, e);
	if (l) return l;
	BiNode* r = parentFind(root->right, e);
	if (r) return r;
	return nullptr;
}

//��������t���ڣ�e��t�е�ĳ����㣬��e��t�ķǸ���㣬�򷵻�����˫�ף����򷵻� ���ա�
BiNode* parent(BinaryTree& t, BiNode* e) {
	if (e == t.root) return nullptr;
	return parentFind(t.root, e);
}

//����e�����ֵܡ���e��t�����ӻ������ֵܣ��򷵻� ���ա�
BiNode* leftBrother(BinaryTree& t, BiNode* e) {
	BiNode* p = parent(t, e);
	if (!p || e == p->left || !p->left) return nullptr;
	return p->left;
}

//����e�����ֵܡ���e��t���Һ��ӻ������ֵܣ��򷵻� ���ա�
BiNode* rightBrother(BinaryTree& t, BiNode* e) {
	BiNode* p = parent(t, e);
	if (!p || e == p->right || !p->right) return nullptr;
	return p->right;
}

//����lrΪ0��1, ɾ��t��p��ָ���������������
void deleteChild(BinaryTree& t, BiNode* p, int lr) {
	if (lr == 0) {
		BiNode* a = p->left;
		p->left = nullptr;
		destroyBiNode(a);
	} else {
		BiNode* a = p->right;
		p->right = nullptr;
		destroyBiNode(a);
	}
}

//ǰ�������ӡ����Ԫ��
void preTraversal(BiNode* root) {
	if (!root) return;
	std::cout << root->val << " ";
	preTraversal(root->left);
	preTraversal(root->right);
}

//�������t, ��ÿ��������һ�Ρ�
void levelOrderTraverse(BinaryTree& t) {
	std::queue<BiNode*> que;
	que.push(t.root);
	while (!que.empty()) {
		int size = que.size();
		for (int i = 0; i < size; ++i) {
			BiNode* p = que.front();
			std::cout << p->val << " ";
			que.pop();
			if (p->left) que.push(p->left);
			if (p->right) que.push(p->right);
		}
	}
}

int main() {
	BinaryTree t;
	initBiTree(t);
	t.root->left = new BiNode(2);
	t.root->right = new BiNode(3);
	t.root->left->left = new BiNode(4);
	t.root->left->right = new BiNode(5);
	t.root->right->left = new BiNode(6);
	t.size = 6;
	//			 0
	//		2		  3
	//	4	   5   6

	preTraversal(t.root); //0 2 4 5 3 6
	std::cout << std::endl;
	levelOrderTraverse(t); //0 2 3 4 5 6
	std::cout << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << BiTreeDepth(t.root) << std::endl; //3
	std::cout << returnRoot(t)->val << std::endl; //0
	std::cout << rootVal(t, t.root) << std::endl; //0
	assign(t, t.root->left, 222);
	preTraversal(t.root); //0 222 4 5 3 6
	std::cout << std::endl;
	std::cout << "-------------------" << std::endl;

	std::cout << parent(t, t.root->left->right)->val << std::endl; //222
	std::cout << leftBrother(t, t.root->left->right)->val << std::endl; //4
	std::cout << rightBrother(t, t.root->left->left)->val << std::endl; //5
	deleteChild(t, t.root, 0);
	preTraversal(t.root); //0 3 6
	std::cout << std::endl;

	destroyBiTree(t);
	preTraversal(t.root);
	return 0;
}

//BiTreeDepth(BiNode* root)
//BiNode* returnRoot(BinaryTree& t)
//int rootVal(BinaryTree& t, BiNode* e)
//void assign(BinaryTree& t, BiNode* e, int value)
//BiNode* parent(BinaryTree& t, BiNode* e)
//BiNode* leftBrother(BinaryTree& t, BiNode* e)
//BiNode* rightBrother(BinaryTree& t, BiNode* e)
//void deleteChild(BinaryTree& t, BiNode* p, int lr)
//void preTraversal(BiNode* root)
//void levelOrderTraverse(BinaryTree& t)