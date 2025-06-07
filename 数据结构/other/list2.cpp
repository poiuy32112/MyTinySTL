#include <iostream>
#include <vector>
#include <list>

namespace mystl {

struct list_node {
	list_node* m_next;
	list_node* m_prev;
	int m_data;

	list_node() : m_next(nullptr), m_prev(nullptr), m_data(0) {}
	list_node(const int& value) : m_next(nullptr), m_prev(nullptr), m_data(value) {}
};

class list {
public:
	using Node = list_node;

private:
	Node* m_head{ nullptr };
	int m_size{ 0 };

public:
	list() {
		m_head = new Node();
		m_head->m_next = m_head;
		m_head->m_prev = m_head;
	}

	list(int n) : list() {
		for (int i = 0; i < n; ++i) {
			push_back(0);
		}
	}

	list(int n, const int& value) : list() {
		for (int i = 0; i < n; ++i) {
			push_back(value);
		}
	}

	list(const list& li) : list() {
		for (auto it = li.m_head->m_next; it != li.m_head; it = it->m_next) {
			push_back(it->m_data);
		}
	}

	list(std::initializer_list<int> init) : list() {
		for (const int& value : init) {
			push_back(value);
		}
	}

	~list() {
		clear();
		delete[] m_head;
		m_head = nullptr;
	}

	//容量相关操作
	bool empty() const { return m_head->m_next == m_head; }
	int size() const { return m_size; }

	//取值相关操作
	int& front() { return m_head->m_next->m_data; }
	int& back() { return m_head->m_prev->m_data; }

	//修改链表操作
	void push_front(int value) { insert(0, value); }
	void push_back(int value) { insert(m_size, value); }
	void clear() {
		Node* cur{ m_head->m_next };
		Node* t{ cur };
		while (cur != m_head) {
			t = t->m_next;
			delete[] cur;
			cur = t;
		}
		m_size = 0;
		m_head->m_next = m_head;
		m_head->m_prev = m_head;
	}
	void pop_front() { erase(0); }
	void pop_back() { erase(m_size - 1); }

	Node* insert(int pos, const int& value) {
		Node* cur{ m_head };
		for (int i = 0; i <= pos; ++i) {
			cur = cur->m_next;
		}
		Node* prev = cur->m_prev;

		Node* new_node = new Node(value);
		new_node->m_prev = prev;
		new_node->m_next = cur;

		prev->m_next = new_node;
		cur->m_prev = new_node;

		m_size++;
		return new_node;
	}

	Node* erase(int pos) {
		Node* t{ m_head };
		for (int i = 0; i <= pos; ++i) {
			t = t->m_next;
		}
		if (t == m_head) return m_head;

		Node* cur = t;
		Node* prev = cur->m_prev;
		Node* next = cur->m_next;

		prev->m_next = next;
		next->m_prev = prev;

		m_size--;
		delete[] cur;

		return next;
	}

	void printList() {
		for (auto it = m_head->m_next; it != m_head; it = it->m_next) {
			std::cout << it->m_data << " ";
		}
		std::cout << '\n';
	}
};

}

int main() {
	mystl::list l{ 0,1,2,3 };
	std::cout << l.size() << '\n'; //4
	l.push_back(44);
	l.push_front(-1);
	l.push_back(55);
	std::cout << l.front() << '\n'; //-1
	std::cout << l.back() << '\n'; //55
	l.printList(); //-1 0 1 2 3 44 55
	std::cout << "----------------------\n";

	l.insert(0, -2); //-2 -1 0 1 2 3 44 55
	l.erase(3); //-2 -1 0 2 3 44 55
	l.insert(7, 66);
	l.printList(); //-2 -1 0 2 3 44 55 66
	std::cout << "----------------------\n";

	l.pop_front();
	l.pop_back();
	l.printList(); //-1 0 2 3 44 55
	std::cout << l.size() << '\n'; //6
	std::cout << "----------------------\n";

	l.clear();
	std::cout << l.size() << '\n'; //0
	std::cout << l.empty() << '\n'; //1

	return 0;
}

//list(int* first, int* last) : list() {
//	for (int* it = first; it != last; ++it) {
//		push_back(*it);
//	}
//	m_size = last - first;
//}

//std::vector<int> vec{ 0,1,2,3,4,5};
//std::list<int> l(vec.begin() + 1, vec.begin() + 4);
//for (auto& i : l) {
//	std::cout << i << " ";
//}