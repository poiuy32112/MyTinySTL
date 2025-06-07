#include <iostream>
#include <vector>

namespace mystl {

//键值对
struct Pair {
    int key{ 0 };
    std::string val;

    Pair(int key, std::string val) : key(key), val(val) {}
};

/* 链式地址哈希表 */
class HashMapChaining {
private:
    int m_size;                       // 键值对数量
    int m_capacity;                   // 哈希表容量
    double m_loadThres;               // 触发扩容的负载因子阈值
    int m_extendRatio;                // 扩容倍数
    std::vector<std::vector<Pair*>> m_buckets; // 桶数组

public:
    /* 构造方法 */
    HashMapChaining() : m_size(0), m_capacity(4), m_loadThres(2.0 / 3.0), m_extendRatio(2) {
        m_buckets.resize(m_capacity);
    }

    /* 析构方法 */
    ~HashMapChaining() {
        for (auto& bucket : m_buckets) {
            for (Pair* pair : bucket) {
                // 释放内存
                delete pair;
            }
        }
    }

    //当前键值对的数量
    int size() {
        return m_size;
    }

    //当前哈希表的容量
    int capacity() {
        return m_capacity;
    }

    /* 哈希函数 */
    int hashFunc(int key) {
        return key % m_capacity;
    }

    /* 负载因子 */
    double loadFactor() {
        return (double)m_size / (double)m_capacity;
    }

    /* 查询操作 */
    std::string get(int key) {
        int index = hashFunc(key);
        // 遍历桶，若找到 key ，则返回对应 val
        for (Pair* pair : m_buckets[index]) {
            if (pair->key == key) {
                return pair->val;
            }
        }
        std::cout << "未找到 key，已返回空字符串\n";
        // 若未找到 key ，则返回空字符串
        return "";
    }

    /* 添加操作 */
    void put(int key, std::string val) {
        // 当负载因子超过阈值时，执行扩容
        if (loadFactor() > m_loadThres) {
            extend();
        }
        int index = hashFunc(key);
        // 遍历桶，若遇到指定 key ，则更新对应 val 并返回
        for (Pair* pair : m_buckets[index]) {
            if (pair->key == key) {
                pair->val = val;
                return;
            }
        }
        // 若无该 key ，则将键值对添加至尾部
        m_buckets[index].push_back(new Pair(key, val));
        m_size++;
    }

    /* 删除操作 */
    void remove(int key) {
        int index = hashFunc(key);
        auto& bucket = m_buckets[index];
        // 遍历桶，从中删除键值对
        for (int i = 0; i < bucket.size(); i++) {
            if (bucket[i]->key == key) {
                Pair* tmp = bucket[i];
                bucket.erase(bucket.begin() + i); // 从中删除键值对
                delete tmp;                       // 释放内存
                m_size--;
                return;
            }
        }
    }

    /* 扩容哈希表 */
    void extend() {
        // 暂存原哈希表
        std::vector<std::vector<Pair*>> bucketsTmp = m_buckets;
        // 初始化扩容后的新哈希表
        m_capacity *= m_extendRatio;
        m_buckets.clear();
        m_buckets.resize(m_capacity);
        m_size = 0;
        // 将键值对从原哈希表搬运至新哈希表
        for (auto& bucket : bucketsTmp) {
            for (Pair* pair : bucket) {
                put(pair->key, pair->val);
                // 释放内存
                delete pair;
            }
        }
    }

    /* 打印哈希表 */
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

//int hashFunc(int key)
//double loadFactor()
//std::string get(int key)/* 查询操作 */
//void put(int key, std::string val)/* 添加操作 */
//void remove(int key)/* 删除操作 */
//void extend()/* 扩容哈希表 */
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
