#include <iostream>
#include <vector>

namespace mystl {

//��ֵ��
struct Pair {
    int key{ 0 };
    std::string val;

    Pair(int key, std::string val) : key(key), val(val) {}
};

/* ��ʽ��ַ��ϣ�� */
class HashMapChaining {
private:
    int m_size;                       // ��ֵ������
    int m_capacity;                   // ��ϣ������
    double m_loadThres;               // �������ݵĸ���������ֵ
    int m_extendRatio;                // ���ݱ���
    std::vector<std::vector<Pair*>> m_buckets; // Ͱ����

public:
    /* ���췽�� */
    HashMapChaining() : m_size(0), m_capacity(4), m_loadThres(2.0 / 3.0), m_extendRatio(2) {
        m_buckets.resize(m_capacity);
    }

    /* �������� */
    ~HashMapChaining() {
        for (auto& bucket : m_buckets) {
            for (Pair* pair : bucket) {
                // �ͷ��ڴ�
                delete pair;
            }
        }
    }

    //��ǰ��ֵ�Ե�����
    int size() {
        return m_size;
    }

    //��ǰ��ϣ�������
    int capacity() {
        return m_capacity;
    }

    /* ��ϣ���� */
    int hashFunc(int key) {
        return key % m_capacity;
    }

    /* �������� */
    double loadFactor() {
        return (double)m_size / (double)m_capacity;
    }

    /* ��ѯ���� */
    std::string get(int key) {
        int index = hashFunc(key);
        // ����Ͱ�����ҵ� key ���򷵻ض�Ӧ val
        for (Pair* pair : m_buckets[index]) {
            if (pair->key == key) {
                return pair->val;
            }
        }
        std::cout << "δ�ҵ� key���ѷ��ؿ��ַ���\n";
        // ��δ�ҵ� key ���򷵻ؿ��ַ���
        return "";
    }

    /* ��Ӳ��� */
    void put(int key, std::string val) {
        // ���������ӳ�����ֵʱ��ִ������
        if (loadFactor() > m_loadThres) {
            extend();
        }
        int index = hashFunc(key);
        // ����Ͱ��������ָ�� key ������¶�Ӧ val ������
        for (Pair* pair : m_buckets[index]) {
            if (pair->key == key) {
                pair->val = val;
                return;
            }
        }
        // ���޸� key ���򽫼�ֵ�������β��
        m_buckets[index].push_back(new Pair(key, val));
        m_size++;
    }

    /* ɾ������ */
    void remove(int key) {
        int index = hashFunc(key);
        auto& bucket = m_buckets[index];
        // ����Ͱ������ɾ����ֵ��
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket[i]->key == key) {
                Pair* tmp = bucket[i];
                bucket.erase(bucket.begin() + i); // ����ɾ����ֵ��
                delete tmp;                       // �ͷ��ڴ�
                m_size--;
                return;
            }
        }
    }

    /* ���ݹ�ϣ�� */
    void extend() {
        // �ݴ�ԭ��ϣ��
        std::vector<std::vector<Pair*>> bucketsTmp = m_buckets;
        // ��ʼ�����ݺ���¹�ϣ��
        m_capacity *= m_extendRatio;
        m_buckets.clear();
        m_buckets.resize(m_capacity);
        m_size = 0;
        // ����ֵ�Դ�ԭ��ϣ��������¹�ϣ��
        for (auto& bucket : bucketsTmp) {
            for (Pair* pair : bucket) {
                put(pair->key, pair->val);
                // �ͷ��ڴ�
                delete pair;
            }
        }
    }

    /* ��ӡ��ϣ�� */
    void print() {
        for (auto& bucket : m_buckets) {
            std::cout << "[";
            for (Pair* pair : bucket) {
                std::cout << pair->key << " -> " << pair->val << ", ";
            }
            std::cout << "]\n";
        }
    }
};

}

int main() {
    mystl::HashMapChaining umap;
    umap.put(1, "a");
    std::cout << "��ǰ��ֵ�Ե�������" << umap.size() << '\n'; //1
    std::cout << "��ǰ��ϣ���������" << umap.capacity() << '\n'; //4
    umap.put(2, "ab");
    std::cout << "��ǰ��ֵ�Ե�������" << umap.size() << '\n'; //2
    std::cout << "��ǰ��ϣ���������" << umap.capacity() << '\n'; //4
    umap.put(3, "abc");
    std::cout << "��ǰ��ֵ�Ե�������" << umap.size() << '\n'; //3
    std::cout << "��ǰ��ϣ���������" << umap.capacity() << '\n'; //4
    umap.put(4, "abcd");
    std::cout << "��ǰ��ֵ�Ե�������" << umap.size() << '\n'; //4
    std::cout << "��ǰ��ϣ���������" << umap.capacity() << '\n'; //8
    umap.print();
    std::cout << "------------------------\n";

    std::cout << umap.get(2) << '\n';
    umap.put(0, "qqq");
    umap.remove(2);
    std::cout << umap.get(2) << '\n';
    umap.put(8, "w");
    umap.put(24, "ww");
    umap.put(19, "w");
    umap.put(0, "eee");
    std::cout << "��ǰ��ֵ�Ե�������" << umap.size() << '\n'; //4
    std::cout << "��ǰ��ϣ���������" << umap.capacity() << '\n'; //8
    umap.print();

    return 0;
}

//int hashFunc(int key)
//double loadFactor()
//std::string get(int key)/* ��ѯ���� */
//void put(int key, std::string val)/* ��Ӳ��� */
//void remove(int key)/* ɾ������ */
//void extend()/* ���ݹ�ϣ�� */
//void print()

//size()
//m_capacity()
//hashFunc()
//loadFactor()
//get()
//put()
//remove()
//extend()
//print()
