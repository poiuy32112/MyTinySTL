#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class vector
{
public:
	// ��׼STL���Ͷ���
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
	iterator m_elements;     // ָ��̬�����ָ��
	size_type m_capacity; // ���������
	size_type m_size;     // ������Ԫ�صĸ���

public:
	// ���캯��
	vector() : m_elements(nullptr), m_capacity(0), m_size(0) {}

	// ��������
	~vector()
	{
		delete[] m_elements;
	}

	// �������캯��
	vector(const vector& other) : m_capacity(other.m_capacity), m_size(other.m_size)
	{
		m_elements = new T[m_capacity];
		std::copy(other.m_elements, other.m_elements + m_size, m_elements);
	}

	// ������ֵ������
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

	// ����Ԫ�ص�����ĩβ
	void push_back(const T& value)
	{
		if (m_size == m_capacity)
		{
			// ���������������չ����
			reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
		}
		m_elements[m_size++] = value;
	}

	// ��ȡ������Ԫ�صĸ���
	size_t getSize() const
	{
		return m_size;
	}

	// ��ȡ���������
	size_t getCapacity() const
	{
		return m_capacity;
	}

	// ���������е�Ԫ��
	T& operator[](size_t index)
	{
		// ��������Ƿ�Խ��
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// const�汾�ķ��������е�Ԫ��
	const T& operator[](size_t index) const
	{
		// ��������Ƿ�Խ��
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_elements[index];
	}

	// ��ָ��λ�ò���Ԫ��
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

	// ɾ������ĩβ��Ԫ��
	void pop_back()
	{
		if (m_size > 0)
		{
			--m_size;
		}
	}

	// ������ĩβֱ�ӹ���Ԫ�أ�ʹ������ת����
	template<typename... Args>
	void emplace_back(Args&&... args)
	{
		if (m_size == m_capacity)
		{
			// ����������㣬��չ����
			reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
		}
		// ʹ��placement new��ָ��λ��ֱ�ӹ���Ԫ��
		new (&m_elements[m_size]) T(std::forward<Args>(args)...);
		++m_size;
	}

	// �������
	void clear()
	{
		m_size = 0;
	}

	// ʹ�õ�������������Ŀ�ʼλ��
	T* begin()
	{
		return m_elements;
	}

	// ʹ�õ�������������Ľ���λ��
	T* end()
	{
		return m_elements + m_size;
	}

	// ʹ�õ�������������Ŀ�ʼλ�ã�const�汾��
	const T* begin() const
	{
		return m_elements;
	}

	// ʹ�õ�������������Ľ���λ�ã�const�汾��
	const T* end() const
	{
		return m_elements + m_size;
	}

	// ��ӡ�����е�Ԫ��
	void printElements() const
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			std::cout << m_elements[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	// ��չ��������
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