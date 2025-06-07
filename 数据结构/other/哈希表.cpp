#define _CRT_SECURE_NO_WARNINGS 1 

#include<iostream>

#define MAX_SIZE 16

//键值对 int->string
struct Pair {
    int key;
    char* val;
};

//基于数组实现的哈希表
struct ArrayHashMap {
    Pair* buckets[MAX_SIZE];
};

struct MapSet {
    void* set;
    int len;
};

ArrayHashMap* newArrayHashMap() {
    ArrayHashMap* ans = new ArrayHashMap;
    for (int i = 0; i < MAX_SIZE; ++i) {
        ans->buckets[i] = nullptr;
    }
    return ans;
}

void delArrayHashMap(ArrayHashMap* hmap) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (hmap->buckets[i] != nullptr) {
            delete(hmap->buckets[i]->val);
            delete(hmap->buckets[i]);
        }
    }
    delete(hmap);
}

//哈希函数
int hashFunc(int key) {
    int index = key % MAX_SIZE;
    return index;
}

//添加操作
void put(ArrayHashMap* hmap, const int key, const char* val) {
    Pair* p = new Pair;
    p->key = key;
    p->val = new char[strlen(val) + 1];
    strcpy(p->val, val);

    int index = hashFunc(key);
    hmap->buckets[index] = p;
}

//删除操作
void removeItem(ArrayHashMap* hmap, const int key) {
    int index = hashFunc(key);
    delete(hmap->buckets[index]->val);
    delete(hmap->buckets[index]);
    hmap->buckets[index] = nullptr;
}

void print(ArrayHashMap* hmap) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (hmap->buckets[i] != nullptr) {
            std::cout << "键key: " << hmap->buckets[i]->key << "     值val: " << hmap->buckets[i]->val << '\n';
        }
    }
    std::cout << std::endl;
}

int main() {
    ArrayHashMap* hmap = newArrayHashMap();
    put(hmap, 0, "张三");
    put(hmap, 1, "李四");
    put(hmap, 2, "王五");
    put(hmap, 15, "赵六");
    put(hmap, 12, "ds");
    put(hmap, 6, "aaa");
    print(hmap);
    std::cout << "-------------------------" << std::endl;

    removeItem(hmap, 0);
    removeItem(hmap, 1);
    put(hmap, 0, "bbb");
    print(hmap);
    std::cout << "-------------------------" << std::endl;

    delArrayHashMap(hmap);
    return 0;
}

//ArrayHashMap* newArrayHashMap()
//void delArrayHashMap(ArrayHashMap* hmap)
//void put(ArrayHashMap* hmap, const int key, const char* val) //添加操作
//void removeItem(ArrayHashMap* hmap, const int key) //删除操作
//void print(ArrayHashMap* hmap)

//void pairSet(ArrayHashMap* hmap, MapSet* set) //获取所有键值对
//void keySet(ArrayHashMap* hmap, MapSet* set) //获取所有键
//void valueSet(ArrayHashMap* hmap, MapSet* set) //获取所有值