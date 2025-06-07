#include <iostream>

namespace mystl {

struct list_node {
	list_node* m_next{ nullptr };
	list_node* m_prev{ nullptr };
	int m_data{ 0 };

	list_node() : m_next(nullptr), m_prev(nullptr), m_data(0) {}
	list_node(const int& value) : m_next(nullptr), m_prev(nullptr), m_data(value) {}
};

struct list_iterator {
	using iterator = list_iterator;

	using Node = list_node;

	Node* m_node{ nullptr };

	list_iterator() {}
	list_iterator(Node* x) : m_node(x) {}
	list_iterator(const iterator& x) : m_node(x.m_node) {}

	bool operator==(const iterator& rhs) const { return m_node == rhs.m_node; }
	bool operator!=(const iterator& rhs) const { return !(m_node == rhs.m_node); }
	int& operator*() { return (*m_node).m_data; }
	int* operator->() { return &(operator*()); }
	iterator& operator++() {
		m_node = (*m_node).m_next;
		return *this;
	}
	iterator operator++(int) {
		iterator tmp = *this;
		++*this;
		return tmp;
	}
	iterator& operator--() {
		m_node = (*m_node).m_prev;
		return *this;
	}
	iterator& operator--(int) {
		iterator tmp = *this;
		--*this;
		return tmp;
	}
};

class list {
public:
	using iterator = list_iterator;

	using Node = list_node;

private:
	Node* m_head{ nullptr };
	int m_size{ 0 };

public:
	//构造和析构函数
	list();
	list(int n);
	list(int n, const int& value);
	list(const list& li);
	list(std::initializer_list<int> init);
	~list() {
		clear();
		delete[] m_head;
		m_head = nullptr;
	}

	//迭代器相关操作
	iterator begin() noexcept { return iterator(m_head->m_next); }
	const iterator begin() const noexcept { return iterator(m_head->m_next); }
	iterator end() noexcept { return iterator(m_head); }
	const iterator end() const noexcept { return iterator(m_head); }

	//容量相关操作
	bool empty() const { return begin() == end(); }
	int size() const { return m_size; }

	//取值相关操作
	int& front() { return m_head->m_next->m_data; }
	int& back() { return m_head->m_prev->m_data; }

	//修改链表操作
	void push_front(int value) { insert(begin(), value); }
	void push_back(int value) { insert(end(), value); }
	void clear();
	void pop_front() { erase(begin()); }
	void pop_back() { erase(--end()); }
	iterator insert(iterator pos, const int& value);
	iterator erase(iterator pos);

	//打印
	void printList();
};

list::list() {
	m_head = new Node();
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}

list::list(int n) : list() {
	for (int i = 0; i < n; ++i) {
		push_back(0);
	}
}

list::list(int n, const int& value) : list() {
	for (int i = 0; i < n; ++i) {
		push_back(value);
	}
}

list::list(const list& li) : list() {
	for (int& i : li) {
		push_back(i);
	}
}

list::list(std::initializer_list<int> init) : list() {
	for (const int& value : init) {
		push_back(value);
	}
}

list_iterator list::insert(iterator pos, const int& value) {
	Node* cur{ pos.m_node };
	Node* prev = cur->m_prev;

	Node* new_node = new Node(value);
	new_node->m_prev = prev;
	new_node->m_next = cur;

	prev->m_next = new_node;
	cur->m_prev = new_node;

	m_size++;
	return new_node;
}

list_iterator list::erase(iterator pos) {
	if (pos == end()) return end();

	Node* cur = pos.m_node;
	Node* prev = cur->m_prev;
	Node* next = cur->m_next;

	prev->m_next = next;
	next->m_prev = prev;

	m_size--;
	delete[] cur;

	return next;
}

void list::clear() {
	Node* cur{ begin().m_node };
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

void list::printList() {
	for (auto it = begin(); it != end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << '\n';
}

} // namespace mystl

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

	l.insert(l.begin(), -2); //-2 -1 0 1 2 3 44 55
	auto it = l.begin();
	it++, it++, it++;
	l.erase(it); //-2 -1 0 2 3 44 55
	l.insert(l.end(), 66);
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