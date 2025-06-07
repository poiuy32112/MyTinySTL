#include <iostream>
#include <vector>

/* 双向链表节点 */
struct DoublyListNode {
    int val;              // 节点值
    DoublyListNode* next; // 后继节点指针
    DoublyListNode* prev; // 前驱节点指针
    DoublyListNode(int val) : val(val), prev(nullptr), next(nullptr) {
    }
};

/* 基于双向链表实现的双向队列 */
class LinkedListDeque {
private:
    DoublyListNode* front, * rear; // 头节点 front ，尾节点 rear
    int queSize = 0;              // 双向队列的长度

public:
    /* 构造方法 */
    LinkedListDeque() : front(nullptr), rear(nullptr) {
    }

    /* 析构方法 */
    ~LinkedListDeque() {
        // 遍历链表删除节点，释放内存
        DoublyListNode* pre, * cur = front;
        while (cur != nullptr) {
            pre = cur;
            cur = cur->next;
            delete pre;
        }
    }

    /* 获取双向队列的长度 */
    int size() {
        return queSize;
    }

    /* 判断双向队列是否为空 */
    bool isEmpty() {
        return size() == 0;
    }

    /* 入队操作 */
    void push(int num, bool isFront) {
        DoublyListNode* node = new DoublyListNode(num);
        // 若链表为空，则令 front 和 rear 都指向 node
        if (isEmpty())
            front = rear = node;
        // 队首入队操作
        else if (isFront) {
            // 将 node 添加至链表头部
            front->prev = node;
            node->next = front;
            front = node; // 更新头节点
            // 队尾入队操作
        } else {
            // 将 node 添加至链表尾部
            rear->next = node;
            node->prev = rear;
            rear = node; // 更新尾节点
        }
        queSize++; // 更新队列长度
    }

    /* 队首入队 */
    void pushFirst(int num) {
        push(num, true);
    }

    /* 队尾入队 */
    void pushLast(int num) {
        push(num, false);
    }

    /* 出队操作 */
    int pop(bool isFront) {
        if (isEmpty())
            throw std::out_of_range::out_of_range("队列为空");
        int val;
        // 队首出队操作
        if (isFront) {
            val = front->val; // 暂存头节点值
            // 删除头节点
            DoublyListNode* fNext = front->next;
            if (fNext != nullptr) {
                fNext->prev = nullptr;
                front->next = nullptr;
            }
            delete front;
            front = fNext; // 更新头节点
            // 队尾出队操作
        } else {
            val = rear->val; // 暂存尾节点值
            // 删除尾节点
            DoublyListNode* rPrev = rear->prev;
            if (rPrev != nullptr) {
                rPrev->next = nullptr;
                rear->prev = nullptr;
            }
            delete rear;
            rear = rPrev; // 更新尾节点
        }
        queSize--; // 更新队列长度
        return val;
    }

    /* 队首出队 */
    int popFirst() {
        return pop(true);
    }

    /* 队尾出队 */
    int popLast() {
        return pop(false);
    }

    /* 访问队首元素 */
    int peekFirst() {
        if (isEmpty())
            throw std::out_of_range::out_of_range("双向队列为空");
        return front->val;
    }

    /* 访问队尾元素 */
    int peekLast() {
        if (isEmpty())
            throw std::out_of_range::out_of_range("双向队列为空");
        return rear->val;
    }

    /* 返回数组用于打印 */
    void print() {
        DoublyListNode* node = front;
        for (int i = 0; i < size(); i++) {
            std::cout << node->val << " ";
            node = node->next;
        }
        std::cout << '\n';
    }
};

int main() {
    LinkedListDeque deq;
    deq.pushFirst(3);
    deq.pushFirst(-3);
    deq.pushLast(4);
    deq.pushLast(5);
    deq.pushFirst(-4);
    deq.print(); //-4 -3 3 4 5
    std::cout << "-------------------------\n";

    deq.popFirst();
    deq.popLast();
    std::cout << deq.peekFirst() << '\n'; //-3
    std::cout << deq.peekLast() << '\n'; //4
    deq.pushLast(66);
    std::cout << deq.size() << '\n'; //4
    deq.print(); //-3 3 4 66
    return 0;
}


//LinkedListDeque
//int size()
//bool isEmpty()
//void push(int num, bool isFront)
//void pushFirst(int num)
//void pushLast(int num)
//int pop(bool isFront)
//int popFirst()
//int popLast()
//int peekFirst()
//int peekLast()
//void print()


//DNode
//LinkListDeque
//size
//empty
//push_front()
//push_back()
//pop_front()
//pop_back()
//front()
//back()
//print()