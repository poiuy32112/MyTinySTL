#include "rb_tree.h" // ֮ǰʵ�ֵĺ����
#include <cstddef>
#include <iostream>
#include <list>

template <typename Key, typename Value> class MultiMap
{
public:
    using ValueType = std::list<Value>; // �޸�Value������Ϊlist

    MultiMap() : rbTree(), size(0) {}

    void insert(const Key& key, const Value& value)
    {
        // ���ҵ�ǰ���Ƿ��Ѿ�����
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            // ������Ѿ����ڣ���ֵ��ӵ���Ӧ��list��
            existingValues->push_back(value);
        }
        else
        {
            // ����������ڣ�����һ���µ�list�����ֵ��Ȼ����뵽�������
            ValueType values;
            values.push_back(value);
            rbTree.insert(key, values);
        }
        size++;
    }

    void remove(const Key& key)
    {
        // ɾ�������������������е�ֵ
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            size -= existingValues->size();
            rbTree.remove(key);
        }
    }

    void remove(const Key& key, const Value& value)
    {
        // ���ҵ�ǰ��
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            // ɾ��������ֵ
            existingValues->remove(value);
            size--;
            // ���ɾ��ֵ��listΪ�գ�Ҳɾ����
            if (existingValues->empty())
            {
                rbTree.remove(key);
            }
        }
    }

    ValueType* at(const Key& key)
    {
        // ��ȡ����Ӧ������ֵ���б�
        return rbTree.at(key);
    }

    int getSize() { return size; }

    bool empty() { return size == 0; }

private:
    RedBlackTree<Key, ValueType> rbTree; // ʹ��ValueType��Ϊ�������ֵ����
    size_t size;
};

int main()
{
    // ����һ��MultiMapʵ��������������std::string��ֵ��������int
    MultiMap<std::string, int> myMultiMap;

    // ����һЩ��ֵ��
    myMultiMap.insert("apple", 10);
    myMultiMap.insert("banana", 20);
    myMultiMap.insert("apple", 30); // "apple"�����ж��ֵ

    // ��ȡ����ӡ��"apple"������ֵ
    auto appleValues = myMultiMap.at("apple");
    if (appleValues)
    {
        std::cout << "Values for 'apple':";
        for (const auto& val : *appleValues)
        {
            std::cout << val << ", ";
        }
        std::cout << '\n';
    }

    // ��MultiMap���Ƴ���"banana"������ֵ
    myMultiMap.remove("banana");

    // ��MultiMap���Ƴ���"apple"��ֵ30
    myMultiMap.remove("apple", 30);

    // ���MultiMap�Ƿ�Ϊ��
    if (!myMultiMap.empty())
    {
        std::cout << "The MultiMap is not empty, it has " << myMultiMap.getSize()
            << " elements." << std::endl;
    }

    return 0;
}