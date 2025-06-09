#include "hashTable.h" // ֮ǰʵ�ֵĹ�ϣ��
#include <cstddef>

template <typename Key, typename Value> class Unordered_map
{
private:
    HashTable<Key, Value> hashtable;

public:
    Unordered_map() : hashtable() {};

    ~Unordered_map() {}

    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(const Key& key, const Value& value)
    {
        hashtable.insert(key, value);
    }

    void erase(const Key& key) { hashtable.erase(key); }

    bool find(const Key& key) { return hashtable.find(key) != nullptr; }

    Value& operator[](const Key& key)
    {
        Value* ans = hashtable.find(key);
        if (ans != nullptr)
        {
            return *ans;
        }
        hashtable.insertKey(key);
        ans = hashtable.find(key);
        return *ans;
    }
};

int main()
{
    // ����һ�� Unordered_map������ֵ���� std::string ����
    Unordered_map<std::string, std::string> map;

    // ����һЩ��ֵ��
    map.insert("apple", "ƻ��");
    map.insert("banana", "�㽶");
    map.insert("cherry", "ӣ��");

    // ���ӳ���Ƿ�Ϊ��
    std::cout << "ӳ���Ƿ�Ϊ��? " << (map.empty() ? "��" : "��") << std::endl;

    // ��ȡӳ��Ĵ�С
    std::cout << "ӳ��Ĵ�С: " << map.size() << std::endl;

    // ����Ԫ��
    std::cout << "apple ��Ӧ��������: " << map["apple"] << std::endl;

    // �޸�Ԫ��
    map["apple"] = "��ƻ��";
    std::cout << "�޸ĺ� apple ��Ӧ��������: " << map["apple"] << std::endl;

    // ʹ�� [] �����������µļ�ֵ��
    map["orange"] = "����";
    std::cout << "orange ��Ӧ��������: " << map["orange"] << std::endl;

    // ����Ԫ��
    std::cout << "cherry �Ƿ���ӳ����? " << (map.find("cherry") ? "��" : "��")
        << std::endl;

    // ɾ��Ԫ��
    map.erase("banana");
    std::cout << "ɾ�� banana ��banana �Ƿ���ӳ����? "
        << (map.find("banana") ? "��" : "��") << std::endl;

    // ���ӳ��
    map.clear();
    std::cout << "��պ�ӳ���Ƿ�Ϊ��? " << (map.empty() ? "��" : "��")
        << std::endl;

    return 0;
}