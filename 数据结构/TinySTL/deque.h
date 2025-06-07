#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Deque
{
private:
    T* elements;  // ����һ��ѭ��һά����
    size_t capacity;  // �����������
    size_t frontIndex;  // deque��ǰ������
    size_t backIndex;  // deque�ĺ������
    size_t size;  // deque�е�Ԫ������

public:
    // ���캯��
    Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}

    // ��������
    ~Deque()
    {
        clear();
        delete[] elements;
    }

    // ��deque��ǰ�˲���Ԫ��
    void push_front(const T& value)
    {
        // ����Ƿ���Ҫ��չ��������
        if (size == capacity)
        {
            resize();
        }

        // �����µ�ǰ������
        frontIndex = (frontIndex - 1 + capacity) % capacity;

        // ���µ�ǰ��λ�ò���Ԫ��
        elements[frontIndex] = value;

        // ����deque��Ԫ������
        ++size;
    }

    // ��deque�ĺ�˲���Ԫ��
    void push_back(const T& value)
    {
        // ����Ƿ���Ҫ��չ��������
        if (size == capacity)
        {
            resize();
        }

        // �ڵ�ǰ���λ�ò���Ԫ��
        elements[backIndex] = value;

        // �����µĺ������
        backIndex = (backIndex + 1) % capacity;

        // ����deque��Ԫ������
        ++size;
    }

    // ��deque��ǰ���Ƴ�Ԫ��
    void pop_front()
    {
        // ���deque�Ƿ�Ϊ��
        if (size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }

        // ɾ��Ԫ�ز���Ҫ��ʽ��ɾ��, �Ժ���׷��Ԫ�ػ��Զ�����
        // �����µ�ǰ������
        frontIndex = (frontIndex + 1) % capacity;

        // ����deque��Ԫ������
        --size;
    }

    // ��deque�ĺ���Ƴ�Ԫ��
    void pop_back()
    {
        // ���deque�Ƿ�Ϊ��
        if (size == 0)
        {
            throw std::out_of_range("Deque is empty");
        }

        // ɾ��Ԫ�ز���Ҫ��ʽ��ɾ��, �Ժ���׷��Ԫ�ػ��Զ�����
        // �����µĺ������
        backIndex = (backIndex - 1 + capacity) % capacity;

        // ����deque��Ԫ������
        --size;
    }
    // �������Ԫ��
    T& operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return elements[(frontIndex + index) % capacity];
    }

    // ��ȡdeque�е�Ԫ������
    size_t getSize() const
    {
        return size;
    }

    // ���deque
    void clear()
    {
        while (size > 0)
        {
            pop_front();
        }
    }

    // ��ӡdeque�е�Ԫ��
    void printElements() const
    {
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }

private:
    // ��չ��������
    void resize()
    {
        // �����µ�����
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;

        // �����µ�����
        T* newElements = new T[newCapacity];

        // ����Ԫ�ص�������
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i)
        {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        // �ͷž�������ڴ�
        delete[] elements;

        // ���³�Ա����
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
};

int main()
{
    // ����һ�� Deque ����
    Deque<int> myDeque;

    int N;
    std::cin >> N;
    // ���߻س�
    getchar();
    std::string line;
    // ��������
    for (int i = 0; i < N; i++)
    {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back")
        {
            iss >> value;
            myDeque.push_back(value);
        }

        if (command == "push_front")
        {
            iss >> value;
            myDeque.push_front(value);
        }

        if (command == "pop_back")
        {
            if (myDeque.getSize() == 0)
            {
                continue;
            }
            myDeque.pop_back();
        }

        if (command == "pop_front")
        {
            if (myDeque.getSize() == 0)
            {
                continue;
            }
            myDeque.pop_front();
        }

        if (command == "clear")
        {
            myDeque.clear();
        }

        if (command == "size")
        {
            std::cout << myDeque.getSize() << std::endl;
        }

        if (command == "get")
        {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        }

        if (command == "print")
        {
            if (myDeque.getSize() == 0)
            {
                std::cout << "empty" << std::endl;
            }
            else
            {
                myDeque.printElements();
            }
        }
    }
    return 0;
}