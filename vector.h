#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <limits>
#include <stdexcept>

template <typename T>
class Vector
{
public:
	explicit Vector();
	explicit Vector(size_t n, const T& val);
	Vector(const Vector<T>& other);
	~Vector();
	Vector<T>& operator=(const Vector<T>& other);

	size_t size() const;
	size_t max_size() const;
	void resize (size_t n,T val);
	size_t capacity() const;
	bool empty() const;
	void reserve(size_t n);

	T& operator[] (size_t n);
	const T& operator[] (size_t n) const;
	T& at (size_t n);
	const T& at (size_t n) const;
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	T* data() noexcept;
	const T* data() const noexcept;
	void assign(size_t n, const T& val);
	void push_back(T val);
	void pop_back();
	void insert(T val, size_t index);
	T* erase (T* position);
	T* erase (T* first, T* last);
	void swap (Vector& x);
	void clear();

private:
    	T* m_vector;
    	size_t m_capacity;
    	size_t m_size;
};

template<typename T>
Vector<T>::Vector():m_vector(NULL), m_capacity(0), m_size (0)
{

}

template<typename T>
inline Vector<T>::Vector(size_t n, const T &val): m_vector(new T[n]), m_size(n), m_capacity(n)
{
	for(size_t i =0; i < m_size; i++)
        	m_vector[i]=val;
}

template<typename T>
inline Vector<T>::Vector(const Vector<T> &other):m_vector(new T[other.m_capacity]),m_size(other.m_size), m_capacity(other.m_capacity)
{
	for(size_t i=0; i<m_capacity; i++)
        	m_vector[i]=other.m_vector[i];
}

template<typename T>
Vector<T>::~Vector()
{
    	delete [] m_vector;
	m_vector = NULL;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector<T> &other)
{
	if(this != &other)
   	{	
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_vector;
		m_vector = new T[other.m_capacity];
		for(size_t i = 0; i < other.m_size; i++)
		{
			m_vector[i] = (other.m_vector)[i];
		}
	}
	return *this;
}

template<typename T>
inline size_t Vector<T>::size() const
{
    return m_size;
}

template<typename T>
inline size_t Vector<T>::max_size() const
{
    return std::numeric_limits<size_t>::max();
}

template<typename T>
inline void Vector<T>::resize(size_t n, T val)
{
	if(n == m_size)
		return;
	else if(n < m_size)
	{
		for(size_t i = m_size-1; i >= n-1; i--)
			pop_back();
		return;
	}
	Vector tmp;
	tmp.m_vector = new T[n];
	tmp.m_size = n;
	tmp.m_capacity = n;
	for(size_t i = 0; i < n; i++)
	{	
		if(i < m_size)
			tmp.m_vector[i] = m_vector[i];
		else
			tmp.m_vector[i] = val;
	}
	delete[] m_vector;
	*this = tmp;
}

template<typename T>
inline size_t Vector<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
inline bool Vector<T>::empty() const
{
    return m_vector==NULL;
}

template<typename T>
inline void Vector<T>::reserve(size_t n)
{
	if(n <= m_capacity)
		return;
	T *tmp = new T[n];
	for(size_t i = 0; i < m_size; i++)
		tmp[i] = m_vector[i];
	delete[] m_vector;
	m_vector = tmp;
	m_capacity = n;
}

template<typename T>
inline T& Vector<T>::operator[](size_t n)
{
    return m_vector[n];
}

template<typename T>
inline const T& Vector<T>::operator[](size_t n) const
{
    return m_vector[n];
}

template<typename T>
inline T& Vector<T>::at(size_t n)
{
    	if(n > m_size)
	{
        	throw std::out_of_range("invalid index");
    	}
    	return m_vector[n];
}

template<typename T>
inline const T& Vector<T>::at(size_t n) const
{
    	if(n > m_size)
	{
        	throw std::out_of_range("invalid index");
   	}
    	return m_vector[n];
}

template<typename T>
inline T& Vector<T>::front()
{
	return m_vector[0];
}

template<typename T>
inline const T& Vector<T>::front() const
{
	return m_vector[0];
}

template<typename T>
inline T& Vector<T>::back()
{
	return m_vector[m_size-1];
}

template<typename T>
inline const T& Vector<T>::back() const
{
    	return m_vector[m_size-1];
}

template<typename T>
inline T* Vector<T>::data()  noexcept
{
    return m_vector;
}

template<typename T>
inline const T* Vector<T>::data() const  noexcept
{
    return m_vector;
}
template<typename T>
inline void Vector<T>::assign(size_t n, const T& val)
{
	this->clear();
	for(size_t i = 0; i< n; i++)
		this->push_back(val);
	 
}
template<typename T>
void Vector<T>::push_back(T val)
{
	insert(val,m_size);
}
template<typename T>
inline void Vector<T>::pop_back()
{
	if(m_size==0)
	{
		throw std::underflow_error("underflow error");
	}
	else
	{	
		m_size--;
		m_vector[m_size].~T();
	}
}
template<typename T>
void Vector<T>::insert(T val, size_t index)
{
   	size_t i=m_size;
	if(index>m_size)
	{
		throw std::out_of_range("bad index error");
	}
	else
	{
		if(m_capacity == m_size)
		{
			int* temp = new int[2 * m_capacity];
			for (int i = 0; i < m_capacity; i++)
			{ 
		    		temp[i] = m_vector[i]; 
		    	} 
		    delete[] m_vector;
		    m_capacity *= 2; 
		    m_vector = temp;	 
		}
		if(m_size<=index)
		{
			m_vector[index] = val;
			m_size = index+1;
		}
		else
		{
			while(i>index)
			{
				m_vector[i]=m_vector[i-1];
				i--;
			}
			m_vector[index] = val;
			m_size++;
		}
	}
}

template<typename T>
inline T* Vector<T>::erase(T* pos)
{

	size_t i=0;
	while(true)
	{
		if(m_vector+i==pos)
		{
			m_vector[i].~T();
			break;
		}
		i++;
	}
	for(;i<m_size;i++)
	{
		m_vector[i] = m_vector[i+1];
	}
	m_size--;
	return m_vector;
}

template<typename T>
inline T* Vector<T>::erase(T* first, T* last)
{
	for(T* i = first; i < last; i++)
		erase(i);
	return m_vector;
}

template<typename T>
inline void Vector<T>::swap(Vector<T>& x)
{
	Vector tmp;
	tmp = x;
	x = *this;
	*this = tmp;
	
}

template<typename T>
inline void Vector<T>::clear()
{
	for(size_t i = 0; i < m_size; i++)
		pop_back();
}

template<typename T>
inline Vector<T> operator+(const Vector<T>& vec1, const Vector<T>& vec2)
{
	Vector<T> vec(vec1.size()+vec2.size(), '\0');
	for(size_t i=0;i<vec1.size();i++)
	{
		vec[i] = vec1[i];
	}
	for(size_t i=0;i<vec2.size();i++)
	{
		vec[i+vec1.size()] = vec2[i];
	}
	return vec;
}

template<typename T>
inline Vector<T>& operator+=(Vector<T>& vec1, const Vector<T>& vec2)
{
	for(size_t i=0;i<vec2.size();i++)
	{
		vec1.push_back(vec2[i]);
	}
	return vec1;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out,const Vector<T>& vec)
{
	for(size_t i=0;i<vec.size();i++)
	{
		out<<vec[i]<<" ";
	}
	return out;
}
#endif
