#include <iostream>
#include <vector>

namespace mystl {

struct Pair {
    int m_key{ 0 };
    std::string m_val;

    Pair(int key, std::string val) : m_key(key), m_val(val) {}
};

class HashMapChaining {
private:
    int m_size;
    int m_cap;
    double m_load_thres;
    int m_extend_ration;
    std::vector<std::vector<Pair*>> m_buckets;

public:
    HashMapChaining() : m_size(0), m_cap(4), m_load_thres(2.0 / 3.0), m_extend_ration(2) {
        m_buckets.resize(m_cap);
    }

    ~HashMapChaining() {
        for (auto& bucket : m_buckets) {
            for (Pair* pair : bucket) {
                delete pair;
            }
        }
    }

    int size() {
        return m_size;
    }

    int capacity() {
        return m_cap;
    }

    int hashFunc(int key) {
        return key % capacity();
    }

    double loadFactor() {
        return (double)size() / (double)capacity();
    }

    std::string get(int key) {
        int index = hashFunc(key);
        for (Pair* pair : m_buckets[index]) {
            if (pair->m_key == key) {
                return pair->m_val;
            }
        }

        std::cout << "未找到key，已返回空字符串\n";
        return "";
    }

    void put(int key, std::string val) {
        if (loadFactor() > m_load_thres) {
            extend();
        }

        int index = hashFunc(key);
        for (Pair* pair : m_buckets[index]) {
            if (pair->m_key == key) {
                pair->m_val = val;
                return;
            }
        }

        m_buckets[index].push_back(new Pair(key, val));
        m_size++;
    }

    void remove(int key) {
        int index = hashFunc(key);
        for (int i = 0; i < m_buckets[index].size(); ++i) {
            if (m_buckets[index][i]->m_key == key) {
                Pair* tmp = m_buckets[index][i];
                m_buckets[index].erase(m_buckets[index].begin() + i);
                delete tmp;
                m_size--;
                return;
            }
        }
    }

    void extend() {
        std::vector<std::vector<Pair*>> buckets_tmp = m_buckets;
        m_cap *= m_extend_ration;
        m_buckets.clear();
        m_buckets.resize(m_cap);
        m_size = 0;

        for (auto& bucket : buckets_tmp) {
            for (Pair* pair : bucket) {
                put(pair->m_key, pair->m_val);
            }
        }
    }

    void print() {
        for (auto& bucket : m_buckets) {
            std::cout << '[';
            for (Pair* pair : bucket) {
                std::cout << pair->m_key << " -> " << pair->m_val << ", ";
            }
            std::cout << "]\n";
        }
    }

};

}

int main() {
    mystl::HashMapChaining umap;
    umap.put(1, "a");
    std::cout << "当前键值对的数量：" << umap.size() << '\n'; //1
    std::cout << "当前哈希表的容量：" << umap.capacity() << '\n'; //4
    umap.put(2, "ab");
    std::cout << "当前键值对的数量：" << umap.size() << '\n'; //2
    std::cout << "当前哈希表的容量：" << umap.capacity() << '\n'; //4
    umap.put(3, "abc");
    std::cout << "当前键值对的数量：" << umap.size() << '\n'; //3
    std::cout << "当前哈希表的容量：" << umap.capacity() << '\n'; //4
    umap.put(4, "abcd");
    std::cout << "当前键值对的数量：" << umap.size() << '\n'; //4
    std::cout << "当前哈希表的容量：" << umap.capacity() << '\n'; //8
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
    std::cout << "当前键值对的数量：" << umap.size() << '\n'; //4
    std::cout << "当前哈希表的容量：" << umap.capacity() << '\n'; //8
    umap.print();

    return 0;
}