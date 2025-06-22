#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>   // for std::move and std::forward
#include <initializer_list>
#include <memory>    // for std::allocator
#include "iterator.h"

template <typename T, typename Allocator = std::allocator<T>>
class vector
{
public:
    // 标准STL类型定义
    typedef T                                   value_type;
    typedef Allocator                           allocator_type;
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
    allocator_type m_allocator;  // 分配器

public:
    // 构造函数和析构函数
    vector();
    explicit vector(const allocator_type& alloc);              // 分配器构造
    explicit vector(size_type count, const allocator_type& alloc = allocator_type());  // 指定大小
    vector(size_type count, const T& value, const allocator_type& alloc = allocator_type());  // 指定大小和值
    template<class InputIt>
    vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type());  // 范围构造
    vector(std::initializer_list<T> init, const allocator_type& alloc = allocator_type());  // 初始化列表
    ~vector();
    vector(const vector& other);                    // 拷贝构造函数
    vector(const vector& other, const allocator_type& alloc);  // 带分配器的拷贝构造
    vector(vector&& other) noexcept;               // 移动构造函数
    vector(vector&& other, const allocator_type& alloc);       // 带分配器的移动构造

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
    size_type size() const;
    size_type capacity() const;
    void reserve(size_type newCapacity);
    void shrink_to_fit();
    void resize(size_type count);
    void resize(size_type count, const T& value);

    // 迭代器
    iterator begin() { return m_begin; };
    iterator end() { return m_end; }
    const_iterator begin() const { return m_begin; }
    const_iterator end() const { return m_end; }

    // 反向迭代器
    reverse_iterator_type rbegin() { return reverse_iterator_type(m_end); }
    reverse_iterator_type rend() { return reverse_iterator_type(m_begin); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(m_end); }
    const_reverse_iterator rend() const { return const_reverse_iterator(m_begin); }

    // const迭代器（C++11）
    const_iterator cbegin() const { return m_begin; }
    const_iterator cend() const { return m_end; }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(m_end); }
    const_reverse_iterator crend() const { return const_reverse_iterator(m_begin); }

    // 分配器访问
    allocator_type get_allocator() const { return m_allocator; }

    // 辅助函数
    void printElements() const;
};

// 比较操作符重载
template<typename T, typename Allocator>
bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

template<typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

// 非成员swap函数
template<typename T, typename Allocator>
void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) noexcept;

// ==================== 成员函数实现 ====================

// 默认构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector() : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator() {}

// 分配器构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc) {}

// 指定大小的构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count, const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    if (count > 0)
    {
        m_begin = m_allocator.allocate(count);
        m_end = m_begin;
        m_cap = m_begin + count;

        try
        {
            for (size_type i = 0; i < count; ++i)
            {
                new (m_end) T();  // 默认构造
                ++m_end;
            }
        }
        catch (...)
        {
            clear();
            m_allocator.deallocate(m_begin, count);
            m_begin = nullptr;
            m_end = nullptr;
            m_cap = nullptr;
            throw;
        }
    }
}

// 指定大小和值的构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count, const T& value, const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    if (count > 0)
    {
        m_begin = m_allocator.allocate(count);
        m_end = m_begin;
        m_cap = m_begin + count;

        try
        {
            for (size_type i = 0; i < count; ++i)
            {
                new (m_end) T(value);  // 拷贝构造
                ++m_end;
            }
        }
        catch (...)
        {
            clear();
            m_allocator.deallocate(m_begin, count);
            m_begin = nullptr;
            m_end = nullptr;
            m_cap = nullptr;
            throw;
        }
    }
}

