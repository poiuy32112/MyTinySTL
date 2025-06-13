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
	iterator m_elements;     // 指向动态数组的指针
	size_type m_capacity;    // 容器的容量
	size_type m_size;        // 容器中元素的个数

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

	// 修改器
	void push_back(const T& value);                // 拷贝版本
	void push_back(T&& value);                     // 移动版本
	void pop_back();
	template<typename... Args>
	void emplace_back(Args&&... args);
	void insert(size_type index, const T& value);  // 拷贝版本
	void insert(size_type index, T&& value);       // 移动版本
	iterator erase(size_type index);               // 删除单个元素
	iterator erase(size_type first, size_type last); // 删除范围元素
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
vector<T>::vector() : m_elements(nullptr), m_capacity(0), m_size(0) {}

// 析构函数
template<typename T>
vector<T>::~vector()
{
	clear();  // 显式调用析构函数
	delete[] m_elements;
}

// 拷贝构造函数 - 异常安全版本
template<typename T>
vector<T>::vector(const vector& other) : m_elements(nullptr), m_capacity(0), m_size(0)
{
	if (other.m_size > 0)
	{
		// 先分配内存
		m_elements = new T[other.m_capacity];
		m_capacity = other.m_capacity;

		// 逐个拷贝元素，若失败则回滚并释放资源
		try
		{
			for (size_type i = 0; i < other.m_size; ++i)
			{
				new (&m_elements[i]) T(other.m_elements[i]);  // 使用拷贝构造
				++m_size;  // 只有构造成功才增加计数
			}
		}
		catch (...)
		{
			// 异常安全：销毁已构造的元素
			clear();
			delete[] m_elements;
			m_elements = nullptr;
			m_capacity = 0;
			m_size = 0;
			throw;  // 重新抛出异常
		}
	}
}

// 移动构造函数 (C++11) - noexcept 保证
template<typename T>
vector<T>::vector(vector&& other) noexcept
	: m_elements(other.m_elements)
	, m_capacity(other.m_capacity)
	, m_size(other.m_size)
{
	// 将源对象置为有效但未指定的状态
	other.m_elements = nullptr;
	other.m_capacity = 0;
	other.m_size = 0;
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
		delete[] m_elements;

		// 移动资源
		m_elements = other.m_elements;
		m_capacity = other.m_capacity;
		m_size = other.m_size;

		// 将源对象置为有效但未指定的状态
		other.m_elements = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;
	}
	return *this;
}

// 交换函数 - noexcept 保证
template<typename T>
void vector<T>::swap(vector& other) noexcept
{
	std::swap(m_elements, other.m_elements);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_size, other.m_size);
}

// 访问容器中的元素
template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type index)
{
	// 检查索引是否越界
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_elements[index];
}

// const版本的访问容器中的元素
template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type index) const
{
	// 检查索引是否越界
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_elements[index];
}

// 在容器末尾添加元素 - 拷贝版本
template<typename T>
void vector<T>::push_back(const T& value)
{
	if (m_size == m_capacity)
	{
		// 如果容量不足，则扩展容量
		reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
	}

	// 使用placement new在指定位置构造元素
	new (&m_elements[m_size]) T(value);
	++m_size;
}

// 在容器末尾添加元素 - 移动版本 (C++11)
template<typename T>
void vector<T>::push_back(T&& value)
{
	if (m_size == m_capacity)
	{
		// 如果容量不足，则扩展容量
		reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
	}

	// 使用移动构造在指定位置构造元素
	new (&m_elements[m_size]) T(std::move(value));
	++m_size;
}

// 删除容器末尾的元素 - 显式析构
template<typename T>
void vector<T>::pop_back()
{
	if (m_size > 0)
	{
		m_elements[m_size - 1].~T();  // 显式调用析构函数
		--m_size;
	}
}

// 在容器末尾直接构造元素，使用完美转发
template<typename T>
template<typename... Args>
void vector<T>::emplace_back(Args&&... args)
{
	if (m_size == m_capacity)
	{
		// 如果容量不足，扩展容量
		reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
	}
	// 使用placement new在指定位置直接构造元素
	new (&m_elements[m_size]) T(std::forward<Args>(args)...);
	++m_size;
}

