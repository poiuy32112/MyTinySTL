#include <iostream>
#include <string>
#include <chrono>
#include "vector1_2.h"

// 用于测试移动语义的类
class MoveTestClass
{
private:
    static int copy_count;
    static int move_count;
    static int construction_count;
    std::string data;
    int id;

public:
    // 构造函数
    MoveTestClass(int value = 0) : id(value), data("data_" + std::to_string(value))
    {
        ++construction_count;
        std::cout << "构造 MoveTestClass(" << id << "), 总构造次数: " << construction_count << std::endl;
    }

    // 拷贝构造函数
    MoveTestClass(const MoveTestClass& other) : id(other.id), data(other.data)
    {
        ++copy_count;
        ++construction_count;
        std::cout << "拷贝构造 MoveTestClass(" << id << "), 拷贝次数: " << copy_count << std::endl;
    }

    // 移动构造函数 (C++11)
    MoveTestClass(MoveTestClass&& other) noexcept : id(other.id), data(std::move(other.data))
    {
        ++move_count;
        ++construction_count;
        other.id = -1;  // 标记为已移动
        std::cout << "移动构造 MoveTestClass(" << id << "), 移动次数: " << move_count << std::endl;
    }

    // 拷贝赋值操作符
    MoveTestClass& operator=(const MoveTestClass& other)
    {
        if (this != &other)
        {
            id = other.id;
            data = other.data;
            ++copy_count;
            std::cout << "拷贝赋值 MoveTestClass(" << id << "), 拷贝次数: " << copy_count << std::endl;
        }
        return *this;
    }

    // 移动赋值操作符 (C++11)
    MoveTestClass& operator=(MoveTestClass&& other) noexcept
    {
        if (this != &other)
        {
            id = other.id;
            data = std::move(other.data);
            other.id = -1;  // 标记为已移动
            ++move_count;
            std::cout << "移动赋值 MoveTestClass(" << id << "), 移动次数: " << move_count << std::endl;
        }
        return *this;
    }

    ~MoveTestClass()
    {
        std::cout << "析构 MoveTestClass(" << id << ")" << std::endl;
    }

    int getId() const { return id; }
    const std::string& getData() const { return data; }

    static void resetCounters()
    {
        copy_count = 0;
        move_count = 0;
        construction_count = 0;
    }

    static void printStats()
    {
        std::cout << "=== 统计信息 ===" << std::endl;
        std::cout << "总构造次数: " << construction_count << std::endl;
        std::cout << "拷贝次数: " << copy_count << std::endl;
        std::cout << "移动次数: " << move_count << std::endl;
        std::cout << "=================" << std::endl;
    }
};

int MoveTestClass::copy_count = 0;
int MoveTestClass::move_count = 0;
int MoveTestClass::construction_count = 0;

// 测试移动构造函数
void testMoveConstructor()
{
    std::cout << "\n=== 测试移动构造函数 ===\n";

    MoveTestClass::resetCounters();

    // 创建源容器
    vector<MoveTestClass> source;
    source.push_back(MoveTestClass(1));
    source.push_back(MoveTestClass(2));
    source.push_back(MoveTestClass(3));

    std::cout << "\n创建源容器完成，size = " << source.getSize() << std::endl;
    MoveTestClass::printStats();

    // 移动构造
    std::cout << "\n执行移动构造...\n";
    vector<MoveTestClass> target(std::move(source));

    std::cout << "\n移动构造完成:" << std::endl;
    std::cout << "目标容器 size = " << target.getSize() << std::endl;
    std::cout << "源容器 size = " << source.getSize() << " (应该为0)" << std::endl;

    MoveTestClass::printStats();
}

// 测试移动赋值操作符
void testMoveAssignment()
{
    std::cout << "\n=== 测试移动赋值操作符 ===\n";

    MoveTestClass::resetCounters();

    // 创建目标容器
    vector<MoveTestClass> target;
    target.push_back(MoveTestClass(10));
    target.push_back(MoveTestClass(20));

    // 创建源容器
    vector<MoveTestClass> source;
    source.push_back(MoveTestClass(1));
    source.push_back(MoveTestClass(2));
    source.push_back(MoveTestClass(3));

    std::cout << "\n赋值前:" << std::endl;
    std::cout << "目标容器 size = " << target.getSize() << std::endl;
    std::cout << "源容器 size = " << source.getSize() << std::endl;

    // 移动赋值
    std::cout << "\n执行移动赋值...\n";
    target = std::move(source);

    std::cout << "\n移动赋值完成:" << std::endl;
    std::cout << "目标容器 size = " << target.getSize() << std::endl;
    std::cout << "源容器 size = " << source.getSize() << " (应该为0)" << std::endl;

    MoveTestClass::printStats();
}

// 测试移动版本的 push_back
void testMovePushBack()
{
    std::cout << "\n=== 测试移动版本的 push_back ===\n";

    MoveTestClass::resetCounters();

    vector<MoveTestClass> v;

    std::cout << "\n测试拷贝版本的 push_back:\n";
    MoveTestClass obj1(100);
    v.push_back(obj1);  // 拷贝版本

    std::cout << "\n测试移动版本的 push_back:\n";
    v.push_back(MoveTestClass(200));  // 移动版本（临时对象）

    std::cout << "\n测试显式移动的 push_back:\n";
    MoveTestClass obj3(300);
    v.push_back(std::move(obj3));  // 显式移动

    std::cout << "\n容器大小: " << v.getSize() << std::endl;
    MoveTestClass::printStats();
}

// 测试移动版本的 insert
void testMoveInsert()
{
    std::cout << "\n=== 测试移动版本的 insert ===\n";

    MoveTestClass::resetCounters();

    vector<MoveTestClass> v;
    v.push_back(MoveTestClass(1));
    v.push_back(MoveTestClass(3));

    std::cout << "\n初始容器创建完成, size = " << v.getSize() << std::endl;

    std::cout << "\n测试拷贝版本的 insert:\n";
    MoveTestClass obj2(20);
    v.insert(1, obj2);  // 在位置1插入，拷贝版本

    std::cout << "\n测试移动版本的 insert:\n";
    v.insert(1, MoveTestClass(10));  // 在位置1插入，移动版本

    std::cout << "\n容器大小: " << v.getSize() << std::endl;
    MoveTestClass::printStats();
}

// 性能对比测试
void performanceComparison()
{
    std::cout << "\n=== 性能对比测试 ===\n";

    const int N = 1000;

    // 测试拷贝性能
    {
        MoveTestClass::resetCounters();
        auto start = std::chrono::high_resolution_clock::now();

        vector<MoveTestClass> v;
        for (int i = 0; i < N; ++i)
        {
            MoveTestClass obj(i);
            v.push_back(obj);  // 拷贝版本
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "拷贝版本 - 时间: " << duration.count() << " 微秒\n";
        MoveTestClass::printStats();
    }

    // 测试移动性能
    {
        MoveTestClass::resetCounters();
        auto start = std::chrono::high_resolution_clock::now();

        vector<MoveTestClass> v;
        for (int i = 0; i < N; ++i)
        {
            v.push_back(MoveTestClass(i));  // 移动版本（临时对象）
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "移动版本 - 时间: " << duration.count() << " 微秒\n";
        MoveTestClass::printStats();
    }
}

int main()
{
    try
    {
        testMoveConstructor();
        testMoveAssignment();
        testMovePushBack();
        testMoveInsert();
        performanceComparison();

        std::cout << "\n=== 所有移动语义测试完成 ===\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "程序异常终止: " << e.what() << std::endl;
    }

    return 0;
}