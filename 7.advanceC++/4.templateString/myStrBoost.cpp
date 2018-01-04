#include <ctype.h>
#include <wctype.h>
#include <iostream>

#include "myStrBoost.h"

namespace advcpp
{

template<>
void ToUpper(String_t<char>& _str)
{
	for(unsigned int i = 0; i < _str.Length(); ++i)
	{
		_str[i] = toupper(_str[i]);
	}
}

template<>
void ToUpper(String_t<wchar_t>& _str)
{
	for(unsigned int i = 0; i < _str.Length(); ++i)
	{
		_str[i] = towupper(_str[i]);
	}
}


template<>
void ToLower(advcpp::String_t<char>& _str)
{
	for(unsigned int i = 0; i < _str.Length(); ++i)
	{
		_str[i] = tolower(_str[i]);
	}
}

template<>
void ToLower(advcpp::String_t<wchar_t>& _str)
{
	for(unsigned int i = 0; i < _str.Length(); ++i)
	{
		_str[i] = towlower(_str[i]);
	}
}

}
