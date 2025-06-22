#include "rb_tree.h" // ֮ǰʵ�ֵĺ����

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

    // ����Ԫ��
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);

    // ��ӡ���ϴ�С
    std::cout << "��ǰ���ϵĴ�С: " << mySet.size() << std::endl;

    // ��鼯���Ƿ�����ض�Ԫ��
    int keyToCheck = 20;
    std::cout << "�����Ƿ����Ԫ��" << keyToCheck << ": "
        << (mySet.contains(keyToCheck) ? "��" : "��") << std::endl;

    // ɾ��Ԫ��
    int keyToDelete = 20;
    mySet.erase(keyToDelete);
    std::cout << "ɾ��Ԫ��" << keyToDelete
        << "�󣬵�ǰ���ϵĴ�С: " << mySet.size() << std::endl;

    // �ٴμ�鼯���Ƿ������ɾ����Ԫ��
    std::cout << "ɾ��Ԫ��" << keyToDelete << "�󣬼����Ƿ����Ԫ��"
        << keyToDelete << ": " << (mySet.contains(keyToCheck) ? "��" : "��")
        << std::endl;

    // ��鼯���Ƿ�Ϊ��
    std::cout << "�����Ƿ�Ϊ��: " << (mySet.empty() ? "��" : "��") << std::endl;

    return 0;
}