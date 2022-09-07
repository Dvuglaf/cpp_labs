#pragma once
typedef unsigned long int ulint;
template<typename T>
class iterator
{
    T* ptr;
public:
    iterator() :ptr(nullptr) {}
    iterator(T* resource) {ptr = resource;}
    iterator& operator++()
    {
        ++ptr;
        return *this;
    }
    T* operator->() const noexcept
    {
        return ptr;
    }
    iterator& operator++(int)
    {
        iterator temp(*this);
        ++ptr;
        return temp;
    }
    T& operator*() const
    {
        return *ptr;
    }
    bool operator ==(const iterator& rhs) const
    {
        return ptr == rhs.ptr;
    }
    bool operator !=(const iterator& rhs) const
    {
        return !(ptr == rhs.ptr);
    }
    iterator& operator--()
    {
        --ptr;
        return *this;
    }
    iterator& operator--(int)
    {
        iterator temp(*this);
        --ptr;
        return temp;
    }
    iterator& operator=(const iterator& second)
    {
        ptr = second.ptr;
        return *this;
    }
};

template<typename T>
class vector
{
    T* value;
    ulint count;
public:
    ~vector()
    {
        if (count > 0)
            clear();
    }
    explicit vector(ulint size) :value(new T[size]), count(size){}
    vector() : value(nullptr), count(0) {}
    vector(ulint size, const T& key) : count(size) {
        value = new T[count];
        for (ulint i = 0; i < count; ++i)
        {
            value[i] = key;
        }
    }
    vector(T* arr, size_t size) {
        value = new T[size];
        for (size_t i = 0; i < size; ++i) {
            value[i] = arr[i];
        }
    }
    vector(const vector& resource) : value(new T[resource.count]), count(resource.count)
    {
        for (ulint i = 0; i < count; ++i)
            value[i] = resource.value[i];
    }
    vector(vector&& resource) noexcept :  value(resource.value), count(resource.count)//ctor �������
    {
        resource.count = 0;
        resource.value = nullptr;
    }
    vector& operator=(const vector& rhs)
    {
        auto new_value = new T[rhs.count];
        for (ulint i = 0; i < rhs.count; ++i)
            new_value[i] = rhs.value[i];
        delete[] value;
        value = new_value;
        count = rhs.count;
        return *this;
    }
    T& operator[](size_t index) {
        return value[index];
    }
    vector& operator=(vector&& rhs) noexcept
    {
        std::cout << "=move";
        delete[] value;
        value = rhs.value;
        count = rhs.count;
        rhs.value = nullptr;
        rhs.count = 0;
        return *this;
    }
    ulint size() const noexcept
    {
        return count;
    }
    iterator<T> begin()
    {
        return iterator<T>(value);
    }
    iterator<T> begin() const
    {
        return iterator<T>(value);
    }
    iterator<T> end()
    {
        return iterator<T>(value + count);
    }
    const iterator<T> end() const
    {
        return iterator<T>(value + count);
    }
    iterator<T> insert(iterator<T> it, const T& key)
    {
        auto temp = new T[count + (ulint)1]();
        iterator<T> beg = begin();
        iterator<T> it_temp(temp);
        iterator<T> ret;
        while (beg != it)
        {
            *it_temp = *beg;
            ++beg;
            ++it_temp;
        }
        *it_temp = key;
        ret = it_temp;
        it_temp++;
        while (beg != end())
        {
            *it_temp = *beg;
            ++it_temp;
            ++beg;
        }
        delete[] value;
        ++count;
        value = temp;
        return ret;
    }
    iterator<T> erase(iterator<T> it)
    {
        if (count == 0)
            return end();
        auto temp = new T[count - (ulint)1]();
        iterator<T> beg;
        beg=begin();
        iterator<T> it_temp(temp);
        iterator<T> ret;
        while (beg != it)
        {
            *it_temp = *beg;
            ++it_temp;
            ++beg;
        }
        ret = ++beg;
        while (beg != end())
        {
            *it_temp = *beg;
            ++it_temp;
            ++beg;
        }
        delete[] value;
        --count;
        value = temp;
        return ret;
    }
    void clear()
    {
        delete[] value;
        count = 0;
    }
};