// 范围构造函数
template<typename T, typename Allocator>
template<class InputIt>
vector<T, Allocator>::vector(InputIt first, InputIt last, const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    if (first != last)
    {
        // 计算距离（对于输入迭代器可能需要遍历）
        size_type count = 0;
        for (InputIt it = first; it != last; ++it)
        {
            ++count;
        }

        if (count > 0)
        {
            m_begin = m_allocator.allocate(count);
            m_end = m_begin;
            m_cap = m_begin + count;

            try
            {
                for (InputIt it = first; it != last; ++it)
                {
                    new (m_end) T(*it);  // 拷贝构造
                    ++m_end;
                }
            }
            catch (...)
            {
                clear();
                m_allocator.deallocate(m_begin, count);
                m_begin = nullptr;
                m_end = nullptr;
                m_cap = nullptr;
                throw;
            }
        }
    }
}

// 初始化列表构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init, const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    size_type count = init.size();
    if (count > 0)
    {
        m_begin = m_allocator.allocate(count);
        m_end = m_begin;
        m_cap = m_begin + count;

        try
        {
            for (const auto& value : init)
            {
                new (m_end) T(value);  // 拷贝构造
                ++m_end;
            }
        }
        catch (...)
        {
            clear();
            m_allocator.deallocate(m_begin, count);
            m_begin = nullptr;
            m_end = nullptr;
            m_cap = nullptr;
            throw;
        }
    }
}

// 析构函数
template<typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    clear();  // 显式调用析构函数
    if (m_begin)
    {
        m_allocator.deallocate(m_begin, m_cap - m_begin);
    }
}

// 拷贝构造函数 - 异常安全版本
template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(other.m_allocator)
{
    size_type other_size = other.m_end - other.m_begin;
    if (other_size > 0)
    {
        size_type other_capacity = other.m_cap - other.m_begin;
        // 先分配内存
        m_begin = m_allocator.allocate(other_capacity);
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
            m_allocator.deallocate(m_begin, other_capacity);
            m_begin = nullptr;
            m_end = nullptr;
            m_cap = nullptr;
            throw;  // 重新抛出异常
        }
    }
}

// 带分配器的拷贝构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector& other, const allocator_type& alloc) : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    size_type other_size = other.m_end - other.m_begin;
    if (other_size > 0)
    {
        size_type other_capacity = other.m_cap - other.m_begin;
        // 先分配内存
        m_begin = m_allocator.allocate(other_capacity);
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
            m_allocator.deallocate(m_begin, other_capacity);
            m_begin = nullptr;
            m_end = nullptr;
            m_cap = nullptr;
            throw;  // 重新抛出异常
        }
    }
}

// 移动构造函数 (C++11) - noexcept 保证
template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other) noexcept
    : m_begin(other.m_begin)
    , m_end(other.m_end)
    , m_cap(other.m_cap)
    , m_allocator(std::move(other.m_allocator))
{
    // 将源对象置为有效但未指定的状态
    other.m_begin = nullptr;
    other.m_end = nullptr;
    other.m_cap = nullptr;
}

// 带分配器的移动构造函数
template<typename T, typename Allocator>
vector<T, Allocator>::vector(vector&& other, const allocator_type& alloc)
    : m_begin(nullptr), m_end(nullptr), m_cap(nullptr), m_allocator(alloc)
{
    if (alloc == other.m_allocator)
    {
        // 分配器相同，直接移动
        m_begin = other.m_begin;
        m_end = other.m_end;
        m_cap = other.m_cap;

        other.m_begin = nullptr;
        other.m_end = nullptr;
        other.m_cap = nullptr;
    }
    else
    {
        // 分配器不同，需要重新分配并移动元素
        size_type other_size = other.m_end - other.m_begin;
        if (other_size > 0)
        {
            size_type other_capacity = other.m_cap - other.m_begin;
            m_begin = m_allocator.allocate(other_capacity);
            m_end = m_begin;
            m_cap = m_begin + other_capacity;

            try
            {
                for (iterator src_it = other.m_begin; src_it != other.m_end; ++src_it, ++m_end)
                {
                    new (m_end) T(std::move(*src_it));
                }
            }
            catch (...)
            {
                clear();
                m_allocator.deallocate(m_begin, other_capacity);
                m_begin = nullptr;
                m_end = nullptr;
                m_cap = nullptr;
                throw;
            }
        }
    }
}

