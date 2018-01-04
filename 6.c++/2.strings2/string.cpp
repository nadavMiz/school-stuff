#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "strings.h"

using namespace std;

size_t String_t::m_defaultCapacity = 32;
size_t String_t::m_blockSize = 32;
bool String_t::m_caseSens = true;

/*-------------------------------*/

size_t String_t::GetNewCapacity(size_t _length)
{
	size_t capacity = m_capacity;
	while(_length > capacity)
	{
		capacity += m_blockSize;
	}
	return capacity;
}

/*-------------------------------*/

char* String_t::RealocateString(size_t _newCapacity)
{
	char* newString = new char[m_capacity];
	if(NULL == newString)
	{
		return NULL;
	}
	strcpy(newString, m_string);
	
	return newString;
}

/*-------------------------------*/

void String_t::CreateFromString(const char* _str)
{
	if(NULL == _str)
	{
		_str = "";
	}
	
	size_t length = strlen(_str);
	
	// get the capacity
	size_t capacity = GetNewCapacity(length);
	
	// create the string
	char* string = new char[m_capacity];
	if(NULL == string)
	{
		return;
	}
	strcpy(string, _str);
	
	// set the class values
	m_length = length;
	m_capacity = capacity;
	m_string = string;
}

/*--------------------------------*/

String_t::String_t(const char* _str)
{
	m_capacity = m_defaultCapacity;
	CreateFromString(_str);
}

/*---------------------------------*/

String_t::String_t(const String_t& _str)
{
	m_capacity = m_defaultCapacity;
	CreateFromString(_str.m_string);
}

/*---------------------------------*/

void String_t::SetString(const char* _str)
{
	char* tmp = m_string;
	CreateFromString(_str);
	if(tmp != m_string)
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
	SetString(_str.m_string);
	return *this;
}

/*---------------------------------*/

size_t String_t::Compare(const String_t& _str) const
{

	int result;
	
	if(m_caseSens)
	{
		result = strcmp(m_string, _str.m_string);
	}
	else
	{
		result = strcasecmp(m_string, _str.m_string);
	}
	
	return((0 == result) ? 0 : ((0 > result) ? 1 : 2));
}

/*-----------------------------------*/

void String_t::ConvertToLower()
{
	for(size_t i = 0; i < m_length; ++i)
	{
		m_string[i] = (char)tolower(m_string[i]);
	}
}

/*-----------------------------------*/

void String_t::ConvertToUpper()
{
	for(size_t i = 0; i < m_length; ++i)
	{
		m_string[i] = (char)toupper(m_string[i]);
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
	strcat(newString, m_string);
	
	//replace old string
	delete[] m_string;
	m_string = newString;
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
		delete[] m_string;
		m_string = newString;
		
		m_capacity = newCapacity;
	}
	
	strcat(m_string, _str);
	
	m_length = newLength;
	
	return *this;
}

/*----------------------------------------*/

String_t& String_t::operator+=(const String_t& _str)
{
	*this += _str.m_string;
	return *this;
}

/*-------------------------------------------*/

bool String_t::Contains(const char* _str) const
{
	if(m_caseSens)
	{
		return (NULL != strstr(m_string, _str));
	}
	else
	{
		return (NULL != strcasestr(m_string, _str));
	}
}

/*-------------------------------------------*/

bool String_t::Contains(const String_t& _str) const
{
	if(_str.m_length > m_length)
	{
		return 0;
	}
	
	return Contains(_str.m_string);
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
	
	return m_string[_index];
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
	while(m_string[i] != '\0')
	{
		if(charecter == m_string[i])
		{
			break;
		}
		if(m_caseSens && otherCharacter == m_string[i])
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
		if(charecter == m_string[i])
		{
			return i;
		}
		if(m_caseSens && otherCharacter == m_string[i])
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
		return String_t(m_string + start);
	}
	
	char tmp = m_string[substringsEnd];
	m_string[substringsEnd] = '\0';
	
	String_t newStr(m_string + start);
	
	m_string[substringsEnd] = tmp;
	
	return newStr;
}








