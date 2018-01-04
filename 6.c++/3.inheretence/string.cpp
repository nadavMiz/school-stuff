#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "Buffer.h"
#include "strings.h"

using namespace std;

size_t String_t::m_defaultCapacity = 32;
size_t String_t::m_blockSize = 32;
bool String_t::m_caseSens = true;

/*-------------------------------*/

size_t String_t::GetNewCapacity(size_t _length)
{
	size_t capacity = m_defaultCapacity;
	while(_length > capacity)
	{
		capacity += m_blockSize;
	}
	return capacity;
}

/*--------------------------------*/

/*---------------------------------*/

String_t::String_t(const String_t& _str)
{
	m_capacity = m_defaultCapacity;
	CreateFromString(_str.m_buffer);
}

/*---------------------------------*/

void String_t::SetString(const char* _str)
{
	char* tmp = m_buffer;
	CreateFromString(_str);
	if(tmp != m_buffer)
	{
		delete tmp;
	}
}

/*---------------------------------*/

String_t& String_t::operator=(const char* _str)
{
	SetString(_str);
	return *this;
}

/*--------------------------------*/

String_t& String_t::operator=(const String_t& _str)
{
	SetString(_str.m_buffer);
	return *this;
}

/*---------------------------------*/

size_t String_t::Compare(const String_t& _str) const
{

	int result;
	
	if(m_caseSens)
	{
		result = strcmp(m_buffer, _str.m_buffer);
	}
	else
	{
		result = strcasecmp(m_buffer, _str.m_buffer);
	}
	
	return((0 == result) ? 0 : ((0 > result) ? 1 : 2));
}

/*-----------------------------------*/

void String_t::ConvertToLower()
{
	for(size_t i = 0; i < m_length; ++i)
	{
		m_buffer[i] = (char)tolower(m_buffer[i]);
	}
}

/*-----------------------------------*/

void String_t::ConvertToUpper()
{
	for(size_t i = 0; i < m_length; ++i)
	{
		m_buffer[i] = (char)toupper(m_buffer[i]);
	}
}

/*-------------------------------------*/

void String_t::Prepend(const char* _str)
{
	size_t newLength = strlen(_str) + m_length;
	
	size_t newCapacity = GetNewCapacity(newLength);
	char* newString = new char[newCapacity];
	if(NULL == newString)
	{
		return;
	}
	
	// create new string
	m_length = newLength;
	m_capacity = newCapacity;
	strcpy(newString, _str);
	strcat(newString, m_buffer);
	
	//replace old string
	delete[] m_buffer;
	m_buffer = newString;
}

/*----------------------------------------*/

String_t& String_t::operator+=(const char* _str)
{
	size_t newLength = strlen(_str) + m_length;
	size_t newCapacity = GetNewCapacity(newLength);
	
	if(newCapacity > m_capacity)
	{
		char* newString = RealocateString(newCapacity);
		if(NULL == newString)
		{
			return *this;
		}
		delete[] m_buffer;
		m_buffer = newString;
		
		m_capacity = newCapacity;
	}
	
	strcat(m_buffer, _str);
	
	m_length = newLength;
	
	return *this;
}

/*----------------------------------------*/

String_t& String_t::operator+=(const String_t& _str)
{
	*this += _str.m_buffer;
	return *this;
}

/*-------------------------------------------*/

bool String_t::Contains(const char* _str) const
{
	if(m_caseSens)
	{
		return (NULL != strstr(m_buffer, _str));
	}
	else
	{
		return (NULL != strcasestr(m_buffer, _str));
	}
}

/*-------------------------------------------*/

bool String_t::Contains(const String_t& _str) const
{
	if(_str.m_length > m_length)
	{
		return 0;
	}
	
	return Contains(_str.m_buffer);
}

/*--------------------------------------------*/

bool String_t::operator<(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (1 == Compare(_str));
}

/*--------------------------------------------*/

bool String_t::operator>(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (2 == Compare(_str));
}

/*--------------------------------------------*/

bool String_t::operator<=(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (2 != Compare(_str));
}

/*--------------------------------------------*/

bool String_t::operator>=(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (1 != Compare(_str));
}

/*--------------------------------------------*/

bool String_t::operator==(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (0 == Compare(_str));
}

/*--------------------------------------------*/

bool String_t::operator!=(const char* _str) const
{
	if(NULL == _str)
	{
		_str = "";
	}
	return (0 != Compare(_str));
}

/*--------------------------------------------*/

char& String_t::operator[](size_t _index) const
{
	if(_index > m_length)
	{
		_index = m_length - 1;
	}
	
	return m_buffer[_index];
}

/*----------------------------------------------*/

ostream& operator<<(ostream& _os, const String_t& _str)
{
	_os << _str.GetString();
	return _os;
}

/*----------------------------------------------*/

istream& operator>>(istream& _is, String_t& _str)
{
	char newStr[128];
	
	_is >> newStr;
	
	_str.SetString(newStr);
	
	return _is;
}

/*-----------------------------------------------*/

size_t String_t::FirstCharInString(const char _character) const
{
	char charecter = _character;
	char otherCharacter;
	if(m_caseSens == false)
	{
		charecter = (char)tolower(_character);
		otherCharacter = (char)toupper(_character);
	}
	
	size_t i;
	while(m_buffer[i] != '\0')
	{
		if(charecter == m_buffer[i])
		{
			break;
		}
		if(m_caseSens && otherCharacter == m_buffer[i])
		{
			break;
		}
		++i;
	}
	return i;
}

/*----------------------------------------------*/

size_t String_t::LastCharInString(const char _character) const
{
	char charecter = _character;
	char otherCharacter;
	if(m_caseSens == false)
	{
		charecter = (char)tolower(_character);
		otherCharacter = (char)toupper(_character);
	}
	
	for(size_t i = m_length - 1; i < m_length; --i)
	{
		if(charecter == m_buffer[i])
		{
			return i;
		}
		if(m_caseSens && otherCharacter == m_buffer[i])
		{
			return i;
		}
	}
	return m_length;
}

/*----------------------------------------------------*/

String_t String_t::operator()(size_t start, size_t len)
{
	if(start >= m_length)
	{
		return String_t();
	}
	
	size_t substringsEnd = start + len;
	if(substringsEnd >= m_length)
	{
		return String_t(m_buffer + start);
	}
	
	char tmp = m_buffer[substringsEnd];
	m_buffer[substringsEnd] = '\0';
	
	String_t newStr(m_buffer + start);
	
	m_buffer[substringsEnd] = tmp;
	
	return newStr;
}








