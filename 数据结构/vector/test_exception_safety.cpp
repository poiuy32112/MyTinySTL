#include <iostream>
#include <stdexcept>
#include <string>
#include "vector1_1.h"

// 用于测试异常安全性的类
class ThrowingClass
{
private:
    static int construction_count;
    static int copy_threshold;  // 在第几次拷贝时抛异常
    int value;

public:
    ThrowingClass(int v = 0) : value(v) 
    {
        std::cout << "构造 ThrowingClass(" << value << ")\n";
    }

    // 拷贝构造函数 - 可能抛异常
    ThrowingClass(const ThrowingClass& other) : value(other.value)
    {
        ++construction_count;
        std::cout << "拷贝构造 ThrowingClass(" << value << "), 拷贝次数: " << construction_count << "\n";
        
        if (copy_threshold > 0 && construction_count >= copy_threshold)
        {
            std::cout << "在第 " << construction_count << " 次拷贝时抛出异常!\n";
            throw std::runtime_error("拷贝构造失败");
        }
    }

    // 拷贝赋值操作符
    ThrowingClass& operator=(const ThrowingClass& other)
    {
        if (this != &other)
        {
            value = other.value;
            std::cout << "赋值 ThrowingClass(" << value << ")\n";
        }
        return *this;
    }

    ~ThrowingClass()
    {
        std::cout << "析构 ThrowingClass(" << value << ")\n";
    }

    int getValue() const { return value; }

    static void setCopyThreshold(int threshold) { copy_threshold = threshold; }
    static void resetCopyCount() { construction_count = 0; }
};

int ThrowingClass::construction_count = 0;
int ThrowingClass::copy_threshold = 0;

// 测试基本功能
void testBasicFunctionality()
{
    std::cout << "\n=== 测试基本功能 ===\n";
    
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    std::cout << "Size: " << v.getSize() << ", Capacity: " << v.getCapacity() << std::endl;
    std::cout << "Elements: ";
    v.printElements();
    
    // 测试拷贝构造
    vector<int> v2(v);
    std::cout << "拷贝后的 v2: ";
    v2.printElements();
    
    // 测试赋值操作
    vector<int> v3;
    v3 = v;
    std::cout << "赋值后的 v3: ";
    v3.printElements();
}

// 测试异常安全的拷贝构造
void testExceptionSafeCopyConstruction()
{
    std::cout << "\n=== 测试异常安全的拷贝构造 ===\n";
    
    // 创建源容器
    vector<ThrowingClass> original;
    original.push_back(ThrowingClass(1));
    original.push_back(ThrowingClass(2));
    original.push_back(ThrowingClass(3));
    
    std::cout << "\n原始容器创建完成，size = " << original.getSize() << std::endl;
    
    // 设置在第2次拷贝时抛异常
    ThrowingClass::resetCopyCount();
    ThrowingClass::setCopyThreshold(2);
    
    try
    {
        std::cout << "\n尝试拷贝构造（预期在第2次拷贝时失败）...\n";
        vector<ThrowingClass> copy(original);  // 这里应该会抛异常
        std::cout << "拷贝成功（不应该到达这里）\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "捕获异常: " << e.what() << std::endl;
        std::cout << "异常安全：拷贝失败时原对象应该保持不变\n";
        std::cout << "原始容器仍有 " << original.getSize() << " 个元素\n";
    }
    
    // 关闭异常，测试正常拷贝
    ThrowingClass::setCopyThreshold(0);
    ThrowingClass::resetCopyCount();
    
    try
    {
        std::cout << "\n正常拷贝构造测试...\n";
        vector<ThrowingClass> copy(original);
        std::cout << "拷贝成功，新容器有 " << copy.getSize() << " 个元素\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "意外异常: " << e.what() << std::endl;
    }
}

// 测试异常安全的赋值操作（copy-and-swap）
void testExceptionSafeAssignment()
{
    std::cout << "\n=== 测试异常安全的赋值操作 ===\n";
    
    // 创建目标容器
    vector<ThrowingClass> target;
    target.push_back(ThrowingClass(10));
    target.push_back(ThrowingClass(20));
    
    // 创建源容器
    vector<ThrowingClass> source;
    source.push_back(ThrowingClass(1));
    source.push_back(ThrowingClass(2));
    source.push_back(ThrowingClass(3));
    
    std::cout << "\n赋值前 - 目标容器大小: " << target.getSize() 
              << ", 源容器大小: " << source.getSize() << std::endl;
    
    // 设置在第2次拷贝时抛异常
    ThrowingClass::resetCopyCount();
    ThrowingClass::setCopyThreshold(2);
    
    try
    {
        std::cout << "\n尝试赋值操作（预期失败）...\n";
        target = source;  // copy-and-swap: 先构造临时副本，失败时target不变
        std::cout << "赋值成功（不应该到达这里）\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "捕获异常: " << e.what() << std::endl;
        std::cout << "异常安全：赋值失败时目标对象应该保持不变\n";
        std::cout << "目标容器仍有 " << target.getSize() << " 个元素\n";
    }
    
    // 关闭异常，测试正常赋值
    ThrowingClass::setCopyThreshold(0);
    ThrowingClass::resetCopyCount();
    
    try
    {
        std::cout << "\n正常赋值操作测试...\n";
        target = source;
        std::cout << "赋值成功，目标容器现在有 " << target.getSize() << " 个元素\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "意外异常: " << e.what() << std::endl;
    }
}

// 测试swap函数
void testSwapFunction()
{
    std::cout << "\n=== 测试 swap 函数 ===\n";
    
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    
    vector<int> v2;
    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    
    std::cout << "交换前:\n";
    std::cout << "v1 size=" << v1.getSize() << ": ";
    v1.printElements();
    std::cout << "v2 size=" << v2.getSize() << ": ";
    v2.printElements();
    
    v1.swap(v2);
    
    std::cout << "交换后:\n";
    std::cout << "v1 size=" << v1.getSize() << ": ";
    v1.printElements();
    std::cout << "v2 size=" << v2.getSize() << ": ";
    v2.printElements();
    
    // 测试非成员swap函数
    swap(v1, v2);
    std::cout << "再次交换后:\n";
    std::cout << "v1 size=" << v1.getSize() << ": ";
    v1.printElements();
    std::cout << "v2 size=" << v2.getSize() << ": ";
    v2.printElements();
}

int main()
{
    try
    {
        testBasicFunctionality();
        testExceptionSafeCopyConstruction();
        testExceptionSafeAssignment();
        testSwapFunction();
        
        std::cout << "\n=== 所有测试完成 ===\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "程序异常终止: " << e.what() << std::endl;
    }
    
    return 0;
} 