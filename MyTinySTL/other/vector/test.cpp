#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "vector.h"
#include "custom_allocator.h"

// 辅助函数，用于打印 vector 信息
template<typename T>
void print_info(const vector<T>& v, const std::string& name)
{
    std::cout << "--- " << name << " ---" << std::endl;
    std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << std::endl;
    std::cout << "Elements: ";
    v.printElements();
    std::cout << "--------------------" << std::endl;
}

// 辅助函数，用于打印 vector 信息
template<typename T, typename Allocator>
void print_info(const vector<T, Allocator>& v, const std::string& name)
{
    std::cout << "--- " << name << " ---" << std::endl;
    std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << std::endl;
    std::cout << "Elements: ";
    v.printElements();
    std::cout << "--------------------" << std::endl;
}

// 1. 测试构造函数和基础功能
void test_constructors()
{
    std::cout << "\n=== 1. 测试构造函数和基础功能 ===\n";

    // 默认构造
    vector<int> v1;
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    print_info(v1, "v1 (默认构造)");

    // push_back
    v1.push_back(10);
    v1.push_back(20);
    assert(v1.size() == 2);
    assert(v1[0] == 10 && v1[1] == 20);
    print_info(v1, "v1 (push_back后)");

    // 拷贝构造
    vector<int> v2(v1);
    assert(v2.size() == 2);
    assert(v2.capacity() >= 2);
    assert(v2[0] == 10 && v2[1] == 20);
    // 修改v1不应影响v2
    v1.push_back(30);
    assert(v1[2] == 30);
    assert(v2.size() == 2);
    print_info(v1, "v1 (修改后)");
    print_info(v2, "v2 (拷贝构造自 v1)");

    // 移动构造
    vector<int> v3(std::move(v2));
    assert(v3.size() == 2);
    assert(v3[0] == 10 && v3[1] == 20);
    // v2应被置空
    assert(v2.size() == 0);
    assert(v2.capacity() == 0);
    print_info(v3, "v3 (移动构造自 v2)");
    print_info(v2, "v2 (被移动后)");
}

// 2. 测试赋值操作
void test_assignments()
{
    std::cout << "\n=== 2. 测试赋值操作 ===\n";
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    vector<int> v2;
    v2.push_back(100);
    v2.push_back(200);
    v2.push_back(300);

    print_info(v1, "v1 (赋值前)");
    print_info(v2, "v2 (赋值前)");

    // 拷贝赋值
    v1 = v2;
    assert(v1.size() == 3);
    assert(v1[1] == 200);
    v2.push_back(400); // 修改v2不应影响v1
    assert(v1.size() == 3);
    print_info(v1, "v1 (拷贝赋值 v2 后)");

    // 移动赋值
    vector<int> v3;
    v3.push_back(99);
    v3 = std::move(v1);
    assert(v3.size() == 3);
    assert(v3[0] == 100);
    assert(v1.size() == 0); // v1被置空
    print_info(v3, "v3 (移动赋值 v1 后)");
    print_info(v1, "v1 (被移动后)");

    // 自赋值
    v3 = v3;
    assert(v3.size() == 3);
    assert(v3[1] == 200);
    print_info(v3, "v3 (自赋值后)");
    v3 = std::move(v3);
    assert(v3.size() == 3);
    print_info(v3, "v3 (自移动赋值后)");
}

// 3. 测试容量和修改器
void test_modifiers_and_capacity()
{
    std::cout << "\n=== 3. 测试容量和修改器 ===\n";
    vector<int> v;

    // 测试 reserve
    v.reserve(10);
    assert(v.capacity() >= 10);
    assert(v.size() == 0);
    print_info(v, "v (reserve(10)后)");

    // 测试 emplace_back 和扩容
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    assert(v.size() == 3);
    print_info(v, "v (emplace_back 后)");

    // 测试 insert（使用迭代器版本）
    auto it1 = v.insert(v.begin() + 1, 99); // 在中间插入
    assert(v.size() == 4);
    assert(v[1] == 99 && v[2] == 2);
    assert(*it1 == 99);  // 检查返回的迭代器
    print_info(v, "v (insert在位置1插入99后)");

    auto it2 = v.insert(v.begin(), 88); // 在头部插入
    assert(v[0] == 88);
    assert(*it2 == 88);
    print_info(v, "v (insert在头部插入88后)");

    auto it3 = v.insert(v.end(), 77); // 在尾部插入
    assert(v[v.size() - 1] == 77);
    assert(*it3 == 77);
    print_info(v, "v (尾部insert后)");

    // 测试 pop_back
    v.pop_back();
    assert(v.size() == 5);
    print_info(v, "v (pop_back后)");

    // 测试 clear
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() >= 10); // capacity 保持不变
    print_info(v, "v (clear后)");
}

// 4. 测试边界和异常情况
void test_edge_cases()
{
    std::cout << "\n=== 4. 测试边界和异常情况 ===\n";
    vector<int> v;

    // 对空 vector 操作
    v.pop_back(); // 不应崩溃
    assert(v.size() == 0);
    print_info(v, "v (空vector pop_back后)");

    // 触发多次扩容
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    assert(v.size() == 100);
    assert(v[99] == 99);
    print_info(v, "v (100次push_back后)");

    // 测试 operator[] 越界 (应抛异常)
    try
    {
        v[100]; // 越界访问
        assert(false); // 如果没抛异常，测试失败
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获异常: " << e.what() << std::endl;
    }
}

// 5. 测试非基础数据类型 (std::string)
void test_string_vector()
{
    std::cout << "\n=== 5. 测试非基础数据类型 (std::string) ===\n";
    vector<std::string> vs;

    // 测试 push_back (const L-value)
    std::string s1 = "hello";
    vs.push_back(s1);
    print_info(vs, "vs (push_back L-value)");

    // 测试 push_back (R-value)
    vs.push_back("world");
    print_info(vs, "vs (push_back R-value)");

    // 测试 emplace_back
    vs.emplace_back(5, '!'); // "!!!!!"
    assert(vs[2] == "!!!!!");
    print_info(vs, "vs (emplace_back后)");

    // 测试 insert (移动版本)
    auto insert_it = vs.insert(vs.begin(), "Start");
    assert(vs[0] == "Start");
    assert(*insert_it == "Start");
    print_info(vs, "vs (insert后)");

    // 测试拷贝构造
    vector<std::string> vs2(vs);
    assert(vs2.size() == vs.size());
    assert(vs2[1] == "hello");
    print_info(vs2, "vs2 (拷贝构造)");

    // 测试移动赋值
    vs = std::move(vs2);
    assert(vs2.size() == 0);
    print_info(vs, "vs (移动赋值后)");
    print_info(vs2, "vs2 (被移动后)");
}

