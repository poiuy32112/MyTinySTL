#include "rb_tree.h" // 之前实现的红黑树

template <typename Key> class Set
{
public:
    Set() : rbTree() {}

    void insert(const Key& key) { rbTree.insert(key, key); }

    void erase(const Key& key) { rbTree.remove(key); }

    size_t size() { return rbTree.getSize(); }

    bool empty() { return rbTree.empty(); }

    bool contains(const Key& key) { return rbTree.at(key) != nullptr; }

private:
    RedBlackTree<Key, Key> rbTree;
};

int main()
{
    Set<int> mySet;

    // 插入元素
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);

    // 打印集合大小
    std::cout << "当前集合的大小: " << mySet.size() << std::endl;

    // 检查集合是否包含特定元素
    int keyToCheck = 20;
    std::cout << "集合是否包含元素" << keyToCheck << ": "
        << (mySet.contains(keyToCheck) ? "是" : "否") << std::endl;

    // 删除元素
    int keyToDelete = 20;
    mySet.erase(keyToDelete);
    std::cout << "删除元素" << keyToDelete
        << "后，当前集合的大小: " << mySet.size() << std::endl;

    // 再次检查集合是否包含已删除的元素
    std::cout << "删除元素" << keyToDelete << "后，集合是否包含元素"
        << keyToDelete << ": " << (mySet.contains(keyToCheck) ? "是" : "否")
        << std::endl;

    // 检查集合是否为空
    std::cout << "集合是否为空: " << (mySet.empty() ? "是" : "否") << std::endl;

    return 0;
}