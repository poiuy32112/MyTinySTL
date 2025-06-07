#include <iostream>
#include <vector>

namespace mystl {

/* 大顶堆 */
class MaxHeap {
private:
    // 使用动态数组，这样无须考虑扩容问题
    std::vector<int> m_max_heap;

    /* 获取左子节点的索引 */
    int left(int i) {
        return 2 * i + 1;
    }

    /* 获取右子节点的索引 */
    int right(int i) {
        return 2 * i + 2;
    }

    /* 获取父节点的索引 */
    int parent(int i) {
        return (i - 1) / 2; // 向下整除
    }

    /* 从节点 i 开始，从底至顶堆化 */
    void siftUp(int i) {
        while (true) {
            // 获取节点 i 的父节点
            int p = parent(i);
            // 当“越过根节点”或“节点无须修复”时，结束堆化
            if (p < 0 || m_max_heap[i] <= m_max_heap[p])
                break;
            // 交换两节点
            std::swap(m_max_heap[i], m_max_heap[p]);
            // 循环向上堆化
            i = p;
        }
    }

    /* 从节点 i 开始，从顶至底堆化 */
    void siftDown(int i) {
        while (true) {
            // 判断节点 i, l, r 中值最大的节点，记为 ma
            int l = left(i), r = right(i), ma = i;
            if (l < size() && m_max_heap[l] > m_max_heap[ma])
                ma = l;
            if (r < size() && m_max_heap[r] > m_max_heap[ma])
                ma = r;
            // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
            if (ma == i)
                break;
            std::swap(m_max_heap[i], m_max_heap[ma]);
            // 循环向下堆化
            i = ma;
        }
    }

public:
    /* 构造方法，根据输入列表建堆 */
    MaxHeap(std::vector<int> nums) {
        // 将列表元素原封不动添加进堆
        m_max_heap = nums;
        // 堆化除叶节点以外的其他所有节点
        for (int i = parent(size() - 1); i >= 0; i--) {
            siftDown(i);
        }
    }

    /* 获取堆大小 */
    int size() {
        return m_max_heap.size();
    }

    /* 判断堆是否为空 */
    bool isEmpty() {
        return size() == 0;
    }

    /* 访问堆顶元素 */
    int peek() {
        return m_max_heap[0];
    }

    /* 元素入堆 */
    void push(int val) {
        // 添加节点
        m_max_heap.push_back(val);
        // 从底至顶堆化
        siftUp(size() - 1);
    }

    /* 元素出堆 */
    void pop() {
        // 判空处理
        if (isEmpty()) {
            std::cout << "堆此时为空，不能执行pop()操作" << '\n';
            return;
        }
        // 交换根节点与最右叶节点（交换首元素与尾元素）
        std::swap(m_max_heap[0], m_max_heap[size() - 1]);
        // 删除节点
        m_max_heap.pop_back();
        // 从顶至底堆化
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
//MaxHeap //构造函数
//size
//isEmpty
//peek
//push
//pop