// 6. 测试erase函数
void test_erase()
{
    std::cout << "\n=== 6. 测试erase函数 ===\n";

    // 创建测试vector
    vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);  // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    }
    print_info(v, "v (初始状态)");

    // 测试删除中间元素（使用迭代器版本）
    auto erase_it1 = v.erase(v.begin() + 5);  // 删除索引5的元素
    assert(v.size() == 9);
    assert(v[5] == 6);  // 原来的6现在位于索引5
    assert(erase_it1 == v.begin() + 5);  // 检查返回的迭代器
    print_info(v, "v (删除索引5后)");  // [0, 1, 2, 3, 4, 6, 7, 8, 9]

    // 测试删除第一个元素
    auto erase_it2 = v.erase(v.begin());
    assert(v.size() == 8);
    assert(v[0] == 1);
    assert(erase_it2 == v.begin());
    print_info(v, "v (删除第一个元素后)");  // [1, 2, 3, 4, 6, 7, 8, 9]

    // 测试删除最后一个元素
    auto erase_it3 = v.erase(v.end() - 1);
    assert(v.size() == 7);
    assert(v[v.size() - 1] == 8);
    assert(erase_it3 == v.end());  // 删除最后元素后，迭代器指向新的end
    print_info(v, "v (删除最后元素后)");  // [1, 2, 3, 4, 6, 7, 8]

    // 测试范围删除 - 删除中间几个元素
    auto erase_it4 = v.erase(v.begin() + 2, v.begin() + 5);  // 删除索引2到4的元素 [3, 4, 6]
    assert(v.size() == 4);
    assert(v[0] == 1 && v[1] == 2 && v[2] == 7 && v[3] == 8);
    assert(erase_it4 == v.begin() + 2);  // 检查返回的迭代器
    print_info(v, "v (删除范围后)");  // [1, 2, 7, 8]

    // 测试空范围删除
    auto old_size = v.size();
    auto empty_it = v.begin() + 1;
    auto erase_it5 = v.erase(empty_it, empty_it);  // 空范围，不应删除任何元素
    assert(v.size() == old_size);
    assert(erase_it5 == empty_it);
    print_info(v, "v (空范围删除后)");

    // 测试删除剩余所有元素
    auto erase_it6 = v.erase(v.begin(), v.end());
    assert(v.size() == 0);
    assert(erase_it6 == v.end());
    print_info(v, "v (删除全部元素后)");

    // 测试异常情况（使用迭代器版本）
    try
    {
        v.erase(v.begin());  // 对空vector删除
        assert(false);  // 不应该到达这里
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获空vector删除异常: " << e.what() << std::endl;
    }

    // 重新填充数据测试越界
    v.push_back(100);
    v.push_back(200);
    v.push_back(300);

    try
    {
        v.erase(v.end());  // 越界删除（end()位置）
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获越界删除异常: " << e.what() << std::endl;
    }

    try
    {
        v.erase(v.begin() + 1, v.end() + 1);  // 范围越界
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获范围越界异常: " << e.what() << std::endl;
    }

    try
    {
        v.erase(v.begin() + 2, v.begin() + 1);  // 无效范围 (first > last)
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获无效范围异常: " << e.what() << std::endl;
    }
}

// 7. 测试erase函数与string类型
void test_erase_with_strings()
{
    std::cout << "\n=== 7. 测试erase函数与string类型 ===\n";

    vector<std::string> vs;
    vs.push_back("hello");
    vs.push_back("world");
    vs.push_back("test");
    vs.push_back("erase");
    vs.push_back("function");
    print_info(vs, "vs (初始状态)");

    // 删除中间字符串（使用迭代器版本）
    auto str_it1 = vs.erase(vs.begin() + 2);  // 删除"test"
    assert(vs.size() == 4);
    assert(vs[2] == "erase");
    assert(str_it1 == vs.begin() + 2);
    print_info(vs, "vs (删除'test'后)");

    // 范围删除
    auto str_it2 = vs.erase(vs.begin() + 1, vs.begin() + 3);  // 删除"world"和"erase"
    assert(vs.size() == 2);
    assert(vs[0] == "hello" && vs[1] == "function");
    assert(str_it2 == vs.begin() + 1);
    print_info(vs, "vs (范围删除后)");
}

// 8. 测试反向迭代器
void test_reverse_iterators()
{
    std::cout << "\n=== 8. 测试反向迭代器 ===\n";

    // 创建测试vector
    vector<int> v;
    for (int i = 1; i <= 5; ++i)
    {
        v.push_back(i);  // [1, 2, 3, 4, 5]
    }
    print_info(v, "v (初始状态)");

    // 测试基础反向迭代
    std::cout << "反向遍历元素: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 const 反向迭代器
    const vector<int>& cv = v;
    std::cout << "const反向遍历元素: ";
    for (auto it = cv.rbegin(); it != cv.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试反向迭代器的修改操作
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        *it *= 10;  // 将每个元素乘以10
    }
    std::cout << "修改后反向遍历: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    print_info(v, "v (修改后)");

    // 测试反向迭代器的算术操作
    auto it = v.rbegin();
    assert(*it == 50);  // 最后一个元素

    ++it;
    assert(*it == 40);  // 倒数第二个元素

    it += 2;
    assert(*it == 20);  // 倒数第四个元素

    --it;
    assert(*it == 30);  // 倒数第三个元素

    it -= 1;
    assert(*it == 40);  // 倒数第二个元素

    // 测试反向迭代器的随机访问
    auto start_it = v.rbegin();
    assert(start_it[0] == 50);  // 第一个（最后一个）
    assert(start_it[1] == 40);  // 第二个（倒数第二个）
    assert(start_it[4] == 10);  // 第五个（第一个）

    // 测试反向迭代器的比较操作
    auto it1 = v.rbegin();
    auto it2 = v.rbegin();
    auto it3 = v.rend();

    assert(it1 == it2);
    assert(it1 != it3);
    assert(it1 < it3);
    assert(it3 > it1);
    assert(it1 <= it2);
    assert(it1 >= it2);

    // 测试反向迭代器的距离计算
    auto distance = v.rend() - v.rbegin();
    assert(distance == static_cast<ptrdiff_t>(v.size()));

    std::cout << "反向迭代器基础测试通过!" << std::endl;
}

