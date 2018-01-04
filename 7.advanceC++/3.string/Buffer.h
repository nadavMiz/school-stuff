#ifndef __BUFFER_H__
#define __BUFFER_H__

#include  <stdexcept>

template <class T>
class Buffer
{
	public:
		Buffer();
		explicit Buffer(unsigned int _capacity);
		Buffer(const T* _array, unsigned int _length);
		Buffer(const Buffer<T>& _buffer);
		~Buffer ();
		
		Buffer& operator=(const Buffer& _str);
		Buffer& SetArray(const T* _array, unsigned int _length);
		unsigned int Length() const;
		T& operator[](unsigned int _index);
		const T& operator[](unsigned int _index) const;
		void ChangeLength(unsigned int _newLength);
		const T* AsArray() const;
		 
	private:
		/* data */
		unsigned int m_length;
		unsigned int m_capacity;
		T* m_array;
};

template <class T>
Buffer<T>::Buffer(const T* _array, unsigned int _length): 
			m_length(_length), m_capacity(_length)
{	
	m_array = new T[_length];
	for(unsigned int i = 0; i < _length; ++i)
	{
		m_array[i] = _array[i];
	}
	
	m_length = _length;
}

template <class T>
Buffer<T>::Buffer(unsigned int _capacity):
		m_length(0), m_capacity(_capacity), m_array(0)
{}

template <class T>
Buffer<T>::Buffer(const Buffer<T>& _buffer): 
		m_length(_buffer.m_length)
,		m_capacity(_buffer.m_length)
{
	m_array = new T[m_length];
	for(unsigned int i = 0; i < m_length; ++i)
	{
		m_array[i] = _buffer.m_array[i];
	}
}

template <class T>
Buffer<T>::Buffer():
	m_length(0),
	m_capacity(0),
	m_array(0)
{}

template <class T>
Buffer<T>::~Buffer()
{
	if(0 != m_array)
	{
		delete[] m_array;
	}
}

template <class T>
unsigned int Buffer<T>::Length() const
{
	return m_length;
}

template <class T>
const T& Buffer<T>::operator[](unsigned int _index) const
{
	if(_index >= m_length - 1)
	{
		throw std::out_of_range("");
	}
	
	return m_array[_index]; 
}

template <class T>
T& Buffer<T>::operator[](unsigned int _index)
{
	const Buffer* self = static_cast<const Buffer* > (this);
	const T& result = (*self)[_index];
	return const_cast<T&>(result);
}

template <class T>
Buffer<T>& Buffer<T>::SetArray(const T* _array, unsigned int _length)
{
	if(_length > m_capacity)
	{
		T* tmp_buffer = new T[_length];
		
		delete[] m_array;
		m_array = tmp_buffer;
		
		m_capacity = _length;
	}
	
	m_length = _length;
	
	for(unsigned int i = 0; i < m_length; ++i)
	{
		m_array[i] = _array[i];
	}
	
	return *this;
}

template <class T>
Buffer<T>& Buffer<T>::operator=(const Buffer& _str)
{
	return SetArray(_str.AsArray(), _str.Length());
}

template <class T>
const T* Buffer<T>::AsArray() const
{
	return m_array;
}

template <class T>
void Buffer<T>::ChangeLength(unsigned int _newLength)
{
	if(_newLength < m_capacity)
	{
		return;
	}
	
	T* tmp_buffer = new T[_newLength];
	
	for(unsigned int i = 0; i < _newLength; ++i)
	{
		tmp_buffer[i] = m_array[i];
	}
		
	delete[] m_array;
	m_array = tmp_buffer;
	
	m_capacity = _newLength;
}

#endif /* __BUFFER_H__ */

