#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "strings.h"

using namespace std;

/*-------------------------------*/

void String_t::NullInitializer()
{
	m_string = new char[1];
	if(NULL == m_string)
	{
		//TODO something
		return;
	}
	m_string[0] = '\0';
	m_length = 0;
}

/*-------------------------------*/

String_t::String_t()
{
	NullInitializer();
}

/*--------------------------------*/

String_t::String_t(const char* _str)
{
	if(NULL == _str)
	{
		NullInitializer();
		return;
	}
	
	m_length = strlen(_str);
	m_string = new char[m_length + 1];
	if(NULL == m_string)
	{
		//TODO something
		return;
	}
	
	strcpy(m_string, _str);
}

/*---------------------------------*/

String_t::String_t(const String_t& _str)
{
	m_string = new char[_str.m_length + 1];
	if(NULL == m_string)
	{
		//TODO something
		return;
	}
	strcpy(m_string, _str.m_string);
	
	m_length = _str.m_length;
	return;
}

/*---------------------------------*/

String_t::~String_t()
{
	delete[] m_string;
}

/*--------------------------------*/

String_t& String_t::operator=(const String_t& _str)
{
	if(this == &_str)
	{
		return *this;
	}
	
	if(m_length < _str.m_length)
	{
		char* newString = new char[_str.m_length + 1];
		if(NULL == newString)
		{
			return *this;
		}
		delete[] m_string;
		m_string = newString;
	}
	
	m_length = _str.m_length;
	
	strcpy(m_string, _str.m_string);
	
	return *this;
}

/*---------------------------------*/

size_t String_t::Length() const
{
	return m_length;
}

/*---------------------------------*/

void String_t::SetString(const char* _str)
{
	if(NULL == _str)
	{
		return;
	}
	
	size_t newLength = strlen(_str);
	
	// replace old string
	char* newString = new char[newLength + 1];
	if(NULL == newString)
	{
		return;
	}
	
	m_length = newLength;
	
	delete[] m_string;
	m_string = newString;
	strcpy(m_string, _str);
}

/*---------------------------------*/

const char* String_t::GetString() const
{
	return m_string;
}

/*---------------------------------*/

size_t String_t::Compare(const String_t& _str) const
{

	int result = strcmp(m_string, _str.m_string);
	
	return((0 == result) ? 0 : ((0 > result) ? 1 : 0));
}

/*----------------------------------*/

void String_t::Print() const
{
	printf("%s\n", m_string);
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
	char* newString = new char[newLength + 1];
	if(NULL == newString)
	{
		return;
	}
	
	// create new string
	m_length = newLength;
	strcpy(newString, _str);
	strcat(newString, m_string);
	
	//replace old string
	delete[] m_string;
	m_string = newString;
}

/*-------------------------------------*/

void String_t::Prepend(const String_t& _str)
{
	size_t newLength = _str.m_length + m_length;
	char* newString = new char[newLength + 1];
	if(NULL == newString)
	{
		return;
	}
	
	// create new string
	m_length = newLength;
	strcpy(newString, _str.m_string);
	strcat(newString, m_string);
	
	//replace old string
	delete[] m_string;
	m_string = newString;
}

/*----------------------------------------*/

String_t& String_t::operator+=(const String_t& _str)
{
	size_t newLength = _str.m_length + m_length;
	char* newString = new char[newLength + 1];
	if(NULL == newString)
	{
		return *this;
	}
	
	// create new string
	m_length = newLength;
	strcpy(newString, m_string);
	strcat(newString, _str.m_string);
	
	//replace old string
	delete[] m_string;
	m_string = newString;
	
	return *this;
}

/*----------------------------------------*/

String_t& String_t::operator+=(const char* _str)
{
	if(NULL == _str)
	{
		return *this;
	}
	
	size_t newLength = m_length + strlen(_str);
	
	char* newString = new char[newLength + 1];
	if(NULL == newString)
	{
		return *this;
	}
	
	// create new string
	m_length = newLength;
	strcpy(newString, m_string);
	strcat(newString, _str);
	
	//replace old string
	delete[] m_string;
	m_string = newString;
	
	return *this;
}

/*-------------------------------------------*/

int String_t::Contains(const String_t& _str) const
{
	if(_str.m_length > m_length)
	{
		return 0;
	}
	
	return (NULL != strstr(m_string, _str.m_string));
}

/*--------------------------------------------*/

int String_t::operator<(const String_t& _str) const
{
	return (strcmp(m_string, _str.m_string) < 0);
}

/*--------------------------------------------*/

int String_t::operator>(const String_t& _str) const
{
	return (strcmp(m_string, _str.m_string) > 0);
}

/*--------------------------------------------*/

int String_t::operator<=(const String_t& _str) const
{
	return (strcmp(m_string, _str.m_string) <= 0);
}

/*--------------------------------------------*/

int String_t::operator>=(const String_t& _str) const
{
	return (strcmp(m_string, _str.m_string) >= 0);
}

/*--------------------------------------------*/

int String_t::operator==(const String_t& _str) const
{	
	if(m_length != _str.m_length)
	{
		return 0;
	}
	return (strcmp(m_string, _str.m_string) == 0);
}

/*--------------------------------------------*/

int String_t::operator!=(const String_t& _str) const
{
	return (strcmp(m_string, _str.m_string) != 0);
}

/*--------------------------------------------*/

/*--------------------------------------------*/

int String_t::operator<(const char* _str) const
{
	if(NULL == _str)
	{
		return 0;
	}
	
	return (strcmp(m_string, _str) < 0);
}

/*--------------------------------------------*/

int String_t::operator>(const char* _str) const
{
	if(NULL == _str)
	{
		return 1;
	}
	
	return (strcmp(m_string, _str) > 0);
}

/*--------------------------------------------*/

int String_t::operator<=(const char* _str) const
{
	if(NULL == _str)
	{
		return 0;
	}
	
	return (strcmp(m_string, _str) <= 0);
}

/*--------------------------------------------*/

int String_t::operator>=(const char* _str) const
{
	if(NULL == _str)
	{
		return 1;
	}
	
	return (strcmp(m_string, _str) >= 0);
}

/*--------------------------------------------*/

int String_t::operator==(const char* _str) const
{
	if(NULL == _str)
	{
		return 0;
	}
	
	return (strcmp(m_string, _str) == 0);
}

/*--------------------------------------------*/

int String_t::operator!=(const char* _str) const
{
	return (strcmp(m_string, _str) != 0);
}

/*--------------------------------------------*/

char String_t::operator[](size_t _index) const
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