// 在指定位置插入元素 - 拷贝版本
template<typename T>
void vector<T>::insert(size_type index, const T& value)
{
	if (index > m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	if (m_size == m_capacity)
	{
		// 需要扩容时，使用异常安全的 reserve
		reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}

	// 从后向前移动元素，为新元素腾出空间
	for (size_type i = m_size; i > index; --i)
	{
		new (&m_elements[i]) T(std::move(m_elements[i - 1]));
		m_elements[i - 1].~T();
	}

	// 在指定位置构造新元素
	new (&m_elements[index]) T(value);
	++m_size;
}

// 在指定位置插入元素 - 移动版本 (C++11)
template<typename T>
void vector<T>::insert(size_type index, T&& value)
{
	if (index > m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	if (m_size == m_capacity)
	{
		// 需要扩容时，使用异常安全的 reserve
		reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}

	// 从后向前移动元素，为新元素腾出空间
	for (size_type i = m_size; i > index; --i)
	{
		new (&m_elements[i]) T(std::move(m_elements[i - 1]));
		m_elements[i - 1].~T();
	}

	// 在指定位置移动构造新元素
	new (&m_elements[index]) T(std::move(value));
	++m_size;
}

// 删除指定位置的单个元素
template<typename T>
typename vector<T>::iterator vector<T>::erase(size_type index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	// 销毁要删除的元素
	m_elements[index].~T();

	// 将后面的元素向前移动
	for (size_type i = index; i < m_size - 1; ++i)
	{
		new (&m_elements[i]) T(std::move(m_elements[i + 1]));
		m_elements[i + 1].~T();
	}

	--m_size;

	// 返回指向删除位置的迭代器
	return m_elements + index;
}

// 删除指定范围的元素 [first, last)
template<typename T>
typename vector<T>::iterator vector<T>::erase(size_type first, size_type last)
{
	if (first > m_size || last > m_size || first > last)
	{
		throw std::out_of_range("Invalid range");
	}

	if (first == last)
	{
		return m_elements + first;  // 空范围，直接返回
	}

	size_type erase_count = last - first;

	// 销毁要删除范围内的元素
	for (size_type i = first; i < last; ++i)
	{
		m_elements[i].~T();
	}

	// 将后面的元素向前移动
	for (size_type i = first; i < m_size - erase_count; ++i)
	{
		new (&m_elements[i]) T(std::move(m_elements[i + erase_count]));
		m_elements[i + erase_count].~T();
	}

	m_size -= erase_count;

	// 返回指向删除开始位置的迭代器
	return m_elements + first;
}

// 清空容器 - 显式调用析构函数
template<typename T>
void vector<T>::clear()
{
	for (size_type i = 0; i < m_size; ++i)
	{
		m_elements[i].~T();  // 显式调用每个元素的析构函数
	}
	m_size = 0;
}

// 获取容器中元素的个数
template<typename T>
typename vector<T>::size_type vector<T>::getSize() const
{
	return m_size;
}

// 获取容器的容量
template<typename T>
typename vector<T>::size_type vector<T>::getCapacity() const
{
	return m_capacity;
}

// 扩展容器容量 - 异常安全版本
template<typename T>
void vector<T>::reserve(size_type newCapacity)
{
	if (newCapacity > m_capacity)
	{
		// 分配新内存
		T* newElements = new T[newCapacity];

		try
		{
			// 移动/拷贝旧元素到新内存
			for (size_type i = 0; i < m_size; ++i)
			{
				new (&newElements[i]) T(std::move(m_elements[i]));
			}
		}
		catch (...)
		{
			// 如果移动失败，释放新分配的内存
			delete[] newElements;
			throw;  // 重新抛出异常，保持原有对象状态不变
		}

		// 成功后释放旧内存
		// 手动销毁旧元素，但不重置 m_size
		for (size_type i = 0; i < m_size; ++i)
		{
			m_elements[i].~T();
		}
		delete[] m_elements;

		// 更新指针和容量
		m_elements = newElements;
		m_capacity = newCapacity;
	}
}

// 使用的迭代器指向容器的开始位置
template<typename T>
typename vector<T>::iterator vector<T>::begin()
{
	return m_elements;
}

// 使用的迭代器指向容器的结束位置
template<typename T>
typename vector<T>::iterator vector<T>::end()
{
	return m_elements + m_size;
}

// 使用的迭代器指向容器的开始位置（const版本）
template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const
{
	return m_elements;
}

// 使用的迭代器指向容器的结束位置（const版本）
template<typename T>
typename vector<T>::const_iterator vector<T>::end() const
{
	return m_elements + m_size;
}

// 反向迭代器指向容器的反向开始位置
template<typename T>
typename vector<T>::reverse_iterator_type vector<T>::rbegin()
{
	return reverse_iterator_type(end());
}

// 反向迭代器指向容器的反向结束位置
template<typename T>
typename vector<T>::reverse_iterator_type vector<T>::rend()
{
	return reverse_iterator_type(begin());
}

// 反向迭代器指向容器的反向开始位置（const版本）
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const
{
	return const_reverse_iterator(end());
}

// 反向迭代器指向容器的反向结束位置（const版本）
template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const
{
	return const_reverse_iterator(begin());
}

// 打印容器中的元素
template<typename T>
void vector<T>::printElements() const
{
	for (size_type i = 0; i < m_size; ++i)
	{
		std::cout << m_elements[i] << " ";
	}
	std::cout << std::endl;
}

// 非成员swap函数，支持 ADL (Argument Dependent Lookup)
template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept
{
	lhs.swap(rhs);
}
