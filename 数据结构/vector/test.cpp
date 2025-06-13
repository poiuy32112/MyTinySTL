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
	
	// 测试 insert（使用迭代器版本）
	auto it1 = v.insert(v.begin() + 1, 99); // 在中间插入
	assert(v.getSize() == 4);
	assert(v[1] == 99 && v[2] == 2);
	assert(*it1 == 99);  // 检查返回的迭代器
	print_info(v, "v (insert在位置1插入99后)");
	
	auto it2 = v.insert(v.begin(), 88); // 在头部插入
	assert(v[0] == 88);
	assert(*it2 == 88);
	print_info(v, "v (insert在头部插入88后)");
	
	auto it3 = v.insert(v.end(), 77); // 在尾部插入
	assert(v[v.getSize() - 1] == 77);
	assert(*it3 == 77);
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
	auto insert_it = vs.insert(vs.begin(), "Start");
	assert(vs[0] == "Start");
	assert(*insert_it == "Start");
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

// 6. 测试erase函数
void test_erase()
{
	std::cout << "\n=== 6. 测试erase函数 ===\n";
	
	// 创建测试vector
	vector<int> v;
	for(int i = 0; i < 10; ++i) {
		v.push_back(i);  // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
	}
	print_info(v, "v (初始状态)");
	
	// 测试删除中间元素（使用迭代器版本）
	auto erase_it1 = v.erase(v.begin() + 5);  // 删除索引5的元素
	assert(v.getSize() == 9);
	assert(v[5] == 6);  // 原来的6现在位于索引5
	assert(erase_it1 == v.begin() + 5);  // 检查返回的迭代器
	print_info(v, "v (删除索引5后)");  // [0, 1, 2, 3, 4, 6, 7, 8, 9]
	
	// 测试删除第一个元素
	auto erase_it2 = v.erase(v.begin());
	assert(v.getSize() == 8);
	assert(v[0] == 1);
	assert(erase_it2 == v.begin());
	print_info(v, "v (删除第一个元素后)");  // [1, 2, 3, 4, 6, 7, 8, 9]
	
	// 测试删除最后一个元素
	auto erase_it3 = v.erase(v.end() - 1);
	assert(v.getSize() == 7);
	assert(v[v.getSize() - 1] == 8);
	assert(erase_it3 == v.end());  // 删除最后元素后，迭代器指向新的end
	print_info(v, "v (删除最后元素后)");  // [1, 2, 3, 4, 6, 7, 8]
	
	// 测试范围删除 - 删除中间几个元素
	auto erase_it4 = v.erase(v.begin() + 2, v.begin() + 5);  // 删除索引2到4的元素 [3, 4, 6]
	assert(v.getSize() == 4);
	assert(v[0] == 1 && v[1] == 2 && v[2] == 7 && v[3] == 8);
	assert(erase_it4 == v.begin() + 2);  // 检查返回的迭代器
	print_info(v, "v (删除范围后)");  // [1, 2, 7, 8]
	
	// 测试空范围删除
	auto old_size = v.getSize();
	auto empty_it = v.begin() + 1;
	auto erase_it5 = v.erase(empty_it, empty_it);  // 空范围，不应删除任何元素
	assert(v.getSize() == old_size);
	assert(erase_it5 == empty_it);
	print_info(v, "v (空范围删除后)");
	
	// 测试删除剩余所有元素
	auto erase_it6 = v.erase(v.begin(), v.end());
	assert(v.getSize() == 0);
	assert(erase_it6 == v.end());
	print_info(v, "v (删除全部元素后)");
	
	// 测试异常情况（使用迭代器版本）
	try {
		v.erase(v.begin());  // 对空vector删除
		assert(false);  // 不应该到达这里
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获空vector删除异常: " << e.what() << std::endl;
	}
	
	// 重新填充数据测试越界
	v.push_back(100);
	v.push_back(200);
	v.push_back(300);
	
	try {
		v.erase(v.end());  // 越界删除（end()位置）
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获越界删除异常: " << e.what() << std::endl;
	}
	
	try {
		v.erase(v.begin() + 1, v.end() + 1);  // 范围越界
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获范围越界异常: " << e.what() << std::endl;
	}
	
	try {
		v.erase(v.begin() + 2, v.begin() + 1);  // 无效范围 (first > last)
		assert(false);
	} catch (const std::out_of_range& e) {
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
	assert(vs.getSize() == 4);
	assert(vs[2] == "erase");
	assert(str_it1 == vs.begin() + 2);
	print_info(vs, "vs (删除'test'后)");
	
	// 范围删除
	auto str_it2 = vs.erase(vs.begin() + 1, vs.begin() + 3);  // 删除"world"和"erase"
	assert(vs.getSize() == 2);
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
	for(int i = 1; i <= 5; ++i) {
		v.push_back(i);  // [1, 2, 3, 4, 5]
	}
	print_info(v, "v (初始状态)");
	
	// 测试基础反向迭代
	std::cout << "反向遍历元素: ";
	for(auto it = v.rbegin(); it != v.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	// 测试 const 反向迭代器
	const vector<int>& cv = v;
	std::cout << "const反向遍历元素: ";
	for(auto it = cv.rbegin(); it != cv.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	// 测试反向迭代器的修改操作
	for(auto it = v.rbegin(); it != v.rend(); ++it) {
		*it *= 10;  // 将每个元素乘以10
	}
	std::cout << "修改后反向遍历: ";
	for(auto it = v.rbegin(); it != v.rend(); ++it) {
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
	assert(distance == static_cast<ptrdiff_t>(v.getSize()));
	
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
	for(auto it = vs.rbegin(); it != vs.rend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	// 使用反向迭代器修改字符串
	for(auto it = vs.rbegin(); it != vs.rend(); ++it) {
		*it = "modified_" + *it;
	}
	
	std::cout << "修改后反向遍历: ";
	for(auto it = vs.rbegin(); it != vs.rend(); ++it) {
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
	for(int i = 1; i <= 3; ++i) {
		v.push_back(i);  // [1, 2, 3]
	}
	
	// rbegin应该指向最后一个元素
	assert(*v.rbegin() == *std::prev(v.end()));
	// rend应该指向第一个元素之前的位置
	assert(v.rend().base() == v.begin());
	
	std::cout << "反向迭代器与正向迭代器关系测试通过!" << std::endl;
	
	// 使用基于范围的for循环（C++11）进行反向遍历的替代方案
	std::cout << "反向遍历 (手动): ";
	for(auto it = v.rbegin(); it != v.rend(); ++it) {
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
	for(int i = 10; i <= 50; i += 10) {
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
	try {
		v.at(5);  // 越界访问
		assert(false);  // 不应该到达这里
	} catch (const std::out_of_range& e) {
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
	assert(empty_v.getSize() == 0);
	
	// 测试空容器的 data() 方法
	int* ptr = empty_v.data();
	// data() 对空容器可能返回nullptr，这是允许的
	std::cout << "空容器data()指针: " << (ptr ? "非空" : "空") << std::endl;
	
	// 测试空容器的异常情况
	try {
		empty_v.at(0);
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获空容器at()异常: " << e.what() << std::endl;
	}
	
	try {
		empty_v.front();
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获空容器front()异常: " << e.what() << std::endl;
	}
	
	try {
		empty_v.back();
		assert(false);
	} catch (const std::out_of_range& e) {
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
	for(int i = 0; i < 5; ++i) {
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
	assert(*it3 == 999 && v[v.getSize()-1] == 999);
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
	auto current_size = v.getSize();
	auto insert_pos = v.begin() + 1;
	auto result_it = v.insert(insert_pos, 555);
	assert(result_it == v.begin() + 1);
	assert(*result_it == 555);
	assert(v.getSize() == current_size + 1);
	print_info(v, "v (验证insert返回值后)");
	
	// 测试 erase 返回值的正确性
	auto erase_pos = v.begin() + 1;
	auto result_erase_it = v.erase(erase_pos);
	assert(result_erase_it == v.begin() + 1);
	assert(v.getSize() == current_size);
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
	try {
		v.insert(v.end() + 1, 100);  // 超出范围的迭代器
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获insert越界异常: " << e.what() << std::endl;
	}
	
	try {
		v.insert(v.begin() - 1, 100);  // 超出范围的迭代器
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获insert越界异常: " << e.what() << std::endl;
	}
	
	try {
		v.erase(v.end());  // end()位置无法删除
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获erase越界异常: " << e.what() << std::endl;
	}
	
	try {
		v.erase(v.begin() - 1);  // 超出范围的迭代器
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获erase越界异常: " << e.what() << std::endl;
	}
	
	// 测试无效范围
	try {
		v.erase(v.begin() + 2, v.begin() + 1);  // first > last
		assert(false);
	} catch (const std::out_of_range& e) {
		std::cout << "成功捕获无效范围异常: " << e.what() << std::endl;
	}
	
	std::cout << "insert和erase异常安全性测试通过!" << std::endl;
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
	
	std::cout << "\n✅ 所有测试用例执行完毕!\n";
	return 0;
}
