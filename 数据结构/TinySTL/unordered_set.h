#include "hashtable.h" // 之前实现的哈希表
#include <cstddef>

template <typename Key> class Unordered_set
{
public:
    Unordered_set() : hashtable() {};

    ~Unordered_set() {}

    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(Key key) { hashtable.insertKey(key); }

    void erase(Key key) { hashtable.erase(key); }

    bool find(const Key& key) { return hashtable.find(key) != nullptr; }

private:
    HashTable<Key, Key> hashtable;
};

int main()
{
    // 创建一个整数类型的 Unordered_set 集合
    Unordered_set<int> intSet;

    // 插入一些数字
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);

    // 检查集合是否为空
    std::cout << "集合是否为空? " << (intSet.empty() ? "是" : "否") << std::endl;

    // 检查集合的大小
    std::cout << "集合的大小: " << intSet.size() << std::endl;

    // 查找一个元素
    std::cout << "2 是否在集合中? " << (intSet.find(2) ? "是" : "否")
        << std::endl;

    // 删除一个元素
    intSet.erase(2);
    std::cout << "删除 2 后，2 是否还在集合中? " << (intSet.find(2) ? "是" : "否")
        << std::endl;

    // 清空集合
    intSet.clear();
    std::cout << "清空后集合是否为空? " << (intSet.empty() ? "是" : "否")
        << std::endl;

    // 创建一个字符串类型的 Unordered_set 集合
    Unordered_set<std::string> stringSet;

    // 插入一些字符串
    stringSet.insert("apple");
    stringSet.insert("banana");
    stringSet.insert("cherry");

    // 查找一个字符串
    std::cout << "'banana' 是否在集合中? "
        << (stringSet.find("banana") ? "是" : "否") << std::endl;

    // 删除一个字符串
    stringSet.erase("banana");
    std::cout << "删除 'banana' 后，'banana' 是否还在集合中? "
        << (stringSet.find("banana") ? "是" : "否") << std::endl;

    return 0;
}