// 拷贝赋值运算符 - 使用 copy-and-swap 惯用法
template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other)
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
template<typename T, typename Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept
{
    if (this != &other)  // 自移动检查
    {
        // 清理当前对象的资源
        clear();
        if (m_begin)
        {
            m_allocator.deallocate(m_begin, m_cap - m_begin);
        }

        // 移动资源
        m_begin = other.m_begin;
        m_end = other.m_end;
        m_cap = other.m_cap;
        m_allocator = std::move(other.m_allocator);

        // 将源对象置为有效但未指定的状态
        other.m_begin = nullptr;
        other.m_end = nullptr;
        other.m_cap = nullptr;
    }
    return *this;
}

// 交换函数 - noexcept 保证
template<typename T, typename Allocator>
void vector<T, Allocator>::swap(vector& other) noexcept
{
    std::swap(m_begin, other.m_begin);
    std::swap(m_end, other.m_end);
    std::swap(m_cap, other.m_cap);
    std::swap(m_allocator, other.m_allocator);
}

// 访问容器中的元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type index)
{
    // 检查索引是否越界
    if (index >= static_cast<size_type>(m_end - m_begin))
    {
        throw std::out_of_range("Index out of range");
    }
    return m_begin[index];
}

// const版本的访问容器中的元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type index) const
{
    // 检查索引是否越界
    if (index >= static_cast<size_type>(m_end - m_begin))
    {
        throw std::out_of_range("Index out of range");
    }
    return m_begin[index];
}

// 带边界检查的元素访问
template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type index)
{
    if (index >= static_cast<size_type>(m_end - m_begin))
    {
        throw std::out_of_range("vector::at: index out of range");
    }
    return m_begin[index];
}

// const版本的带边界检查的元素访问
template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type index) const
{
    if (index >= static_cast<size_type>(m_end - m_begin))
    {
        throw std::out_of_range("vector::at: index out of range");
    }
    return m_begin[index];
}

// 访问第一个元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front()
{
    if (m_begin == m_end)
    {
        throw std::out_of_range("vector::front: container is empty");
    }
    return *m_begin;
}

// const版本的访问第一个元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const
{
    if (m_begin == m_end)
    {
        throw std::out_of_range("vector::front: container is empty");
    }
    return *m_begin;
}

// 访问最后一个元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back()
{
    if (m_begin == m_end)
    {
        throw std::out_of_range("vector::back: container is empty");
    }
    return *(m_end - 1);
}

// const版本的访问最后一个元素
template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const
{
    if (m_begin == m_end)
    {
        throw std::out_of_range("vector::back: container is empty");
    }
    return *(m_end - 1);
}

// 返回指向底层数组的指针
template<typename T, typename Allocator>
typename vector<T, Allocator>::pointer vector<T, Allocator>::data()
{
    return m_begin;
}

// const版本的返回指向底层数组的指针
template<typename T, typename Allocator>
typename vector<T, Allocator>::const_pointer vector<T, Allocator>::data() const
{
    return m_begin;
}

// 在容器末尾添加元素 - 拷贝版本
template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(const T& value)
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
template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(T&& value)
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
template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back()
{
    if (m_begin != m_end)
    {
        --m_end;
        m_end->~T();  // 显式调用析构函数
    }
}

// 在容器末尾直接构造元素，使用完美转发
template<typename T, typename Allocator>
template<typename... Args>
void vector<T, Allocator>::emplace_back(Args&&... args)
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
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T& value)
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
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, T&& value)
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
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos)
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
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
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
template<typename T, typename Allocator>
void vector<T, Allocator>::clear()
{
    for (iterator it = m_begin; it != m_end; ++it)
    {
        it->~T();  // 显式调用每个元素的析构函数
    }
    m_end = m_begin;
}

