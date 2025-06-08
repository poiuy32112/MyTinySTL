#include "RedBlackTree.h" // ֮ǰʵ�ֵĺ����
#include <iostream>
#include <utility> // For std::pair

// ����RedBlackTree�Ѿ����壬����KeyΪmap��key���ͣ�ValueΪmap��value����

template <typename Key, typename Value> class Map
{
public:
    Map() : rbTree() {}

    void insert(const Key& key, const Value& value) { rbTree.insert(key, value); }

    void erase(const Key& key) { rbTree.remove(key); }

    size_t size() { return rbTree.getSize(); }

    bool empty() const { return rbTree.empty(); }

    bool contains(const Key& key) { return rbTree.at(key) != nullptr; }

    Value& at(const Key& key)
    {
        Value* foundVal = rbTree.at(key);
        if (foundVal)
        {
            return *foundVal;
        }
        else
        {
            throw std::out_of_range("Key not found");
        }
    }

    Value& operator[](const Key& key)
    {
        Value* foundVal = rbTree.at(key);
        if (foundVal)
        {
            // ��������ڣ����ع�����ֵ
            return *foundVal; // ���ߣ��������ҵ��ļ�������ֵ
        }
        else
        {
            // ����������ڣ������¼�ֵ�ԣ��������²����ֵ������
            Value defaultValue;
            rbTree.insert(key, defaultValue);
            return *rbTree.at(key);
        }
    }

private:
    RedBlackTree<Key, Value> rbTree;
};

// main����
int main()
{
    Map<int, std::string> map;

    // �����ֵ��
    map.insert(1, "Apple");
    map.insert(2, "Banana");
    map.insert(3, "Cherry");

    // ��ӡ��С
    std::cout << "��ǰMap�Ĵ�С: " << map.size() << std::endl;

    // ����Ԫ��
    try
    {
        std::cout << "��1��Ӧ��ֵ: " << map.at(1) << std::endl;
        std::cout << "��2��Ӧ��ֵ: " << map.at(2) << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "����: " << e.what() << std::endl;
    }

    // ����Ƿ����ĳ����
    int keyToCheck = 3;
    std::cout << "Map�Ƿ������" << keyToCheck << ": "
        << (map.contains(keyToCheck) ? "��" : "��") << std::endl;

    // ʹ��[]��������ʻ򴴽�Ԫ��
    std::cout << "��4��Ӧ��ֵ���ڴ�֮ǰ�����ڣ�����������: " << map[4]
        << std::endl;

    // ɾ��Ԫ��
    int keyToDelete = 2;
    std::cout << "ɾ����" << keyToDelete << std::endl;
    map.erase(keyToDelete);

    // �ٴδ�ӡ��С
    std::cout << "ɾ����" << keyToDelete << "�󣬵�ǰMap�Ĵ�С: " << map.size()
        << std::endl;

    // ʹ��[]�����ΪԪ�ظ�ֵ
    map[4] = "Pear";
    std::cout << "��4��Ӧ��ֵ: " << map[4] << '\n';
    return 0;
}