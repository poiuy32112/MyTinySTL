#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>   // for std::move and std::forward
#include "iterator.h"

template <typename T>
class vector
{
public:
	// 标准STL类型定义
	typedef T                                   value_type;
	typedef T*                                  pointer;
	typedef const T*                            const_pointer;
	typedef T&                                  reference;
	typedef const T&                            const_reference;
	typedef size_t                              size_type;
	typedef ptrdiff_t                           difference_type;
	typedef T*                                  iterator;
	typedef const T*                            const_iterator;
	typedef reverse_iterator<iterator>          reverse_iterator_type;
	typedef reverse_iterator<const_iterator>    const_reverse_iterator;

private:
	iterator m_begin;        // 使用空间的头部
	iterator m_end;          // 使用空间的尾部
	iterator m_cap;          // 存储空间的尾部

public:
	// 构造函数和析构函数
	vector();
	~vector();
	vector(const vector& other);                    // 拷贝构造函数
	vector(vector&& other) noexcept;               // 移动构造函数

	// 赋值运算符
	vector& operator=(const vector& other);        // 拷贝赋值运算符
	vector& operator=(vector&& other) noexcept;    // 移动赋值运算符

	// 交换函数
	void swap(vector& other) noexcept;

	// 元素访问
	reference operator[](size_type index);
	const_reference operator[](size_type index) const;
	reference at(size_type index);
	const_reference at(size_type index) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;
	pointer data();
	const_pointer data() const;

	// 修改器
	void push_back(const T& value);                // 拷贝版本
	void push_back(T&& value);                     // 移动版本
	void pop_back();
	template<typename... Args>
	void emplace_back(Args&&... args);
	iterator insert(iterator pos, const T& value);  // 拷贝版本
	iterator insert(iterator pos, T&& value);       // 移动版本
	iterator erase(iterator pos);                   // 删除单个元素
	iterator erase(iterator first, iterator last);  // 删除范围元素
	void clear();

	// 容量
	size_type getSize() const;
	size_type getCapacity() const;
	void reserve(size_type newCapacity);

	// 迭代器
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	// 反向迭代器
	reverse_iterator_type rbegin();
	reverse_iterator_type rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

	// 辅助函数
	void printElements() const;
};

// 非成员swap函数
template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept;

// ==================== 成员函数实现 ====================

// 默认构造函数
template<typename T>
vector<T>::vector() : m_begin(nullptr), m_end(nullptr), m_cap(nullptr) {}

// 析构函数
template<typename T>
vector<T>::~vector()
{
	clear();  // 显式调用析构函数
	delete[] m_begin;
}

// 拷贝构造函数 - 异常安全版本
template<typename T>
vector<T>::vector(const vector& other) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr)
{
	size_type other_size = other.m_end - other.m_begin;
	if (other_size > 0)
	{
		size_type other_capacity = other.m_cap - other.m_begin;
		// 先分配内存
		m_begin = new T[other_capacity];
		m_end = m_begin;
		m_cap = m_begin + other_capacity;

		// 逐个拷贝元素，若失败则回滚并释放资源
		try
		{
			for (iterator src_it = other.m_begin; src_it != other.m_end; ++src_it, ++m_end)
			{
				new (m_end) T(*src_it);  // 使用拷贝构造
			}
		}
		catch (...)
		{
			// 异常安全：销毁已构造的元素
			clear();
			delete[] m_begin;
			m_begin = nullptr;
			m_end = nullptr;
			m_cap = nullptr;
			throw;  // 重新抛出异常
		}
	}
}

// 移动构造函数 (C++11) - noexcept 保证
template<typename T>
vector<T>::vector(vector&& other) noexcept
	: m_begin(other.m_begin)
	, m_end(other.m_end)
	, m_cap(other.m_cap)
{
	// 将源对象置为有效但未指定的状态
	other.m_begin = nullptr;
	other.m_end = nullptr;
	other.m_cap = nullptr;
}

// 拷贝赋值运算符 - 使用 copy-and-swap 惯用法
template<typename T>
vector<T>& vector<T>::operator=(const vector& other)
{
	if (this != &other)  // 自我赋值检查
	{
		vector temp(other);  // 创建临时对象，构造中的异常不会影响当前对象
		swap(temp);          // 交换数据，强异常安全保证
	}
	return *this;
	// temp 离开作用域时会自动释放原有的资源
}

// 移动赋值运算符 (C++11) - noexcept 保证
template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept
{
	if (this != &other)  // 自移动检查
	{
		// 清理当前对象的资源
		clear();
		delete[] m_begin;

		// 移动资源
		m_begin = other.m_begin;
		m_end = other.m_end;
		m_cap = other.m_cap;

		// 将源对象置为有效但未指定的状态
		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_cap = nullptr;
	}
	return *this;
}

// 交换函数 - noexcept 保证
template<typename T>
void vector<T>::swap(vector& other) noexcept
{
	std::swap(m_begin, other.m_begin);
	std::swap(m_end, other.m_end);
	std::swap(m_cap, other.m_cap);
}

