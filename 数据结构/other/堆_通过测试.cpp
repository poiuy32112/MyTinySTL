#include <iostream>
#include <vector>

namespace mystl {

class MaxHeap {
private:
    std::vector<int> m_max_heap;

public:
    MaxHeap(std::vector<int> h) {
        m_max_heap = h;
        for (int i = parent(h.size() - 1); i >= 0; --i) {
            siftDown(i);
        }
    }

    int left(int i) {
        return i * 2 + 1;
    }

    int right(int i) {
        return i * 2 + 2;
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    void siftUp(int i) {
        while (true) {
            int p = parent(i);
            if (p < 0 || m_max_heap[i] <= m_max_heap[p]) {
                return;
            }
            std::swap(m_max_heap[i], m_max_heap[p]);
            i = p;
        }
    }

    void siftDown(int i) {
        while (true) {
            int l = left(i), r = right(i), ma = i;
            if (l < size() && m_max_heap[l] > m_max_heap[ma]) {
                ma = l;
            }
            if (r < size() && m_max_heap[r] > m_max_heap[ma]) {
                ma = r;
            }
            if (i == ma) return;
            std::swap(m_max_heap[i], m_max_heap[ma]);
            i = ma;
        }
    }

    int size() {
        return m_max_heap.size();
    }

    bool isEmpty() {
        return size() == 0;
    }

    int peek() {
        return m_max_heap[0];
    }

    void push(int val) {
        m_max_heap.push_back(val);
        siftUp(size() - 1);
    }

    void pop() {
        if (isEmpty()) {
            std::cout << "当前堆为空，不能执行pop()操作" << '\n';
            return;
        }
        std::swap(m_max_heap[0], m_max_heap[size() - 1]);
        m_max_heap.pop_back();
        siftDown(0);
    }
};

}

int main() {
    std::vector<int> vec{ 0, 6, 10, 4, 35, -1,-23, 1, 3, 4 };
    mystl::MaxHeap h(vec);

    std::cout << h.peek() << '\n'; //35
    h.pop();
    std::cout << h.peek() << '\n'; //10
    h.push(100);
    h.push(200);
    std::cout << h.peek() << '\n'; //200
    h.pop();
    std::cout << h.peek() << '\n'; //100
    std::cout << h.size() << '\n'; //10
    std::cout << "--------------------" << '\n';

    h.pop();
    h.pop();
    h.pop();
    std::cout << h.peek() << '\n'; //4

    std::vector<int> vec2{ 0 };
    mystl::MaxHeap h2(vec2);
    h2.push(0);
    h2.pop();
    h2.pop();
    h2.pop();

    return 0;
}