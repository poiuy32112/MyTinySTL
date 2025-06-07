#include <iostream>

namespace mystl {

struct DNode {
	int m_val{ 0 };
	DNode* m_next{ nullptr };
	DNode* m_prev{ nullptr };

	DNode(int val) : m_val(val) {}
};

class LinkListDeque {
private:
	DNode* m_front{ nullptr };
	DNode* m_rear{ nullptr };
	int m_size{ 0 };

public:
	LinkListDeque() {}
	~LinkListDeque();

	int size();
	bool empty();

	void push_front(int val);
	void push_back(int val);
	int pop_front();
	int pop_back();
	int front();
	int back();

	void print();
};

LinkListDeque::~LinkListDeque() {
	DNode* cur{ m_front };
	DNode* pre{ nullptr };
	while (cur) {
		pre = cur;
		cur = cur->m_next;
		delete pre;
	}
}

int LinkListDeque::size() {
	return m_size;
}

bool LinkListDeque::empty() {
	return m_size == 0;
}

void LinkListDeque::push_front(int val) {
	DNode* node = new DNode(val);
	if (empty()) {
		m_front = m_rear = node;
	} else {
		node->m_next = m_front;
		m_front->m_prev = node;
		m_front = node;
	}
	m_size++;
}

void LinkListDeque::push_back(int val) {
	DNode* node = new DNode(val);
	if (empty()) {
		m_front = m_rear = node;
	} else {
		node->m_prev = m_rear;
		m_rear->m_next = node;
		m_rear = node;
	}
	m_size++;
}

int LinkListDeque::pop_front() {
	if (empty()) {
		std::cout << "当前deuqe为空，不能执行pop_front()操作" << '\n';
		return 0;
	}
	int ans{ m_front->m_val };
	DNode* f_next = m_front->m_next;
	if (f_next) {
		f_next->m_prev = nullptr;
		m_front->m_next = nullptr;
		m_front = f_next;
	}
	m_size--;
	return ans;
}

int LinkListDeque::pop_back() {
	if (empty()) {
		std::cout << "当前deuqe为空，不能执行pop_back()操作" << '\n';
		return 0;
	}
	int ans{ m_rear->m_val };
	DNode* r_pre = m_rear->m_prev;
	if (r_pre) {
		r_pre->m_next = nullptr;
		m_rear->m_prev = nullptr;
		m_rear = r_pre;
	}
	m_size--;
	return ans;
}

int LinkListDeque::front() {
	if (empty()) {
		std::cout << "当前deuqe为空，不能执行front()操作" << '\n';
		return 0;
	}
	return m_front->m_val;
}

int LinkListDeque::back() {
	if (empty()) {
		std::cout << "当前deuqe为空，不能执行back()操作" << '\n';
		return 0;
	}
	return m_rear->m_val;
}

void LinkListDeque::print() {
	DNode* cur{ m_front };
	for (int i = 0; i < size(); ++i) {
		std::cout << cur->m_val << " ";
		cur = cur->m_next;
	}
	std::cout << '\n';
}

}

int main() {
	mystl::LinkListDeque deq;
	deq.push_front(3);
	deq.push_front(-3);
	deq.push_back(4);
	deq.push_back(5);
	deq.push_front(-4);
	deq.print(); //-4 -3 3 4 5
	std::cout << "-------------------------\n";

	deq.pop_front();
	deq.pop_back();
	std::cout << deq.front() << '\n'; //-3
	std::cout << deq.back() << '\n'; //4
	deq.push_back(66);
	std::cout << deq.size() << '\n'; //4
	deq.print(); //-3 3 4 66
	return 0;
}