#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>   // for std::move and std::forward

template <typename T>
class vector
{
public:
	// 标准STL类型定义
	typedef T                               value_type;
	typedef T*                              pointer;
	typedef const T*                        const_pointer;
	typedef T&                              reference;
	typedef const T&                        const_reference;
	typedef size_t                          size_type;
	typedef ptrdiff_t                       difference_type;
	typedef T*                              iterator;
	typedef const T*                        const_iterator;

private:
	iterator m_elements;     // 指向动态数组的指针
	size_type m_capacity;    // 容器的容量
	size_type m_size;        // 容器中元素的个数

public:
	// 构造函数
	vector() : m_elements(nullptr), m_capacity(0), m_size(0) {}

	// 析构函数
	~vector()
	{
		clear();  // 显式调用析构函数
		delete[] m_elements;
	}

	// 拷贝构造函数 - 异常安全版本
	vector(const vector& other) : m_elements(nullptr), m_capacity(0), m_size(0)
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
	vector(vector&& other) noexcept
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
	vector& operator=(const vector& other)
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
	vector& operator=(vector&& other) noexcept
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
	void swap(vector& other) noexcept
	{
		std::swap(m_elements, other.m_elements);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_size, other.m_size);
	}

	// 在容器末尾添加元素 - 拷贝版本
	void push_back(const T& value)
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
	void push_back(T&& value)
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

	// 获取容器中元素的个数
	size_t getSize() const
	{
		return m_size;
	}

	// 获取容器的容量
	size_t getCapacity() const
	{
		return m_capacity;
	}

	// 访问容器中的元素
	T& operator[](size_t index)
	{
		// 检查索引是否越界
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// const版本的访问容器中的元素
	const T& operator[](size_t index) const
	{
		// 检查索引是否越界
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// 在指定位置插入元素 - 拷贝版本
	void insert(size_t index, const T& value)
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
		for (size_t i = m_size; i > index; --i)
		{
			new (&m_elements[i]) T(std::move(m_elements[i - 1]));
			m_elements[i - 1].~T();
		}

		// 在指定位置构造新元素
		new (&m_elements[index]) T(value);
		++m_size;
	}

	// 在指定位置插入元素 - 移动版本 (C++11)
	void insert(size_t index, T&& value)
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
		for (size_t i = m_size; i > index; --i)
		{
			new (&m_elements[i]) T(std::move(m_elements[i - 1]));
			m_elements[i - 1].~T();
		}

		// 在指定位置移动构造新元素
		new (&m_elements[index]) T(std::move(value));
		++m_size;
	}

	// 删除容器末尾的元素 - 显式析构
	void pop_back()
	{
		if (m_size > 0)
		{
			m_elements[m_size - 1].~T();  // 显式调用析构函数
			--m_size;
		}
	}

	// 在容器末尾直接构造元素，使用完美转发
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

	// 清空容器 - 显式调用析构函数
	void clear()
	{
		for (size_type i = 0; i < m_size; ++i)
		{
			m_elements[i].~T();  // 显式调用每个元素的析构函数
		}
		m_size = 0;
	}

	// 使用的迭代器指向容器的开始位置
	T* begin()
	{
		return m_elements;
	}

	// 使用的迭代器指向容器的结束位置
	T* end()
	{
		return m_elements + m_size;
	}

	// 使用的迭代器指向容器的开始位置（const版本）
	const T* begin() const
	{
		return m_elements;
	}

	// 使用的迭代器指向容器的结束位置（const版本）
	const T* end() const
	{
		return m_elements + m_size;
	}

	// 打印容器中的元素
	void printElements() const
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			std::cout << m_elements[i] << " ";
		}
		std::cout << std::endl;
	}

	// 扩展容器容量 - 异常安全版本
	void reserve(size_t newCapacity)
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
};

// 非成员swap函数，支持 ADL (Argument Dependent Lookup)
template<typename T>
void swap(vector<T>& lhs, vector<T>& rhs) noexcept
{
	lhs.swap(rhs);
}
