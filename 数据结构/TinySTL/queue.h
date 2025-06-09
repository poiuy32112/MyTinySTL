#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <stdexcept> // �����쳣����
#include <sstream>
#include <string>

template <typename T, typename Container = std::deque<T>>
class MyQueue
{
private:
    Container data; // ʹ�õײ������洢���е�Ԫ��

public:
    // ��Ԫ����ӵ���β
    void push(const T& value)
    {
        data.push_back(value);
    }

    // �Ƴ���ͷԪ��
    void pop()
    {
        if (!empty())
        {
            data.pop_front();
        }
        else
        {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // ���ʶ�ͷԪ�ص�����
    T& front()
    {
        if (!empty())
        {
            return data.front();
        }
        else
        {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // ���ʶ�βԪ�ص�����
    T& back()
    {
        if (!empty())
        {
            return data.back();
        }
        else
        {
            throw std::runtime_error("Queue is empty.");
        }
    }

    // �������Ƿ�Ϊ��
    bool empty() const
    {
        return data.empty();
    }

    // ���ض��еĴ�С
    size_t size() const
    {
        return data.size();
    }
};

int main()
{
    // ʹ�� std::deque ��Ϊ�ײ�������ʾ��
    MyQueue<int, std::deque<int>> myQueue;

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
            myQueue.push(element);
        }

        if (command == "pop")
        {
            try
            {
                myQueue.pop();
            }
            catch (const std::runtime_error& e)
            {
                // �����κδ���
                continue;
            }
        }

        if (command == "front")
        {
            try
            {
                std::cout << myQueue.front() << std::endl;
            }
            catch (const std::runtime_error& e)
            {
                std::cout << "null" << std::endl;
            }
        }

        if (command == "back")
        {
            try
            {
                std::cout << myQueue.back() << std::endl;
            }
            catch (const std::runtime_error& e)
            {
                std::cout << "null" << std::endl;
            }
        }

        if (command == "size")
        {
            std::cout << myQueue.size() << std::endl;
        }

        if (command == "empty")
        {
            std::cout << (myQueue.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}