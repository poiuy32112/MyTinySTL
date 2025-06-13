#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "vector.h"

// 辅助函数，用于打印 vector 信息
template<typename T>
void print_info(const vector<T>& v, const std::string& name)
{
	std::cout << "--- " << name << " ---" << std::endl;
	std::cout << "Size: " << v.getSize() << ", Capacity: " << v.getCapacity() << std::endl;
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
	assert(v1.getSize() == 0);
	assert(v1.getCapacity() == 0);
	print_info(v1, "v1 (默认构造)");
	
	// push_back
	v1.push_back(10);
	v1.push_back(20);
	assert(v1.getSize() == 2);
	assert(v1[0] == 10 && v1[1] == 20);
	print_info(v1, "v1 (push_back后)");
	
	// 拷贝构造
	vector<int> v2(v1);
	assert(v2.getSize() == 2);
	assert(v2.getCapacity() >= 2);
	assert(v2[0] == 10 && v2[1] == 20);
	// 修改v1不应影响v2
	v1.push_back(30);
	assert(v1[2] == 30);
	assert(v2.getSize() == 2);
	print_info(v1, "v1 (修改后)");
	print_info(v2, "v2 (拷贝构造自 v1)");
	
	// 移动构造
	vector<int> v3(std::move(v2));
	assert(v3.getSize() == 2);
	assert(v3[0] == 10 && v3[1] == 20);
	// v2应被置空
	assert(v2.getSize() == 0);
	assert(v2.getCapacity() == 0);
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
	assert(v1.getSize() == 3);
	assert(v1[1] == 200);
	v2.push_back(400); // 修改v2不应影响v1
	assert(v1.getSize() == 3);
	print_info(v1, "v1 (拷贝赋值 v2 后)");
	
	// 移动赋值
	vector<int> v3;
	v3.push_back(99);
	v3 = std::move(v1);
	assert(v3.getSize() == 3);
	assert(v3[0] == 100);
	assert(v1.getSize() == 0); // v1被置空
	print_info(v3, "v3 (移动赋值 v1 后)");
	print_info(v1, "v1 (被移动后)");

	// 自赋值
	v3 = v3;
	assert(v3.getSize() == 3);
	assert(v3[1] == 200);
	print_info(v3, "v3 (自赋值后)");
	v3 = std::move(v3);
	assert(v3.getSize() == 3);
	print_info(v3, "v3 (自移动赋值后)");
}

// 3. 测试容量和修改器
void test_modifiers_and_capacity()
{
	std::cout << "\n=== 3. 测试容量和修改器 ===\n";
	vector<int> v;
	
	// 测试 reserve
	v.reserve(10);
	assert(v.getCapacity() >= 10);
	assert(v.getSize() == 0);
	print_info(v, "v (reserve(10)后)");
	
	// 测试 emplace_back 和扩容
	v.emplace_back(1);
	v.emplace_back(2);
	v.emplace_back(3);
	assert(v.getSize() == 3);
	print_info(v, "v (emplace_back 后)");
	
	// 测试 insert
	v.insert(1, 99); // 在中间插入
	assert(v.getSize() == 4);
	assert(v[1] == 99 && v[2] == 2);
	print_info(v, "v (insert(1, 99)后)");
	
	v.insert(0, 88); // 在头部插入
	assert(v[0] == 88);
	print_info(v, "v (insert(0, 88)后)");
	
	v.insert(v.getSize(), 77); // 在尾部插入
	assert(v[v.getSize() - 1] == 77);
	print_info(v, "v (尾部insert后)");
	
	// 测试 pop_back
	v.pop_back();
	assert(v.getSize() == 5);
	print_info(v, "v (pop_back后)");
	
	// 测试 clear
	v.clear();
	assert(v.getSize() == 0);
	assert(v.getCapacity() >= 10); // capacity 保持不变
	print_info(v, "v (clear后)");
}

// 4. 测试边界和异常情况
void test_edge_cases()
{
	std::cout << "\n=== 4. 测试边界和异常情况 ===\n";
	vector<int> v;
	
	// 对空 vector 操作
	v.pop_back(); // 不应崩溃
	assert(v.getSize() == 0);
	print_info(v, "v (空vector pop_back后)");
	
	// 触发多次扩容
	for(int i = 0; i < 100; ++i) {
		v.push_back(i);
	}
	assert(v.getSize() == 100);
	assert(v[99] == 99);
	print_info(v, "v (100次push_back后)");
	
	// 测试 operator[] 越界 (应抛异常)
	try {
		v[100]; // 越界访问
		assert(false); // 如果没抛异常，测试失败
	} catch (const std::out_of_range& e) {
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
	vs.insert(0, "Start");
	assert(vs[0] == "Start");
	print_info(vs, "vs (insert后)");
	
	// 测试拷贝构造
	vector<std::string> vs2(vs);
	assert(vs2.getSize() == vs.getSize());
	assert(vs2[1] == "hello");
	print_info(vs2, "vs2 (拷贝构造)");
	
	// 测试移动赋值
	vs = std::move(vs2);
	assert(vs2.getSize() == 0);
	print_info(vs, "vs (移动赋值后)");
	print_info(vs2, "vs2 (被移动后)");
}


int main()
{
    std::cout << "11-----------\n";
    int val = 3;
    int* p = new int(val);
    std::cout << *p << std::endl;
    //p = nullptr;
    delete p;
    //p = nullptr;
    delete p;

	test_constructors();
	test_assignments();
	test_modifiers_and_capacity();
	test_edge_cases();
	test_string_vector();
	
	std::cout << "\n✅ 所有测试用例执行完毕!\n";
	return 0;
}
