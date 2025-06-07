#include <iostream>
#include <vector>

/* ˫������ڵ� */
struct DoublyListNode {
    int val;              // �ڵ�ֵ
    DoublyListNode* next; // ��̽ڵ�ָ��
    DoublyListNode* prev; // ǰ���ڵ�ָ��
    DoublyListNode(int val) : val(val), prev(nullptr), next(nullptr) {
    }
};

/* ����˫������ʵ�ֵ�˫����� */
class LinkedListDeque {
private:
    DoublyListNode* front, * rear; // ͷ�ڵ� front ��β�ڵ� rear
    int queSize = 0;              // ˫����еĳ���

public:
    /* ���췽�� */
    LinkedListDeque() : front(nullptr), rear(nullptr) {
    }

    /* �������� */
    ~LinkedListDeque() {
        // ��������ɾ���ڵ㣬�ͷ��ڴ�
        DoublyListNode* pre, * cur = front;
        while (cur != nullptr) {
            pre = cur;
            cur = cur->next;
            delete pre;
        }
    }

    /* ��ȡ˫����еĳ��� */
    int size() {
        return queSize;
    }

    /* �ж�˫������Ƿ�Ϊ�� */
    bool isEmpty() {
        return size() == 0;
    }

    /* ��Ӳ��� */
    void push(int num, bool isFront) {
        DoublyListNode* node = new DoublyListNode(num);
        // ������Ϊ�գ����� front �� rear ��ָ�� node
        if (isEmpty())
            front = rear = node;
        // ������Ӳ���
        else if (isFront) {
            // �� node ���������ͷ��
            front->prev = node;
            node->next = front;
            front = node; // ����ͷ�ڵ�
            // ��β��Ӳ���
        } else {
            // �� node ���������β��
            rear->next = node;
            node->prev = rear;
            rear = node; // ����β�ڵ�
        }
        queSize++; // ���¶��г���
    }

    /* ������� */
    void pushFirst(int num) {
        push(num, true);
    }

    /* ��β��� */
    void pushLast(int num) {
        push(num, false);
    }

    /* ���Ӳ��� */
    int pop(bool isFront) {
        if (isEmpty())
            throw std::out_of_range::out_of_range("����Ϊ��");
        int val;
        // ���׳��Ӳ���
        if (isFront) {
            val = front->val; // �ݴ�ͷ�ڵ�ֵ
            // ɾ��ͷ�ڵ�
            DoublyListNode* fNext = front->next;
            if (fNext != nullptr) {
                fNext->prev = nullptr;
                front->next = nullptr;
            }
            delete front;
            front = fNext; // ����ͷ�ڵ�
            // ��β���Ӳ���
        } else {
            val = rear->val; // �ݴ�β�ڵ�ֵ
            // ɾ��β�ڵ�
            DoublyListNode* rPrev = rear->prev;
            if (rPrev != nullptr) {
                rPrev->next = nullptr;
                rear->prev = nullptr;
            }
            delete rear;
            rear = rPrev; // ����β�ڵ�
        }
        queSize--; // ���¶��г���
        return val;
    }

    /* ���׳��� */
    int popFirst() {
        return pop(true);
    }

    /* ��β���� */
    int popLast() {
        return pop(false);
    }

    /* ���ʶ���Ԫ�� */
    int peekFirst() {
        if (isEmpty())
            throw std::out_of_range::out_of_range("˫�����Ϊ��");
        return front->val;
    }

    /* ���ʶ�βԪ�� */
    int peekLast() {
        if (isEmpty())
            throw std::out_of_range::out_of_range("˫�����Ϊ��");
        return rear->val;
    }

    /* �����������ڴ�ӡ */
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