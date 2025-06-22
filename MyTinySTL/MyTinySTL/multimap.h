#include "rb_tree.h" // 之前实现的红黑树
#include <cstddef>
#include <iostream>
#include <list>

template <typename Key, typename Value> class MultiMap
{
public:
    using ValueType = std::list<Value>; // 修改Value的类型为list

    MultiMap() : rbTree(), size(0) {}

    void insert(const Key& key, const Value& value)
    {
        // 查找当前键是否已经存在
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            // 如果键已经存在，将值添加到对应的list中
            existingValues->push_back(value);
        }
        else
        {
            // 如果键不存在，创建一个新的list并添加值，然后插入到红黑树中
            ValueType values;
            values.push_back(value);
            rbTree.insert(key, values);
        }
        size++;
    }

    void remove(const Key& key)
    {
        // 删除整个键，包括其所有的值
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            size -= existingValues->size();
            rbTree.remove(key);
        }
    }

    void remove(const Key& key, const Value& value)
    {
        // 查找当前键
        ValueType* existingValues = rbTree.at(key);
        if (existingValues)
        {
            // 删除给定的值
            existingValues->remove(value);
            size--;
            // 如果删除值后list为空，也删除键
            if (existingValues->empty())
            {
                rbTree.remove(key);
            }
        }
    }

    ValueType* at(const Key& key)
    {
        // 获取键对应的所有值的列表
        return rbTree.at(key);
    }

    int getSize() { return size; }

    bool empty() { return size == 0; }

private:
    RedBlackTree<Key, ValueType> rbTree; // 使用ValueType作为红黑树的值类型
    size_t size;
};

int main()
{
    // 创建一个MultiMap实例，键的类型是std::string，值的类型是int
    MultiMap<std::string, int> myMultiMap;

    // 插入一些键值对
    myMultiMap.insert("apple", 10);
    myMultiMap.insert("banana", 20);
    myMultiMap.insert("apple", 30); // "apple"可以有多个值

    // 获取并打印键"apple"的所有值
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

    // 从MultiMap中移除键"banana"的所有值
    myMultiMap.remove("banana");

    // 从MultiMap中移除键"apple"的值30
    myMultiMap.remove("apple", 30);

    // 检查MultiMap是否为空
    if (!myMultiMap.empty())
    {
        std::cout << "The MultiMap is not empty, it has " << myMultiMap.getSize()
            << " elements." << std::endl;
    }

    return 0;
}