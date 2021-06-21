#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <exception>

//using size_type = std::size_t;
using size_type = unsigned int;

template <class T>
class Vector
{
private:
    size_type m_size;
    size_type m_capacity;
    T* m_array;
    static constexpr float c = 1.5;
public:
    explicit Vector();
    explicit Vector(size_type n);
    explicit Vector(size_type size, const T& value);
    explicit Vector(const Vector& vec);
    explicit Vector(Vector&& vec);
    ~Vector();
    void PushBack(const T& val);
    void PushBack(T&& val);
    void PopBack();
    size_type Size() const;
    size_type Capacity() const;
    bool Empty() const;
    void Reserve(size_type n);
    void ShrinkToFit();
    Vector<T>& operator=(Vector&& x);
    Vector<T>& operator=(const Vector& x);
    T& operator[](size_type n);
    const T& operator[](size_type n) const;
};

template <class T>
Vector<T>::Vector()
    :m_size(0),
    m_capacity(0),
    m_array(nullptr) {}

template <class T>
Vector<T>::Vector(size_type n):
    m_size(0),
    m_capacity(n)
{
    m_array = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(size_type n, const T& value):
    m_size(n),
    m_capacity(c * n)
{
    m_array = new T[m_capacity];
    for(size_type i = 0; i < m_size; ++i) {
        m_array[i] = value;
    }
}

template <class T>
Vector<T>::Vector(const Vector& vec):
    m_size(vec.m_size),
    m_capacity(vec.m_capacity)
{
    m_array = new T[m_capacity];
    for(size_type i = 0; i < m_size; ++i) {
        m_array[i] = vec.m_array[i];
    }
}

template <class T>
Vector<T>::Vector(Vector&& v)
{
    if(this != &v) {
        m_size = std::move(v.m_size);
        m_capacity = std::move(v.m_capacity);
        m_array = std::move(v.m_array);
        v.m_array = nullptr;
        v.m_size = 0;
        v.m_capacity = 0;
    }
}

template <class T>
Vector<T>::~Vector()
{
    delete [] m_array;
    m_array = nullptr;
}

template <class T>
void Vector<T>::PushBack(const T& val)
{
    if(m_size < m_capacity) {
        m_array[m_size] = val;
        ++m_size;
    } else {
        size_type old_capacity = m_capacity;
        m_capacity = c * old_capacity;
        T* n_array;
        n_array = new T[m_capacity];
        for(size_type i = 0; i < m_size; ++i) {
             n_array[i] = m_array[i];
        }
        n_array[m_size] = val;
        ++m_size;
        delete [] m_array;
        m_array = n_array;
    }
}

template <class T>
void Vector<T>::PushBack(T&& val)
{
    if(m_size < m_capacity) {
        m_array[m_size] = std::move(val);
        ++m_size;
    } else {
        size_type old_capacity = m_capacity;
        m_capacity = c * old_capacity;
        T* n_array;
        n_array = new T[m_capacity];
        for(size_type i = 0; i < m_size; ++i) {
            n_array[i] = std::move(m_array[i]);
        }
        n_array[m_size] = std::move(val);
        ++m_size;
        delete [] m_array;
        m_array = n_array;
    }
}

template <class T>
void Vector<T>::PopBack()
{
    if(m_size == 0) {
        throw std::invalid_argument("Vector is empty");
    }
    --m_size;
}

template <class T>
size_type Vector<T>::Size() const
{
    return m_size;
}

template <class T>
size_type Vector<T>::Capacity() const
{
    return m_capacity;
}

template <class T>
bool Vector<T>::Empty() const
{
    return m_size == 0;
}

template <class T>
void Vector<T>::Reserve(size_type n)
{
    m_capacity = n;
    if(m_size == 0) {
        m_array = new T[m_capacity];
        return;
    }
    T* array = m_array;
    m_array = new T[m_capacity];
    if(n < m_size) {
        m_size = m_capacity;
    }
    for(size_type i = 0; i < m_size; ++i) {
            m_array[i] = array[i];
    }
    delete [] array;
}

template <class T>
void Vector<T>::ShrinkToFit()
{
    m_capacity = m_size;
    T* array = m_array;
    m_array = new T[m_capacity];
    for(size_type i = 0; i < m_size; ++i) {
        m_array[i] = array[i];
    }
    delete [] array;
    array = nullptr;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x)
{
    if(this != &x) {
        m_size = x.m_size;
        m_capacity = x.m_capacity;
        delete m_array;
        m_array = new T[m_capacity];
        for(size_type i = 0; i < m_size; ++i) {
            m_array[i] = x.m_array[i];
        }
    }
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& x) {
    if(this != &x) {
        m_size = std::move(x.m_size);
        m_capacity = std::move(x.m_capacity);
        delete m_array;
        m_array = std::move(x.m_array);
        x.m_array = nullptr;
        x.m_size = 0;
        x.m_capacity = 0;
    }
    return *this;
}

template <class T>
T& Vector<T>::operator[](size_type n)
{
    if(n < 0 || n >= m_size) {
        throw std::out_of_range("out of range");
    } else {
        return m_array[n];
    }
}

template <class T>
const T& Vector<T>::operator[](size_type n) const
{
     if(n < 0 || n >= m_size) {
         throw std::out_of_range("out of range");
     } else {
         return m_array[n];
     }
}

#endif
