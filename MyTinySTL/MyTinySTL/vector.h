#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class vector
{
public:
	// 标准STL类型定义
	typedef T                               value_type;
	typedef T*								pointer;
	typedef const T*						const_pointer;
	typedef T&								reference;
	typedef const T&						const_reference;
	typedef size_t                          size_type;
	typedef ptrdiff_t                       difference_type;
	typedef T*								iterator;
	typedef const T*						const_iterator;

private:
	iterator m_elements;     // 指向动态数组的指针
	size_type m_capacity; // 数组的容量
	size_type m_size;     // 数组中元素的个数

public:
	// 构造函数
	vector() : m_elements(nullptr), m_capacity(0), m_size(0) {}

	// 析构函数
	~vector()
	{
		delete[] m_elements;
	}

	// 拷贝构造函数
	vector(const vector& other) : m_capacity(other.m_capacity), m_size(other.m_size)
	{
		m_elements = new T[m_capacity];
		std::copy(other.m_elements, other.m_elements + m_size, m_elements);
	}

	// 拷贝赋值操作符
	vector& operator=(const vector& other)
	{
		if (this != &other)
		{
			delete[] m_elements;
			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_elements = new T[m_capacity];
			std::copy(other.m_elements, other.m_elements + m_size, m_elements);
		}
		return *this;
	}

	// 添加元素到数组末尾
	void push_back(const T& value)
	{
		if (m_size == m_capacity)
		{
			// 如果数组已满，扩展容量
			reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
		}
		m_elements[m_size++] = value;
	}

	// 获取数组中元素的个数
	size_t getSize() const
	{
		return m_size;
	}

	// 获取数组的容量
	size_t getCapacity() const
	{
		return m_capacity;
	}

	// 访问数组中的元素
	T& operator[](size_t index)
	{
		// 检查索引是否越界
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// const版本的访问数组中的元素
	const T& operator[](size_t index) const
	{
		// 检查索引是否越界
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// 在指定位置插入元素
	void insert(size_t index, const T& value)
	{
		if (index > m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		if (m_size == m_capacity)
		{
			reserve(m_capacity == 0 ? 1 : m_capacity * 2);
		}
		for (size_t i = m_size; i > index; --i)
		{
			m_elements[i] = m_elements[i - 1];
		}
		m_elements[index] = value;
		++m_size;
	}

	// 删除数组末尾的元素
	void pop_back()
	{
		if (m_size > 0)
		{
			--m_size;
		}
	}

	// 在容器末尾直接构造元素（使用完美转发）
	template<typename... Args>
	void emplace_back(Args&&... args)
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

	// 清空数组
	void clear()
	{
		m_size = 0;
	}

	// 使用迭代器遍历数组的开始位置
	T* begin()
	{
		return m_elements;
	}

	// 使用迭代器遍历数组的结束位置
	T* end()
	{
		return m_elements + m_size;
	}

	// 使用迭代器遍历数组的开始位置（const版本）
	const T* begin() const
	{
		return m_elements;
	}

	// 使用迭代器遍历数组的结束位置（const版本）
	const T* end() const
	{
		return m_elements + m_size;
	}

	// 打印数组中的元素
	void printElements() const
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			std::cout << m_elements[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	// 扩展数组容量
	void reserve(size_t newCapacity)
	{
		if (newCapacity > m_capacity)
		{
			T* newElements = new T[newCapacity];
			std::copy(m_elements, m_elements + m_size, newElements);
			delete[] m_elements;
			m_elements = newElements;
			m_capacity = newCapacity;
		}
	}
};