// 访问容器中的元素
template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type index)
{
	// 检查索引是否越界
	if (index >= static_cast<size_type>(m_end - m_begin))
	{
		throw std::out_of_range("Index out of range");
	}
	return m_begin[index];
}

// const版本的访问容器中的元素
template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type index) const
{
	// 检查索引是否越界
	if (index >= static_cast<size_type>(m_end - m_begin))
	{
		throw std::out_of_range("Index out of range");
	}
	return m_begin[index];
}

// 带边界检查的元素访问
template<typename T>
typename vector<T>::reference vector<T>::at(size_type index)
{
	if (index >= static_cast<size_type>(m_end - m_begin))
	{
		throw std::out_of_range("vector::at: index out of range");
	}
	return m_begin[index];
}

// const版本的带边界检查的元素访问
template<typename T>
typename vector<T>::const_reference vector<T>::at(size_type index) const
{
	if (index >= static_cast<size_type>(m_end - m_begin))
	{
		throw std::out_of_range("vector::at: index out of range");
	}
	return m_begin[index];
}

// 访问第一个元素
template<typename T>
typename vector<T>::reference vector<T>::front()
{
	if (m_begin == m_end)
	{
		throw std::out_of_range("vector::front: container is empty");
	}
	return *m_begin;
}

// const版本的访问第一个元素
template<typename T>
typename vector<T>::const_reference vector<T>::front() const
{
	if (m_begin == m_end)
	{
		throw std::out_of_range("vector::front: container is empty");
	}
	return *m_begin;
}

// 访问最后一个元素
template<typename T>
typename vector<T>::reference vector<T>::back()
{
	if (m_begin == m_end)
	{
		throw std::out_of_range("vector::back: container is empty");
	}
	return *(m_end - 1);
}

// const版本的访问最后一个元素
template<typename T>
typename vector<T>::const_reference vector<T>::back() const
{
	if (m_begin == m_end)
	{
		throw std::out_of_range("vector::back: container is empty");
	}
	return *(m_end - 1);
}

// 返回指向底层数组的指针
template<typename T>
typename vector<T>::pointer vector<T>::data()
{
	return m_begin;
}

// const版本的返回指向底层数组的指针
template<typename T>
typename vector<T>::const_pointer vector<T>::data() const
{
	return m_begin;
}

// 在容器末尾添加元素 - 拷贝版本
template<typename T>
void vector<T>::push_back(const T& value)
{
	if (m_end == m_cap)
	{
		// 如果容量不足，则扩展容量
		size_type current_capacity = m_cap - m_begin;
		reserve(current_capacity == 0 ? 1 : 2 * current_capacity);
	}

	// 使用placement new在指定位置构造元素
	new (m_end) T(value);
	++m_end;
}

// 在容器末尾添加元素 - 移动版本 (C++11)
template<typename T>
void vector<T>::push_back(T&& value)
{
	if (m_end == m_cap)
	{
		// 如果容量不足，则扩展容量
		size_type current_capacity = m_cap - m_begin;
		reserve(current_capacity == 0 ? 1 : 2 * current_capacity);
	}

	// 使用移动构造在指定位置构造元素
	new (m_end) T(std::move(value));
	++m_end;
}

// 删除容器末尾的元素 - 显式析构
template<typename T>
void vector<T>::pop_back()
{
	if (m_begin != m_end)
	{
		--m_end;
		m_end->~T();  // 显式调用析构函数
	}
}

// 在容器末尾直接构造元素，使用完美转发
template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&&... args)
{
	if (m_end == m_cap)
	{
		// 如果容量不足，扩展容量
		size_type current_capacity = m_cap - m_begin;
		reserve(current_capacity == 0 ? 1 : 2 * current_capacity);
	}
	// 使用placement new在指定位置直接构造元素
	new (m_end) T(std::forward<Args>(args)...);
	++m_end;
}

// 在指定位置插入元素 - 拷贝版本
template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const T& value)
{
	// 检查迭代器有效性
	if (pos < m_begin || pos > m_end)
	{
		throw std::out_of_range("Iterator out of range");
	}

	size_type index = pos - m_begin;  // 将迭代器转换为索引

	if (m_end == m_cap)
	{
		// 需要扩容时，使用异常安全的 reserve
		size_type current_capacity = m_cap - m_begin;
		reserve(current_capacity == 0 ? 1 : current_capacity * 2);
	}

	// 从后向前移动元素，为新元素腾出空间
	for (iterator it = m_end; it > m_begin + index; --it)
	{
		new (it) T(std::move(*(it - 1)));
		(it - 1)->~T();
	}

	// 在指定位置构造新元素
	new (m_begin + index) T(value);
	++m_end;

	// 返回指向插入元素的迭代器
	return m_begin + index;
}

