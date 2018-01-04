#ifndef __MY_STRING_IMP_H__
#define __MY_STRING_IMP_H__

#include <cstring>

#include "Buffer.h"

namespace advcpp
{

class String_t
{
public:
	String_t();
	explicit String_t(const char* _str);
	String_t(const String_t& _str);
	//virtual ~String_t(); use defalult DTOR
	
	String_t& operator=(const String_t& _str);
	String_t& operator=(const char* _str);
	String_t operator+(const String_t& _str);
	String_t operator+(const char* _str);
	bool operator==(const String_t& _str) const;
	bool operator==(const char* _str) const;
	bool operator!=(const String_t& _str) const;
	bool operator!=(const char* _str) const;
	unsigned int Length() const;
	char& operator[](unsigned int _index);
	const char& operator[](unsigned int _index) const;
	const char* c_str() const;
	
	void ToLower(){}
	void ToUpper(){}

private:
	/* data */
	Buffer<char> m_buffer;
	
	String_t AddArray(const char* _str, unsigned int length);
};

inline String_t::String_t(): m_buffer("", 1) { }

inline String_t::String_t(const char* _str): 
		m_buffer(_str, strlen(_str) + 1){}

inline String_t::String_t(const String_t& _str): 
		m_buffer(_str.c_str(), _str.Length() + 1){}

inline String_t& String_t::operator=(const String_t& _str)
{
	m_buffer.SetArray(_str.c_str(), _str.Length() + 1);
	
	return *this;
}

inline String_t& String_t::operator=(const char* _str)
{
	m_buffer.SetArray(_str, strlen(_str) + 1);
	
	return *this;
}

inline unsigned int String_t::Length() const
{
	return m_buffer.Length() - 1;
}

inline const char& String_t::operator[](unsigned int _index) const
{
	return m_buffer[_index];
}

inline char& String_t::operator[](unsigned int _index)
{
	return m_buffer[_index];
}

inline const char* String_t::c_str() const
{
	return m_buffer.AsArray();
}

inline bool String_t::operator!=(const String_t& _str) const
{
	return !(*this == _str);
}

inline bool String_t::operator!=(const char* _str) const
{
	return !(*this == _str);
}

bool advcpp::String_t::operator==(const String_t& _str) const
{
	unsigned int length = Length();
	
	if(_str.Length() != length)
	{
		return false;
	}
	
	return (0 == strcmp(c_str(), _str.c_str()));
}

bool advcpp::String_t::operator==(const char* _str) const
{
	return (0 == strcmp(c_str(), _str));
}

advcpp::String_t advcpp::String_t::operator+(const String_t& _str)
{
	return AddArray(_str.c_str(), _str.Length());
}

advcpp::String_t advcpp::String_t::operator+(const char* _str)
{
	return AddArray(_str, strlen(_str));
}

advcpp::String_t advcpp::String_t::AddArray(const char* _otherStr, unsigned int otherLength)
{
	unsigned int myLength = Length();
	
	char* newArray = new char[myLength + otherLength + 1];
	
	const char* array = c_str();
	std::copy(array, array + myLength, newArray);
	
	std::copy(_otherStr, _otherStr + otherLength + 1, newArray + myLength);
	
	String_t result(newArray);
	
	delete newArray;
	
	return result;
}

}
#endif /* __MY_STRING_IMP_H__ */