// 9. 测试反向迭代器与string类型
void test_reverse_iterators_with_strings()
{
    std::cout << "\n=== 9. 测试反向迭代器与string类型 ===\n";

    vector<std::string> vs;
    vs.push_back("first");
    vs.push_back("second");
    vs.push_back("third");
    vs.push_back("fourth");
    print_info(vs, "vs (初始状态)");

    // 反向遍历字符串
    std::cout << "反向遍历字符串: ";
    for (auto it = vs.rbegin(); it != vs.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 使用反向迭代器修改字符串
    for (auto it = vs.rbegin(); it != vs.rend(); ++it)
    {
        *it = "modified_" + *it;
    }

    std::cout << "修改后反向遍历: ";
    for (auto it = vs.rbegin(); it != vs.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    print_info(vs, "vs (修改后)");

    // 测试指针访问
    auto it = vs.rbegin();
    std::cout << "使用->访问: " << it->length() << " (长度)" << std::endl;

    std::cout << "反向迭代器字符串测试通过!" << std::endl;
}

// 10. 测试反向迭代器的边界情况
void test_reverse_iterators_edge_cases()
{
    std::cout << "\n=== 10. 测试反向迭代器的边界情况 ===\n";

    // 空vector的反向迭代器
    vector<int> empty_v;
    assert(empty_v.rbegin() == empty_v.rend());
    std::cout << "空vector反向迭代器相等测试通过!" << std::endl;

    // 单元素vector
    vector<int> single_v;
    single_v.push_back(42);

    auto it = single_v.rbegin();
    assert(*it == 42);
    ++it;
    assert(it == single_v.rend());
    std::cout << "单元素vector反向迭代器测试通过!" << std::endl;

    // 测试反向迭代器与正向迭代器的关系
    vector<int> v;
    for (int i = 1; i <= 3; ++i)
    {
        v.push_back(i);  // [1, 2, 3]
    }

    // rbegin应该指向最后一个元素
    assert(*v.rbegin() == *std::prev(v.end()));
    // rend应该指向第一个元素之前的位置
    assert(v.rend().base() == v.begin());

    std::cout << "反向迭代器与正向迭代器关系测试通过!" << std::endl;

    // 使用基于范围的for循环（C++11）进行反向遍历的替代方案
    std::cout << "反向遍历 (手动): ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "反向迭代器边界情况测试通过!" << std::endl;
}

// 11. 测试元素访问接口
void test_element_access()
{
    std::cout << "\n=== 11. 测试元素访问接口 ===\n";

    // 创建测试vector
    vector<int> v;
    for (int i = 10; i <= 50; i += 10)
    {
        v.push_back(i);  // [10, 20, 30, 40, 50]
    }
    print_info(v, "v (初始状态)");

    // 测试 at() 方法
    std::cout << "--- 测试 at() 方法 ---\n";
    assert(v.at(0) == 10);
    assert(v.at(2) == 30);
    assert(v.at(4) == 50);

    // 测试 at() 修改元素
    v.at(1) = 200;
    assert(v.at(1) == 200);
    std::cout << "at()方法访问和修改测试通过!\n";

    // 测试 const at()
    const vector<int>& cv = v;
    assert(cv.at(0) == 10);
    assert(cv.at(1) == 200);
    std::cout << "const at()方法测试通过!\n";

    // 测试 at() 越界异常
    try
    {
        v.at(5);  // 越界访问
        assert(false);  // 不应该到达这里
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获at()越界异常: " << e.what() << std::endl;
    }

    // 测试 front() 和 back() 方法
    std::cout << "--- 测试 front() 和 back() 方法 ---\n";
    assert(v.front() == 10);
    assert(v.back() == 50);
    std::cout << "front(): " << v.front() << ", back(): " << v.back() << std::endl;

    // 测试修改 front() 和 back()
    v.front() = 100;
    v.back() = 500;
    assert(v.front() == 100);
    assert(v.back() == 500);
    print_info(v, "v (修改front和back后)");

    // 测试 const front() 和 back()
    assert(cv.front() == 100);
    assert(cv.back() == 500);
    std::cout << "const front()和back()测试通过!\n";

    // 测试 data() 方法
    std::cout << "--- 测试 data() 方法 ---\n";
    int* ptr = v.data();
    assert(ptr != nullptr);
    assert(*ptr == v[0]);
    assert(*(ptr + 1) == v[1]);

    // 通过 data() 修改元素
    *ptr = 999;
    assert(v[0] == 999);
    std::cout << "data()方法访问和修改测试通过!\n";

    // 测试 const data()
    const int* const_ptr = cv.data();
    assert(const_ptr != nullptr);
    assert(*const_ptr == v[0]);
    assert(*(const_ptr + 2) == v[2]);
    std::cout << "const data()方法测试通过!\n";

    print_info(v, "v (最终状态)");
}

// 12. 测试空容器的元素访问
void test_empty_container_access()
{
    std::cout << "\n=== 12. 测试空容器的元素访问 ===\n";

    vector<int> empty_v;
    assert(empty_v.size() == 0);

    // 测试空容器的 data() 方法
    int* ptr = empty_v.data();
    // data() 对空容器可能返回nullptr，这是允许的
    std::cout << "空容器data()指针: " << (ptr ? "非空" : "空") << std::endl;

    // 测试空容器的异常情况
    try
    {
        empty_v.at(0);
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获空容器at()异常: " << e.what() << std::endl;
    }

    try
    {
        empty_v.front();
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获空容器front()异常: " << e.what() << std::endl;
    }

    try
    {
        empty_v.back();
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获空容器back()异常: " << e.what() << std::endl;
    }

    std::cout << "空容器元素访问测试通过!" << std::endl;
}

// 13. 测试字符串类型的元素访问
void test_string_element_access()
{
    std::cout << "\n=== 13. 测试字符串类型的元素访问 ===\n";

    vector<std::string> vs;
    vs.push_back("first");
    vs.push_back("second");
    vs.push_back("third");
    print_info(vs, "vs (初始状态)");

    // 测试字符串的 at() 方法
    assert(vs.at(0) == "first");
    assert(vs.at(2) == "third");

    // 修改字符串
    vs.at(1) = "modified_second";
    assert(vs.at(1) == "modified_second");

    // 测试 front() 和 back()
    assert(vs.front() == "first");
    assert(vs.back() == "third");

    vs.front() = "new_first";
    vs.back() = "new_third";
    assert(vs.front() == "new_first");
    assert(vs.back() == "new_third");

    // 测试 data() 与字符串
    std::string* str_ptr = vs.data();
    assert(str_ptr != nullptr);
    assert(*str_ptr == vs[0]);

    // 通过指针修改字符串
    *str_ptr = "pointer_modified";
    assert(vs[0] == "pointer_modified");

    print_info(vs, "vs (最终状态)");
    std::cout << "字符串元素访问测试通过!" << std::endl;
}

// 14. 专门测试迭代器版本的 insert 和 erase
void test_iterator_insert_erase()
{
    std::cout << "\n=== 14. 专门测试迭代器版本的 insert 和 erase ===\n";

    vector<int> v;
    for (int i = 0; i < 5; ++i)
    {
        v.push_back(i * 10);  // [0, 10, 20, 30, 40]
    }
    print_info(v, "v (初始状态)");

    // 测试移动版本的 insert
    int value = 99;
    auto it1 = v.insert(v.begin() + 2, std::move(value));
    assert(*it1 == 99);
    assert(v[2] == 99);
    print_info(v, "v (移动insert后)");

    // 测试在多个位置插入
    auto it2 = v.insert(v.begin(), -1);     // 头部插入
    auto it3 = v.insert(v.end(), 999);      // 尾部插入
    assert(*it2 == -1 && v[0] == -1);
    assert(*it3 == 999 && v[v.size() - 1] == 999);
    print_info(v, "v (头尾插入后)");

    // 测试连续删除
    auto erase_it1 = v.erase(v.begin());          // 删除头部
    auto erase_it2 = v.erase(v.end() - 1);        // 删除尾部
    assert(v[0] == 0);  // 原来的第二个元素现在是第一个
    print_info(v, "v (删除头尾后)");

    // 测试批量删除
    auto erase_it3 = v.erase(v.begin() + 1, v.begin() + 4);  // 删除中间三个元素
    assert(erase_it3 == v.begin() + 1);
    print_info(v, "v (批量删除后)");

    // 测试 insert 返回值的正确性
    auto current_size = v.size();
    auto insert_pos = v.begin() + 1;
    auto result_it = v.insert(insert_pos, 555);
    assert(result_it == v.begin() + 1);
    assert(*result_it == 555);
    assert(v.size() == current_size + 1);
    print_info(v, "v (验证insert返回值后)");

    // 测试 erase 返回值的正确性
    auto erase_pos = v.begin() + 1;
    auto result_erase_it = v.erase(erase_pos);
    assert(result_erase_it == v.begin() + 1);
    assert(v.size() == current_size);
    print_info(v, "v (验证erase返回值后)");

    std::cout << "迭代器版本insert和erase测试通过!" << std::endl;
}

// 15. 测试 insert 和 erase 的异常安全性
void test_insert_erase_exceptions()
{
    std::cout << "\n=== 15. 测试 insert 和 erase 的异常安全性 ===\n";

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // 测试无效迭代器的异常
    try
    {
        v.insert(v.end() + 1, 100);  // 超出范围的迭代器
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获insert越界异常: " << e.what() << std::endl;
    }

    try
    {
        v.insert(v.begin() - 1, 100);  // 超出范围的迭代器
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获insert越界异常: " << e.what() << std::endl;
    }

    try
    {
        v.erase(v.end());  // end()位置无法删除
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获erase越界异常: " << e.what() << std::endl;
    }

    try
    {
        v.erase(v.begin() - 1);  // 超出范围的迭代器
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获erase越界异常: " << e.what() << std::endl;
    }

    // 测试无效范围
    try
    {
        v.erase(v.begin() + 2, v.begin() + 1);  // first > last
        assert(false);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "成功捕获无效范围异常: " << e.what() << std::endl;
    }

    std::cout << "insert和erase异常安全性测试通过!" << std::endl;
}

// 16. 测试容量管理和 resize
void test_capacity_and_resize()
{
    std::cout << "\n=== 16. 测试容量管理和 resize ===\n";

    // --- 测试 shrink_to_fit ---
    std::cout << "--- 测试 shrink_to_fit ---\n";
    vector<int> v1;
    v1.reserve(100);
    assert(v1.capacity() >= 100);
    assert(v1.size() == 0);

    for (int i = 0; i < 10; ++i)
    {
        v1.push_back(i);
    }
    print_info(v1, "v1 (reserve并添加元素后)");
    assert(v1.capacity() >= 100);

    v1.shrink_to_fit();
    assert(v1.capacity() == 10);
    assert(v1.size() == 10);
    assert(v1[9] == 9);
    print_info(v1, "v1 (shrink_to_fit后)");

    // 测试对空vector进行shrink_to_fit
    vector<int> v_empty;
    v_empty.reserve(10);
    v_empty.shrink_to_fit();
    assert(v_empty.capacity() == 0);
    assert(v_empty.size() == 0);
    print_info(v_empty, "v_empty (shrink_to_fit后)");

    // --- 测试 resize ---
    std::cout << "\n--- 测试 resize ---\n";
    vector<std::string> vs;
    vs.push_back("a");
    vs.push_back("b");
    vs.push_back("c");
    vs.push_back("d");
    vs.push_back("e");
    print_info(vs, "vs (初始状态)");

    // 测试缩小 (shrink)
    vs.resize(3);
    assert(vs.size() == 3);
    assert(vs.capacity() >= 5);
    assert(vs.back() == "c");
    print_info(vs, "vs (resize to 3)");

    // 测试扩大 (grow) 到同一值
    vs.resize(5, "X");
    assert(vs.size() == 5);
    assert(vs[3] == "X" && vs[4] == "X");
    print_info(vs, "vs (resize to 5 with 'X')");

    // 测试扩大并重新分配
    vs.resize(10, "Y");
    assert(vs.size() == 10);
    assert(vs.capacity() >= 10);
    assert(vs.back() == "Y");
    print_info(vs, "vs (resize to 10 with 'Y')");

    // 测试使用默认值的resize
    vector<int> v2;
    v2.push_back(1);
    v2.resize(5); // 应该用0填充
    assert(v2.size() == 5);
    assert(v2[0] == 1);
    assert(v2[1] == 0 && v2[2] == 0 && v2[3] == 0 && v2[4] == 0);
    print_info(v2, "v2 (resize with default value)");

    v2.resize(2);
    assert(v2.size() == 2);
    assert(v2[1] == 0);
    print_info(v2, "v2 (resize to 2)");

    std::cout << "容量管理和resize测试通过!" << std::endl;
}

// 17. 测试比较操作符重载
void test_comparison_operators()
{
    std::cout << "\n=== 17. 测试比较操作符重载 ===\n";

    // 创建测试vectors
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    // 相同内容的vectors
    for (int i = 1; i <= 3; ++i)
    {
        v1.push_back(i);
        v2.push_back(i);
    }

    // 不同内容的vector
    v3.push_back(1);
    v3.push_back(2);
    v3.push_back(4);  // 最后一个元素不同

    print_info(v1, "v1");
    print_info(v2, "v2");
    print_info(v3, "v3");

    // 测试相等比较
    std::cout << "--- 测试相等比较 ---\n";
    assert(v1 == v2);
    assert(!(v1 == v3));
    assert(!(v1 != v2));
    assert(v1 != v3);
    std::cout << "v1 == v2: " << (v1 == v2) << std::endl;
    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1 != v3: " << (v1 != v3) << std::endl;

    // 测试大小比较
    std::cout << "--- 测试大小比较 ---\n";
    assert(v1 < v3);   // [1,2,3] < [1,2,4]
    assert(!(v3 < v1));
    assert(v3 > v1);
    assert(!(v1 > v3));
    assert(v1 <= v2);  // 相等情况
    assert(v1 <= v3);  // 小于情况
    assert(v2 >= v1);  // 相等情况
    assert(v3 >= v1);  // 大于情况

    std::cout << "v1 < v3: " << (v1 < v3) << std::endl;
    std::cout << "v3 > v1: " << (v3 > v1) << std::endl;
    std::cout << "v1 <= v2: " << (v1 <= v2) << std::endl;
    std::cout << "v3 >= v1: " << (v3 >= v1) << std::endl;

    // 测试不同长度的vectors
    std::cout << "--- 测试不同长度的vectors ---\n";
    vector<int> v_short;
    vector<int> v_long;

    v_short.push_back(1);
    v_short.push_back(2);

    v_long.push_back(1);
    v_long.push_back(2);
    v_long.push_back(3);

    assert(v_short != v_long);
    assert(v_short < v_long);   // 短的vector小于长的vector（当前缀相同时）
    assert(!(v_long < v_short));
    assert(v_long > v_short);
    assert(v_short <= v_long);
    assert(v_long >= v_short);

    print_info(v_short, "v_short");
    print_info(v_long, "v_long");
    std::cout << "v_short < v_long: " << (v_short < v_long) << std::endl;

    // 测试空vectors
    std::cout << "--- 测试空vectors ---\n";
    vector<int> v_empty1;
    vector<int> v_empty2;

    assert(v_empty1 == v_empty2);
    assert(!(v_empty1 != v_empty2));
    assert(!(v_empty1 < v_empty2));
    assert(!(v_empty1 > v_empty2));
    assert(v_empty1 <= v_empty2);
    assert(v_empty1 >= v_empty2);

    // 空vector与非空vector比较
    assert(v_empty1 != v1);
    assert(v_empty1 < v1);
    assert(!(v1 < v_empty1));
    assert(v1 > v_empty1);

    std::cout << "空vector比较测试通过!" << std::endl;

    // 测试字符串vectors的比较
    std::cout << "--- 测试字符串vectors的比较 ---\n";
    vector<std::string> vs1;
    vector<std::string> vs2;
    vector<std::string> vs3;

    vs1.push_back("apple");
    vs1.push_back("banana");

    vs2.push_back("apple");
    vs2.push_back("banana");

    vs3.push_back("apple");
    vs3.push_back("cherry");  // "cherry" > "banana"

    assert(vs1 == vs2);
    assert(vs1 != vs3);
    assert(vs1 < vs3);  // "banana" < "cherry"
    assert(vs3 > vs1);

    print_info(vs1, "vs1");
    print_info(vs3, "vs3");
    std::cout << "vs1 < vs3: " << (vs1 < vs3) << std::endl;

    std::cout << "比较操作符重载测试通过!" << std::endl;
}

// 18. 测试const迭代器
void test_const_iterators()
{
    std::cout << "\n=== 18. 测试const迭代器 ===\n";

    // 创建测试vector
    vector<int> v;
    for (int i = 10; i <= 50; i += 10)
    {
        v.push_back(i);  // [10, 20, 30, 40, 50]
    }
    print_info(v, "v (初始状态)");

    // 测试 cbegin() 和 cend()
    std::cout << "--- 测试 cbegin() 和 cend() ---\n";
    std::cout << "使用cbegin()和cend()遍历: ";
    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 验证cbegin()和cend()返回const_iterator
    auto c_it = v.cbegin();
    assert(*c_it == 10);
    // c_it指向的内容不能修改（这在编译时检查）
    // *c_it = 100;  // 这行如果取消注释会导致编译错误

    // 测试const vector的cbegin()和cend()
    const vector<int>& cv = v;
    std::cout << "const vector使用cbegin()和cend()遍历: ";
    for (auto it = cv.cbegin(); it != cv.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 crbegin() 和 crend()
    std::cout << "--- 测试 crbegin() 和 crend() ---\n";
    std::cout << "使用crbegin()和crend()反向遍历: ";
    for (auto it = v.crbegin(); it != v.crend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 验证crbegin()和crend()返回const_reverse_iterator
    auto cr_it = v.crbegin();
    assert(*cr_it == 50);  // 最后一个元素
    // cr_it指向的内容不能修改
    // *cr_it = 500;  // 这行如果取消注释会导致编译错误

    // 测试const vector的crbegin()和crend()
    std::cout << "const vector使用crbegin()和crend()反向遍历: ";
    for (auto it = cv.crbegin(); it != cv.crend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试const迭代器的算术操作
    std::cout << "--- 测试const迭代器的算术操作 ---\n";
    auto c_begin = v.cbegin();
    auto c_end = v.cend();

    // 测试距离计算
    auto distance = c_end - c_begin;
    assert(distance == static_cast<ptrdiff_t>(v.size()));
    std::cout << "cend() - cbegin() = " << distance << std::endl;

    // 测试随机访问
    auto c_it2 = c_begin + 2;
    assert(*c_it2 == 30);
    std::cout << "*(cbegin() + 2) = " << *c_it2 << std::endl;

    // 测试const反向迭代器的算术操作
    auto cr_begin = v.crbegin();
    auto cr_end = v.crend();

    auto cr_distance = cr_end - cr_begin;
    assert(cr_distance == static_cast<ptrdiff_t>(v.size()));
    std::cout << "crend() - crbegin() = " << cr_distance << std::endl;

    auto cr_it2 = cr_begin + 1;
    assert(*cr_it2 == 40);  // 倒数第二个元素
    std::cout << "*(crbegin() + 1) = " << *cr_it2 << std::endl;

    // 测试const迭代器与普通迭代器的兼容性
    std::cout << "--- 测试const迭代器与普通迭代器的兼容性 ---\n";
    assert(v.cbegin() == v.begin());
    assert(v.cend() == v.end());
    assert(v.crbegin() == v.rbegin());
    assert(v.crend() == v.rend());
    std::cout << "const迭代器与普通迭代器相等性测试通过!" << std::endl;

    // 测试空vector的const迭代器
    std::cout << "--- 测试空vector的const迭代器 ---\n";
    vector<int> empty_v;
    assert(empty_v.cbegin() == empty_v.cend());
    assert(empty_v.crbegin() == empty_v.crend());
    std::cout << "空vector的const迭代器测试通过!" << std::endl;

    // 测试字符串vector的const迭代器
    std::cout << "--- 测试字符串vector的const迭代器 ---\n";
    vector<std::string> vs;
    vs.push_back("first");
    vs.push_back("second");
    vs.push_back("third");

    std::cout << "字符串vector使用cbegin()和cend()遍历: ";
    for (auto it = vs.cbegin(); it != vs.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "字符串vector使用crbegin()和crend()反向遍历: ";
    for (auto it = vs.crbegin(); it != vs.crend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试const迭代器的指针访问
    auto str_c_it = vs.cbegin();
    std::cout << "使用const迭代器->访问字符串长度: " << str_c_it->length() << std::endl;

    std::cout << "const迭代器测试通过!" << std::endl;
}

// 19. 测试自定义分配器
void test_custom_allocator()
{
    std::cout << "\n=== 19. 测试自定义分配器 ===\n";

    // 重置分配器统计
    tracking_allocator<int>::reset_stats();

    {
        // 创建使用自定义分配器的vector
        vector<int, tracking_allocator<int>> v;

        std::cout << "--- 测试基础操作 ---\n";

        // 测试 push_back
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);

        assert(v.size() == 3);
        assert(v[0] == 1 && v[1] == 2 && v[2] == 3);
        print_info(v, "自定义分配器vector");

        // 测试 reserve
        std::cout << "\n--- 测试 reserve ---\n";
        v.reserve(10);
        assert(v.capacity() >= 10);
        print_info(v, "reserve后");

        // 测试拷贝构造
        std::cout << "\n--- 测试拷贝构造 ---\n";
        vector<int, tracking_allocator<int>> v2(v);
        assert(v2.size() == 3);
        assert(v2[1] == 2);
        print_info(v2, "拷贝构造的vector");

        // 测试移动构造
        std::cout << "\n--- 测试移动构造 ---\n";
        vector<int, tracking_allocator<int>> v3(std::move(v2));
        assert(v3.size() == 3);
        assert(v2.size() == 0);  // v2被移动后应该为空
        print_info(v3, "移动构造的vector");
        print_info(v2, "被移动的vector");

        // 测试分配器访问
        std::cout << "\n--- 测试分配器访问 ---\n";
        auto alloc = v.get_allocator();
        std::cout << "成功获取分配器对象" << std::endl;

        // 测试 insert 和 erase
        std::cout << "\n--- 测试 insert 和 erase ---\n";
        v.insert(v.begin() + 1, 99);
        assert(v[1] == 99);
        print_info(v, "insert后");

        v.erase(v.begin() + 1);
        assert(v[1] == 2);
        print_info(v, "erase后");

        std::cout << "\n--- 块结束前的统计 ---\n";
        tracking_allocator<int>::print_stats();
    }

    std::cout << "\n--- 所有对象析构后的统计 ---\n";
    tracking_allocator<int>::print_stats();

    // 验证内存分配和释放是否匹配
    assert(tracking_allocator<int>::allocations == tracking_allocator<int>::deallocations);
    std::cout << "✅ 内存分配和释放匹配!" << std::endl;
}

// 20. 测试带分配器的构造函数
void test_allocator_constructors()
{
    std::cout << "\n=== 20. 测试带分配器的构造函数 ===\n";

    tracking_allocator<std::string>::reset_stats();

    {
        // 测试分配器构造函数
        tracking_allocator<std::string> alloc;
        vector<std::string, tracking_allocator<std::string>> v1(alloc);
        assert(v1.size() == 0);
        print_info(v1, "分配器构造的vector");

        // 测试带分配器的大小构造函数
        vector<std::string, tracking_allocator<std::string>> v2(3, alloc);
        assert(v2.size() == 3);
        print_info(v2, "大小+分配器构造的vector");

        // 测试带分配器的大小+值构造函数
        vector<std::string, tracking_allocator<std::string>> v3(2, "hello", alloc);
        assert(v3.size() == 2);
        assert(v3[0] == "hello" && v3[1] == "hello");
        print_info(v3, "大小+值+分配器构造的vector");

        // 测试带分配器的初始化列表构造函数
        vector<std::string, tracking_allocator<std::string>> v4({ "first", "second", "third" }, alloc);
        assert(v4.size() == 3);
        assert(v4[0] == "first" && v4[2] == "third");
        print_info(v4, "初始化列表+分配器构造的vector");

        // 测试带分配器的范围构造函数
        std::vector<std::string> std_vec = { "a", "b", "c" };
        vector<std::string, tracking_allocator<std::string>> v5(std_vec.begin(), std_vec.end(), alloc);
        assert(v5.size() == 3);
        assert(v5[1] == "b");
        print_info(v5, "范围+分配器构造的vector");

        // 测试带分配器的拷贝构造函数
        vector<std::string, tracking_allocator<std::string>> v6(v4, alloc);
        assert(v6.size() == v4.size());
        assert(v6[0] == v4[0]);
        print_info(v6, "拷贝+分配器构造的vector");

        // 测试带分配器的移动构造函数（相同分配器）
        vector<std::string, tracking_allocator<std::string>> v7(std::move(v6), alloc);
        assert(v7.size() == 3);
        assert(v6.size() == 0);  // v6被移动后应为空
        print_info(v7, "移动+分配器构造的vector");
        print_info(v6, "被移动的vector");

        tracking_allocator<std::string>::print_stats();
    }

    std::cout << "\n--- 所有对象析构后的统计 ---\n";
    tracking_allocator<std::string>::print_stats();

    // 验证内存分配和释放是否匹配
    assert(tracking_allocator<std::string>::allocations == tracking_allocator<std::string>::deallocations);
    std::cout << "✅ 带分配器构造函数测试通过!" << std::endl;
}

// 21. 测试分配器相关的容量操作
void test_allocator_capacity_operations()
{
    std::cout << "\n=== 21. 测试分配器相关的容量操作 ===\n";

    tracking_allocator<int>::reset_stats();

    {
        vector<int, tracking_allocator<int>> v;

        // 测试多次 push_back 触发重新分配
        std::cout << "--- 测试自动扩容 ---\n";
        for (int i = 0; i < 10; ++i)
        {
            v.push_back(i);
            std::cout << "push_back(" << i << "), size: " << v.size()
                << ", capacity: " << v.capacity() << std::endl;
        }

        // 测试 shrink_to_fit
        std::cout << "\n--- 测试 shrink_to_fit ---\n";
        size_t old_capacity = v.capacity();
        v.shrink_to_fit();
        assert(v.capacity() <= old_capacity);
        assert(v.size() == 10);
        print_info(v, "shrink_to_fit后");

        // 测试 resize
        std::cout << "\n--- 测试 resize ---\n";
        v.resize(15, 99);
        assert(v.size() == 15);
        assert(v[14] == 99);
        print_info(v, "resize扩大后");

        v.resize(5);
        assert(v.size() == 5);
        print_info(v, "resize缩小后");

        // 测试 clear
        std::cout << "\n--- 测试 clear ---\n";
        v.clear();
        assert(v.size() == 0);
        print_info(v, "clear后");

        tracking_allocator<int>::print_stats();
    }

    std::cout << "\n--- 所有对象析构后的统计 ---\n";
    tracking_allocator<int>::print_stats();

    assert(tracking_allocator<int>::allocations == tracking_allocator<int>::deallocations);
    std::cout << "✅ 分配器容量操作测试通过!" << std::endl;
}

// 22. 测试分配器的swap和赋值操作
void test_allocator_swap_assignment()
{
    std::cout << "\n=== 22. 测试分配器的swap和赋值操作 ===\n";

    tracking_allocator<int>::reset_stats();

    {
        // 创建两个不同的vector
        vector<int, tracking_allocator<int>> v1;
        vector<int, tracking_allocator<int>> v2;

        // 填充数据
        for (int i = 0; i < 5; ++i)
        {
            v1.push_back(i);
        }
        for (int i = 10; i < 15; ++i)
        {
            v2.push_back(i);
        }

        print_info(v1, "swap前的v1");
        print_info(v2, "swap前的v2");

        // 测试 swap
        std::cout << "\n--- 测试 swap ---\n";
        v1.swap(v2);
        assert(v1.size() == 5 && v1[0] == 10);
        assert(v2.size() == 5 && v2[0] == 0);
        print_info(v1, "swap后的v1");
        print_info(v2, "swap后的v2");

        // 测试非成员swap
        std::cout << "\n--- 测试非成员swap ---\n";
        swap(v1, v2);
        assert(v1.size() == 5 && v1[0] == 0);
        assert(v2.size() == 5 && v2[0] == 10);
        print_info(v1, "非成员swap后的v1");
        print_info(v2, "非成员swap后的v2");

        // 测试拷贝赋值
        std::cout << "\n--- 测试拷贝赋值 ---\n";
        vector<int, tracking_allocator<int>> v3;
        v3.push_back(999);
        print_info(v3, "赋值前的v3");

        v3 = v1;
        assert(v3.size() == v1.size());
        assert(v3[2] == v1[2]);
        print_info(v3, "拷贝赋值后的v3");

        // 测试移动赋值
        std::cout << "\n--- 测试移动赋值 ---\n";
        vector<int, tracking_allocator<int>> v4;
        v4.push_back(888);
        print_info(v4, "移动赋值前的v4");

        v4 = std::move(v2);
        assert(v4.size() == 5 && v4[0] == 10);
        assert(v2.size() == 0);  // v2被移动后应为空
        print_info(v4, "移动赋值后的v4");
        print_info(v2, "被移动的v2");

        tracking_allocator<int>::print_stats();
    }

    std::cout << "\n--- 所有对象析构后的统计 ---\n";
    tracking_allocator<int>::print_stats();

    assert(tracking_allocator<int>::allocations == tracking_allocator<int>::deallocations);
    std::cout << "✅ 分配器swap和赋值操作测试通过!" << std::endl;
}

// 23. 测试分配器与标准分配器的兼容性
void test_allocator_compatibility()
{
    std::cout << "\n=== 23. 测试分配器与标准分配器的兼容性 ===\n";

    // 测试默认分配器（std::allocator）
    std::cout << "--- 测试默认分配器 ---\n";
    vector<int> std_alloc_vec;  // 使用默认的std::allocator
    std_alloc_vec.push_back(1);
    std_alloc_vec.push_back(2);
    std_alloc_vec.push_back(3);

    assert(std_alloc_vec.size() == 3);
    assert(std_alloc_vec[1] == 2);
    print_info(std_alloc_vec, "标准分配器vector");

    // 测试默认分配器的所有操作
    std_alloc_vec.reserve(10);
    std_alloc_vec.resize(5, 99);
    std_alloc_vec.insert(std_alloc_vec.begin(), 0);
    std_alloc_vec.erase(std_alloc_vec.end() - 1);

    assert(std_alloc_vec.front() == 0);
    assert(std_alloc_vec.back() == 99);
    print_info(std_alloc_vec, "操作后的标准分配器vector");

    // 测试比较操作
    std::cout << "--- 测试不同分配器类型间的比较 ---\n";
    vector<int> v1 = { 1, 2, 3 };
    vector<int> v2 = { 1, 2, 3 };
    vector<int> v3 = { 1, 2, 4 };

    assert(v1 == v2);
    assert(v1 != v3);
    assert(v1 < v3);
    std::cout << "✅ 比较操作正常工作" << std::endl;

    // 测试类型别名
    std::cout << "--- 测试类型别名 ---\n";
    vector<std::string>::allocator_type alloc = std_alloc_vec.get_allocator();
    vector<std::string>::size_type sz = 0;
    vector<std::string>::value_type val = "test";
    std::cout << "✅ 类型别名定义正确" << std::endl;

    std::cout << "✅ 分配器兼容性测试通过!" << std::endl;
}

// 24. 测试allocator_traits的基础功能
void test_allocator_traits()
{
    std::cout << "\n=== 24. 测试allocator_traits的基础功能 ===\n";

    // 测试allocator_traits类型特征
    std::cout << "--- 测试allocator_traits类型特征 ---\n";

    typedef vector<int>::allocator_type alloc_type;
    typedef vector<int>::allocator_traits traits_type;

    // 验证类型特征
    static_assert(std::is_same_v<traits_type::value_type, int>, "value_type应该是int");
    static_assert(std::is_same_v<traits_type::allocator_type, std::allocator<int>>, "allocator_type应该是std::allocator<int>");

    std::cout << "✅ allocator_traits类型特征正确" << std::endl;

    // 测试基础的allocator_traits功能
    std::cout << "--- 测试基础的allocator_traits功能 ---\n";

    vector<std::string> v;

    // 测试基础操作
    v.push_back("first");
    v.push_back("second");
    v.emplace_back("third");

    assert(v.size() == 3);
    assert(v[0] == "first");
    assert(v[1] == "second");
    assert(v[2] == "third");
    print_info(v, "allocator_traits基础操作");

    // 测试容量管理
    v.reserve(10);
    assert(v.capacity() >= 10);
    v.resize(5, "default");
    assert(v.size() == 5);
    assert(v[4] == "default");
    print_info(v, "容量管理后");

    // 测试插入和删除
    auto it = v.insert(v.begin() + 1, "inserted");
    assert(*it == "inserted");
    assert(v[1] == "inserted");

    v.erase(v.begin() + 1);
    assert(v[1] == "second");
    print_info(v, "插入删除后");

    std::cout << "✅ allocator_traits基础功能测试通过!" << std::endl;
}

// 25. 测试allocator_traits与自定义分配器的配合
void test_allocator_traits_with_custom_allocator()
{
    std::cout << "\n=== 25. 测试allocator_traits与自定义分配器的配合 ===\n";

    tracking_allocator<int>::reset_stats();

    {
        std::cout << "--- 测试自定义分配器的allocator_traits ---\n";

        typedef vector<int, tracking_allocator<int>>::allocator_traits custom_traits;

        // 验证自定义分配器的traits
        static_assert(std::is_same_v<custom_traits::value_type, int>, "value_type应该是int");
        static_assert(std::is_same_v<custom_traits::allocator_type, tracking_allocator<int>>, "allocator_type应该是tracking_allocator<int>");

        vector<int, tracking_allocator<int>> v;

        // 测试构造和析构的正确跟踪
        std::cout << "\n--- 测试构造和析构跟踪 ---\n";

        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        tracking_allocator<int>::print_stats();

        // 测试emplace_back
        v.emplace_back(4);
        v.emplace_back(5);
        assert(v.size() == 5);
        tracking_allocator<int>::print_stats();

        // 测试insert
        v.insert(v.begin() + 2, 99);
        assert(v[2] == 99);
        tracking_allocator<int>::print_stats();

        // 测试erase
        v.erase(v.begin() + 2);
        assert(v[2] == 3);
        tracking_allocator<int>::print_stats();

        // 测试resize
        v.resize(10, 88);
        assert(v.size() == 10);
        assert(v[9] == 88);
        tracking_allocator<int>::print_stats();

        // 测试shrink_to_fit
        v.shrink_to_fit();
        assert(v.capacity() == 10);
        tracking_allocator<int>::print_stats();

        print_info(v, "自定义分配器测试完成");
    }

    std::cout << "\n--- 析构后的统计 ---\n";
    tracking_allocator<int>::print_stats();

    // 验证没有内存泄漏
    assert(tracking_allocator<int>::allocations == tracking_allocator<int>::deallocations);
    std::cout << "✅ 自定义分配器的allocator_traits测试通过!" << std::endl;
}

// 26. 测试allocator_traits的边界情况
void test_allocator_traits_edge_cases()
{
    std::cout << "\n=== 26. 测试allocator_traits的边界情况 ===\n";

    tracking_allocator<std::string>::reset_stats();

    {
        // 测试复杂类型（std::string）的allocator_traits
        std::cout << "--- 测试复杂类型的allocator_traits ---\n";

        vector<std::string, tracking_allocator<std::string>> v;

        // 测试大量插入和删除操作
        for (int i = 0; i < 20; ++i)
        {
            v.push_back("item_" + std::to_string(i));
        }
        assert(v.size() == 20);
        tracking_allocator<std::string>::print_stats();

        // 测试范围删除
        v.erase(v.begin() + 5, v.begin() + 15);
        assert(v.size() == 10);
        tracking_allocator<std::string>::print_stats();

        // 测试clear
        v.clear();
        assert(v.size() == 0);
        tracking_allocator<std::string>::print_stats();

        // 测试重新填充
        v.resize(5, "new_item");
        assert(v.size() == 5);
        assert(v[0] == "new_item");
        tracking_allocator<std::string>::print_stats();

        // 测试拷贝构造
        vector<std::string, tracking_allocator<std::string>> v2(v);
        assert(v2.size() == v.size());
        assert(v2[0] == v[0]);
        tracking_allocator<std::string>::print_stats();

        // 测试移动构造
        vector<std::string, tracking_allocator<std::string>> v3(std::move(v2));
        assert(v3.size() == 5);
        assert(v2.size() == 0);
        tracking_allocator<std::string>::print_stats();

        // 测试赋值操作
        v = v3;
        assert(v.size() == 5);
        tracking_allocator<std::string>::print_stats();

        print_info(v, "复杂类型测试完成");
        print_info(v2, "被移动的vector");
        print_info(v3, "移动构造的vector");
    }

    std::cout << "\n--- 所有对象析构后的统计 ---\n";
    tracking_allocator<std::string>::print_stats();

    // 验证没有内存泄漏
    assert(tracking_allocator<std::string>::allocations == tracking_allocator<std::string>::deallocations);

    // 测试空vector的allocator_traits操作
    std::cout << "\n--- 测试空vector的allocator_traits操作 ---\n";

    tracking_allocator<int>::reset_stats();
    {
        vector<int, tracking_allocator<int>> empty_v;

        // 对空vector的操作不应该分配内存
        empty_v.clear();
        empty_v.shrink_to_fit();
        empty_v.resize(0);

        // 验证没有分配
        assert(tracking_allocator<int>::allocations == 0);
        std::cout << "✅ 空vector操作测试通过" << std::endl;

        // 首次分配测试
        empty_v.push_back(42);
        assert(empty_v[0] == 42);
        assert(tracking_allocator<int>::allocations > 0);
        tracking_allocator<int>::print_stats();
    }

    tracking_allocator<int>::print_stats();
    assert(tracking_allocator<int>::allocations == tracking_allocator<int>::deallocations);

    std::cout << "✅ allocator_traits边界情况测试通过!" << std::endl;
}

int main()
{
    test_constructors();
    test_assignments();
    test_modifiers_and_capacity();
    test_edge_cases();
    test_string_vector();
    test_erase();
    test_erase_with_strings();
    test_reverse_iterators();
    test_reverse_iterators_with_strings();
    test_reverse_iterators_edge_cases();
    test_element_access();
    test_empty_container_access();
    test_string_element_access();
    test_iterator_insert_erase();
    test_insert_erase_exceptions();
    test_capacity_and_resize();
    test_comparison_operators();
    test_const_iterators();
    test_custom_allocator();
    test_allocator_constructors();
    test_allocator_capacity_operations();
    test_allocator_swap_assignment();
    test_allocator_compatibility();
    test_allocator_traits();
    test_allocator_traits_with_custom_allocator();
    test_allocator_traits_edge_cases();

    std::cout << "\n✅ 所有测试用例执行完毕!\n";
    return 0;
}
