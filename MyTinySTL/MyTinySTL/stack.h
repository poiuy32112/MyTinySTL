#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept> // �����쳣����
#include <sstream>
#include <string>

template <typename T, typename Container = std::deque<T>>
class MyStack
{
private:
    Container data; // ʹ�õײ������洢ջ��Ԫ��

public:
    // ѹ��Ԫ�ص�ջ��
    void push(const T& value)
    {
        data.push_back(value);
    }

    // ����ջ��Ԫ��
    void pop()
    {
        if (!empty())
        {
            data.pop_back();
        }
        else
        {
            throw std::runtime_error("Stack is empty.");
        }
    }

    // ����ջ��Ԫ�ص�����
    T& top()
    {
        if (!empty())
        {
            return data.back();
        }
        else
        {
            throw std::runtime_error("Stack is empty.");
        }
    }

    // ���ջ�Ƿ�Ϊ��
    bool empty() const
    {
        return data.empty();
    }

    // ����ջ�Ĵ�С
    size_t size() const
    {
        return data.size();
    }
};

int main()
{
    // ʹ�� std::deque ��Ϊ�ײ�������ʾ��
    MyStack<int, std::deque<int>> stack;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++)
    {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int element;
        if (command == "push")
        {
            iss >> element;
            stack.push(element);
        }
        if (command == "pop")
        {
            try
            {
                stack.pop();
            }
            catch (const std::runtime_error& e)
            {
                // �����κδ���
                continue;
            }
        }
        if (command == "top")
        {
            try
            {
                std::cout << stack.top() << std::endl;
            }
            catch (const std::runtime_error& e)
            {
                std::cout << "null" << std::endl;
            }
        }
        if (command == "size")
        {
            std::cout << stack.size() << std::endl;
        }
        if (command == "empty")
        {
            std::cout << (stack.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}