// 获取容器中元素的个数
template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
{
    return m_end - m_begin;
}

// 获取容器的容量
template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const
{
    return m_cap - m_begin;
}

// 扩展容器容量 - 异常安全版本
template<typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type newCapacity)
{
    size_type current_capacity = m_cap - m_begin;
    if (newCapacity > current_capacity)
    {
        size_type current_size = m_end - m_begin;

        // 分配新内存
        T* newElements = m_allocator.allocate(newCapacity);

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
            m_allocator.deallocate(newElements, newCapacity);
            throw;  // 重新抛出异常，保持原有对象状态不变
        }

        // 成功后释放旧内存
        // 手动销毁旧元素
        for (iterator it = m_begin; it != m_end; ++it)
        {
            it->~T();
        }
        if (m_begin)
        {
            m_allocator.deallocate(m_begin, current_capacity);
        }

        // 更新指针
        m_begin = newElements;
        m_end = m_begin + current_size;
        m_cap = m_begin + newCapacity;
    }
}

// 减少容量以适应元素数量
template<typename T, typename Allocator>
void vector<T, Allocator>::shrink_to_fit()
{
    size_type current_size = size();
    if (capacity() > current_size)
    {
        if (current_size == 0)
        {
            // 如果为空，释放所有内存
            clear();
            if (m_begin)
            {
                m_allocator.deallocate(m_begin, m_cap - m_begin);
            }
            m_begin = m_end = m_cap = nullptr;
            return;
        }

        // 分配新内存
        T* newElements = m_allocator.allocate(current_size);

        try
        {
            // 移动旧元素到新内存
            size_type i = 0;
            for (iterator it = m_begin; it != m_end; ++it, ++i)
            {
                new (&newElements[i]) T(std::move(*it));
            }
        }
        catch (...)
        {
            // 如果移动失败，释放新分配的内存
            m_allocator.deallocate(newElements, current_size);
            throw; // 重新抛出异常，保持原有对象状态不变
        }

        // 成功后释放旧内存
        // 手动销毁旧元素
        size_type old_capacity = m_cap - m_begin;
        for (iterator it = m_begin; it != m_end; ++it)
        {
            it->~T();
        }
        m_allocator.deallocate(m_begin, old_capacity);

        // 更新指针
        m_begin = newElements;
        m_end = m_begin + current_size;
        m_cap = m_begin + current_size;
    }
}

// 更改容器中元素的数量 - 版本1：默认值
template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count)
{
    resize(count, T());
}

// 更改容器中元素的数量 - 版本2：指定值
template<typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type count, const T& value)
{
    size_type current_size = size();

    if (count < current_size)
    {
        // 缩小：销毁多余的元素
        iterator new_end = m_begin + count;
        for (iterator it = new_end; it != m_end; ++it)
        {
            it->~T();
        }
        m_end = new_end;
    }
    else if (count > current_size)
    {
        // 扩大：添加新元素
        reserve(count); // 确保有足够容量，可能会重新分配
        for (size_type i = current_size; i < count; ++i)
        {
            new (m_end) T(value); // 拷贝构造新元素
            ++m_end;
        }
    }
    // 如果 count == current_size，什么都不做
}

// 打印容器中的元素
template<typename T, typename Allocator>
void vector<T, Allocator>::printElements() const
{
    for (iterator it = m_begin; it != m_end; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// 比较操作符重载
template<typename T, typename Allocator>
bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template<typename T, typename Allocator>
bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename Allocator>
bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Allocator>
bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    return rhs < lhs;
}

template<typename T, typename Allocator>
bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template<typename T, typename Allocator>
bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{
    return !(lhs < rhs);
}

// 非成员swap函数，支持 ADL (Argument Dependent Lookup)
template<typename T, typename Allocator>
void swap(vector<T, Allocator>& lhs, vector<T, Allocator>& rhs) noexcept
{
    lhs.swap(rhs);
}
