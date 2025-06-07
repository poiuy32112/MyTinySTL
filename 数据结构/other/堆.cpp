#include <iostream>
#include <vector>

namespace mystl {

/* �󶥶� */
class MaxHeap {
private:
    // ʹ�ö�̬���飬�������뿼����������
    std::vector<int> m_max_heap;

    /* ��ȡ���ӽڵ������ */
    int left(int i) {
        return 2 * i + 1;
    }

    /* ��ȡ���ӽڵ������ */
    int right(int i) {
        return 2 * i + 2;
    }

    /* ��ȡ���ڵ������ */
    int parent(int i) {
        return (i - 1) / 2; // ��������
    }

    /* �ӽڵ� i ��ʼ���ӵ������ѻ� */
    void siftUp(int i) {
        while (true) {
            // ��ȡ�ڵ� i �ĸ��ڵ�
            int p = parent(i);
            // ����Խ�����ڵ㡱�򡰽ڵ������޸���ʱ�������ѻ�
            if (p < 0 || m_max_heap[i] <= m_max_heap[p])
                break;
            // �������ڵ�
            std::swap(m_max_heap[i], m_max_heap[p]);
            // ѭ�����϶ѻ�
            i = p;
        }
    }

    /* �ӽڵ� i ��ʼ���Ӷ����׶ѻ� */
    void siftDown(int i) {
        while (true) {
            // �жϽڵ� i, l, r ��ֵ���Ľڵ㣬��Ϊ ma
            int l = left(i), r = right(i), ma = i;
            if (l < size() && m_max_heap[l] > m_max_heap[ma])
                ma = l;
            if (r < size() && m_max_heap[r] > m_max_heap[ma])
                ma = r;
            // ���ڵ� i �������� l, r Խ�磬����������ѻ�������
            if (ma == i)
                break;
            std::swap(m_max_heap[i], m_max_heap[ma]);
            // ѭ�����¶ѻ�
            i = ma;
        }
    }

public:
    /* ���췽�������������б��� */
    MaxHeap(std::vector<int> nums) {
        // ���б�Ԫ��ԭ�ⲻ����ӽ���
        m_max_heap = nums;
        // �ѻ���Ҷ�ڵ�������������нڵ�
        for (int i = parent(size() - 1); i >= 0; i--) {
            siftDown(i);
        }
    }

    /* ��ȡ�Ѵ�С */
    int size() {
        return m_max_heap.size();
    }

    /* �ж϶��Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ���ʶѶ�Ԫ�� */
    int peek() {
        return m_max_heap[0];
    }

    /* Ԫ����� */
    void push(int val) {
        // ��ӽڵ�
        m_max_heap.push_back(val);
        // �ӵ������ѻ�
        siftUp(size() - 1);
    }

    /* Ԫ�س��� */
    void pop() {
        // �пմ���
        if (isEmpty()) {
            std::cout << "�Ѵ�ʱΪ�գ�����ִ��pop()����" << '\n';
            return;
        }
        // �������ڵ�������Ҷ�ڵ㣨������Ԫ����βԪ�أ�
        std::swap(m_max_heap[0], m_max_heap[size() - 1]);
        // ɾ���ڵ�
        m_max_heap.pop_back();
        // �Ӷ����׶ѻ�
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

//siftUp
//siftDown
//MaxHeap //���캯��
//size
//isEmpty
//peek
//push
//pop