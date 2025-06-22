#include "hashtable.h" // ֮ǰʵ�ֵĹ�ϣ��
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
    // ����һ���������͵� Unordered_set ����
    Unordered_set<int> intSet;

    // ����һЩ����
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);

    // ��鼯���Ƿ�Ϊ��
    std::cout << "�����Ƿ�Ϊ��? " << (intSet.empty() ? "��" : "��") << std::endl;

    // ��鼯�ϵĴ�С
    std::cout << "���ϵĴ�С: " << intSet.size() << std::endl;

    // ����һ��Ԫ��
    std::cout << "2 �Ƿ��ڼ�����? " << (intSet.find(2) ? "��" : "��")
        << std::endl;

    // ɾ��һ��Ԫ��
    intSet.erase(2);
    std::cout << "ɾ�� 2 ��2 �Ƿ��ڼ�����? " << (intSet.find(2) ? "��" : "��")
        << std::endl;

    // ��ռ���
    intSet.clear();
    std::cout << "��պ󼯺��Ƿ�Ϊ��? " << (intSet.empty() ? "��" : "��")
        << std::endl;

    // ����һ���ַ������͵� Unordered_set ����
    Unordered_set<std::string> stringSet;

    // ����һЩ�ַ���
    stringSet.insert("apple");
    stringSet.insert("banana");
    stringSet.insert("cherry");

    // ����һ���ַ���
    std::cout << "'banana' �Ƿ��ڼ�����? "
        << (stringSet.find("banana") ? "��" : "��") << std::endl;

    // ɾ��һ���ַ���
    stringSet.erase("banana");
    std::cout << "ɾ�� 'banana' ��'banana' �Ƿ��ڼ�����? "
        << (stringSet.find("banana") ? "��" : "��") << std::endl;

    return 0;
}