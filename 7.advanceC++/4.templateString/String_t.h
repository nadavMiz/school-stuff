#ifndef __MY_STRING_IMP_H__
#define __MY_STRING_IMP_H__

#include <cstring>
#include <algorithm>
#include <iostream>

#include "Buffer.h"
#include "arrays.h"

namespace advcpp
{

template <class T>
class String_t
{
public:
	String_t();
	explicit String_t(const T* _str);
	String_t(const String_t& _str);
	//virtual ~String_t(); use defalult DTOR
	
	String_t& operator=(const String_t& _str);
	String_t& operator=(const T* _str);
	String_t operator+(const String_t& _str);
	String_t operator+(const T* _str);
	bool operator==(const String_t& _str) const;
	bool operator==(const T* _str) const;
	bool operator!=(const String_t& _str) const;
	bool operator!=(const T* _str) const;
	unsigned int Length() const;
	T& operator[](unsigned int _index);
	const T& operator[](unsigned int _index) const;
	const T* c_str() const;
	
	void ToLower(){}
	void ToUpper(){}

private:
	/* data */
	Buffer<T> m_buffer;
	
	String_t AddArray(const T* _str, unsigned int length);
};

template <class T>
String_t<T>::String_t(): m_buffer(1) { }

template <class T>
String_t<T>::String_t(const T* _str): 
		m_buffer(_str, ArrayLength(_str) + 1){}

template <class T>
String_t<T>::String_t(const String_t& _str): 
		m_buffer(_str.c_str(), _str.Length() + 1){}

template <class T>
String_t<T>& String_t<T>::operator=(const String_t& _str)
{
	m_buffer.SetArray(_str.c_str(), _str.Length() + 1);
	
	return *this;
}

template <class T>
String_t<T>& String_t<T>::operator=(const T* _str)
{
	m_buffer.SetArray(_str, ArrayLength(_str) + 1);
	
	return *this;
}

template <class T>
unsigned int String_t<T>::Length() const
{
	return m_buffer.Length() - 1;
}

template <class T>
const T& String_t<T>::operator[](unsigned int _index) const
{
	return m_buffer[_index];
}

template <class T>
T& String_t<T>::operator[](unsigned int _index)
{
	return m_buffer[_index];
}

template <class T>
const T* String_t<T>::c_str() const
{
	return m_buffer.AsArray();
}

template <class T>
bool String_t<T>::operator!=(const String_t& _str) const
{
	return !(*this == _str);
}

template <class T>
bool String_t<T>::operator!=(const T* _str) const
{
	return !(*this == _str);
}

template <class T>
bool String_t<T>::operator==(const String_t& _str) const
{
	unsigned int length = Length();
	
	if(_str.Length() != length)
	{
		return false;
	}
	
	return (0 == ArrayCompare(c_str(), _str.c_str()));
}

template <class T>
bool String_t<T>::operator==(const T* _str) const
{
	return (0 == ArrayCompare(c_str(), _str));
}

template <class T>
String_t<T> String_t<T>::operator+(const String_t& _str)
{
	return AddArray(_str.c_str(), _str.Length());
}

template <class T>
String_t<T> String_t<T>::operator+(const T* _str)
{
	return AddArray(_str, ArrayLength(_str));
}

template <class T>
String_t<T> String_t<T>::AddArray(const T* _otherStr, unsigned int otherLength)
{
	unsigned int myLength = Length();
	
	T* newArray = new T[myLength + otherLength + 1];
	
	const T* array = c_str();
	std::copy(array, array + myLength, newArray);
	
	std::copy(_otherStr, _otherStr + otherLength + 1, newArray + myLength);
	
	String_t result(newArray);
	
	delete newArray;
	
	return result;
}

}
std::ostream& operator<<(std::ostream& _os, const advcpp::String_t<char>& _str);

std::wostream& operator<<(std::wostream& _os, const advcpp::String_t<wchar_t>& _str);

#endif /* __MY_STRING_IMP_H__ */