// 在指定位置插入元素 - 移动版本 (C++11)
template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, T&& value)
{
	// 检查迭代器有效性
	if (pos < m_begin || pos > m_end)
	{
		throw std::out_of_range("Iterator out of range");
	}

	size_type index = pos - m_begin;  // 将迭代器转换为索引

	if (m_end == m_cap)
	{
		// 需要扩容时，使用异常安全的 reserve
		size_type current_capacity = m_cap - m_begin;
		reserve(current_capacity == 0 ? 1 : current_capacity * 2);
	}

	// 从后向前移动元素，为新元素腾出空间
	for (iterator it = m_end; it > m_begin + index; --it)
	{
		new (it) T(std::move(*(it - 1)));
		(it - 1)->~T();
	}

	// 在指定位置移动构造新元素
	new (m_begin + index) T(std::move(value));
	++m_end;

	// 返回指向插入元素的迭代器
	return m_begin + index;
}

// 删除指定位置的单个元素
template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos)
{
	// 检查迭代器有效性
	if (pos < m_begin || pos >= m_end)
	{
		throw std::out_of_range("Iterator out of range");
	}

	// 销毁要删除的元素
	pos->~T();

	// 将后面的元素向前移动
	for (iterator it = pos; it < m_end - 1; ++it)
	{
		new (it) T(std::move(*(it + 1)));
		(it + 1)->~T();
	}

	--m_end;

	// 返回指向删除位置的迭代器
	return pos;
}

// 删除指定范围的元素 [first, last)
template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator first, iterator last)
{
	// 检查迭代器有效性
	if (first < m_begin || last > m_end || first > last)
	{
		throw std::out_of_range("Invalid iterator range");
	}

	if (first == last)
	{
		return first;  // 空范围，直接返回
	}

	size_type erase_count = last - first;

	// 销毁要删除范围内的元素
	for (iterator it = first; it != last; ++it)
	{
		it->~T();
	}

	// 将后面的元素向前移动
	for (iterator it = first; last != m_end; ++it, ++last)
	{
		new (it) T(std::move(*last));
		last->~T();
	}

	m_end -= erase_count;

	// 返回指向删除开始位置的迭代器
	return first;
}

// 清空容器 - 显式调用析构函数
template<typename T>
void vector<T>::clear()
{
	for (iterator it = m_begin; it != m_end; ++it)
	{
		it->~T();  // 显式调用每个元素的析构函数
	}
	m_end = m_begin;
}

// 获取容器中元素的个数
template<typename T>
typename vector<T>::size_type vector<T>::getSize() const
{
	return m_end - m_begin;
}

// 获取容器的容量
template<typename T>
typename vector<T>::size_type vector<T>::getCapacity() const
{
	return m_cap - m_begin;
}

// 扩展容器容量 - 异常安全版本
template<typename T>
void vector<T>::reserve(size_type newCapacity)
{
	size_type current_capacity = m_cap - m_begin;
	if (newCapacity > current_capacity)
	{
		size_type current_size = m_end - m_begin;
		
		// 分配新内存
		T* newElements = new T[newCapacity];

		try
		{
			// 移动/拷贝旧元素到新内存
			size_type i = 0;
			for (iterator it = m_begin; it != m_end; ++it, ++i)
			{
				new (&newElements[i]) T(std::move(*it));
			}
		}
		catch (...)
		{
			// 如果移动失败，释放新分配的内存
			delete[] newElements;
			throw;  // 重新抛出异常，保持原有对象状态不变
		}

		// 成功后释放旧内存
		// 手动销毁旧元素
		for (iterator it = m_begin; it != m_end; ++it)
		{
			it->~T();
		}
		delete[] m_begin;

		// 更新指针
		m_begin = newElements;
		m_end = m_begin + current_size;
		m_cap = m_begin + newCapacity;
	}
}

// 使用的迭代器指向容器的开始位置
template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
	return m_begin;
}

// 使用的迭代器指向容器的结束位置
template<typename T>
typename vector<T>::iterator vector<T>::end()
{
	return m_end;
}

// 使用的迭代器指向容器的开始位置（const版本）
template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const
{
	return m_begin;
}

// 使用的迭代器指向容器的结束位置（const版本）
template<typename T>
typename vector<T>::const_iterator vector<T>::end() const
{
	return m_end;
}

// 反向迭代器指向容器的反向开始位置
template<typename T>
typename vector<T>::reverse_iterator_type vector<T>::rbegin()
{
	return reverse_iterator_type(m_end);
}

// 反向迭代器指向容器的反向结束位置
template<typename T>
typename vector<T>::reverse_iterator_type vector<T>::rend()
{
	return reverse_iterator_type(m_begin);
}

// 反向迭代器指向容器的反向开始位置（const版本）
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const
{
	return const_reverse_iterator(m_end);
}

// 反向迭代器指向容器的反向结束位置（const版本）
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const
{
	return const_reverse_iterator(m_begin);
}

// 打印容器中的元素
template<typename T>
void vector<T>::printElements() const
{
	for (iterator it = m_begin; it != m_end; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

// 非成员swap函数，支持 ADL (Argument Dependent Lookup)
template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept
{
	lhs.swap(rhs);
}
