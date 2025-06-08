#include "rb_tree.h" // 之前实现的红黑树
#include <cstddef>
#include <stdexcept>

template <typename Key> class MultiSet
{
    RedBlackTree<Key, size_t> rbTree;
    size_t sz;

public:
    MultiSet() : sz(0) {} // 构造函数
    ~MultiSet() {}        // 析构函数

    // 插入元素
    void insert(const Key& key)
    {
        auto count = rbTree.at(key);
        if (count != nullptr)
        {
            (*count)++;
            sz++;

            return;
        }
        rbTree.insert(key, 1);
        sz++;
    }

    // 删除键为key的元素
    void erase(const Key& key)
    {
        auto count = rbTree.at(key);
        if (count == nullptr)
        {
            return;
        }
        (*count)--;
        sz--;
        if (*count == 0)
        {
            rbTree.remove(key);
        }
    }

    // 返回容器中元素的数量
    size_t size() const { return sz; }

    // 判断容器是否为空
    bool empty() const { return sz == 0; }

    // 返回在 multiset 中等于给定值的元素的数量
    size_t count(const Key& key)
    {
        auto num = rbTree.at(key);
        if (num != nullptr)
        {
            return *num;
        }

        return 0;
    }

    void clear()
    {
        sz = 0;
        rbTree.clear();
    }
};

int main()
{
    MultiSet<int> mySet; // Create an Unordered_set for integers

    // Insert some elements
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);

    // Check if elements are in the set
    std::cout << "Does the set contain 1? " << (mySet.count(1) > 0 ? "Yes" : "No")
        << std::endl;
    std::cout << "Does the set contain 4? " << (mySet.count(4) > 0 ? "Yes" : "No")
        << std::endl;

    // Print the size of the set
    std::cout << "The set size is: " << mySet.size() << std::endl;

    // Remove an element
    mySet.erase(2);
    std::cout << "After erasing 2, does the set contain 2? "
        << (mySet.count(2) > 0 ? "Yes" : "No") << std::endl;
    std::cout << "The set size is now: " << mySet.size() << std::endl;

    // Clear the set
    mySet.clear();
    std::cout << "After clearing, is the set empty? "
        << (mySet.empty() ? "Yes" : "No") << std::endl;

    return 0;
}