#pragma once

#include <iterator>  // for std::iterator_traits

// 反向迭代器模板类
template <typename Iterator>
class reverse_iterator
{
public:
    typedef Iterator                                                   iterator_type;
    typedef typename std::iterator_traits<Iterator>::value_type        value_type;
    typedef typename std::iterator_traits<Iterator>::difference_type   difference_type;
    typedef typename std::iterator_traits<Iterator>::pointer           pointer;
    typedef typename std::iterator_traits<Iterator>::reference         reference;

private:
    iterator_type current;

public:
    // 构造函数
    reverse_iterator() : current() {}
    explicit reverse_iterator(iterator_type iter) : current(iter) {}

    // 拷贝构造函数模板，允许从其他类型的反向迭代器构造
    template<typename Iter>
    reverse_iterator(const reverse_iterator<Iter>& other) : current(other.base()) {}

    // 获取底层迭代器
    iterator_type base() const { return current; }

    // 解引用操作符
    reference operator*() const
    {
        iterator_type temp = current;
        return *(--temp);
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    // 前置递增（向前移动，实际是底层迭代器向后移动）
    reverse_iterator& operator++()
    {
        --current;
        return *this;
    }

    // 后置递增
    reverse_iterator operator++(int)
    {
        reverse_iterator temp = *this;
        --current;
        return temp;
    }

    // 前置递减
    reverse_iterator& operator--()
    {
        ++current;
        return *this;
    }

    // 后置递减
    reverse_iterator operator--(int)
    {
        reverse_iterator temp = *this;
        ++current;
        return temp;
    }

    // 算术操作
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current - n);
    }

    reverse_iterator& operator+=(difference_type n)
    {
        current -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current + n);
    }

    reverse_iterator& operator-=(difference_type n)
    {
        current += n;
        return *this;
    }

    // 随机访问
    reference operator[](difference_type n) const
    {
        return *(*this + n);
    }

    // 比较操作符
    template<typename Iter>
    bool operator==(const reverse_iterator<Iter>& other) const
    {
        return current == other.base();
    }

    template<typename Iter>
    bool operator!=(const reverse_iterator<Iter>& other) const
    {
        return current != other.base();
    }

    template<typename Iter>
    bool operator<(const reverse_iterator<Iter>& other) const
    {
        return current > other.base();
    }

    template<typename Iter>
    bool operator<=(const reverse_iterator<Iter>& other) const
    {
        return current >= other.base();
    }

    template<typename Iter>
    bool operator>(const reverse_iterator<Iter>& other) const
    {
        return current < other.base();
    }

    template<typename Iter>
    bool operator>=(const reverse_iterator<Iter>& other) const
    {
        return current <= other.base();
    }
};

// 非成员函数：反向迭代器的算术操作
template<typename Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>& iter)
{
    return iter + n;
}

template<typename Iterator1, typename Iterator2>
auto operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
-> decltype(rhs.base() - lhs.base())
{
    return rhs.base() - lhs.base();
}
