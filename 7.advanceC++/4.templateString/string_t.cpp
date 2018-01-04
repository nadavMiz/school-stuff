#include "String_t.h"

std::ostream& operator<<(std::ostream& _os, const advcpp::String_t<char>& _str)
{
	_os << _str.c_str();
	
	return _os;
}

std::wostream& operator<<(std::wostream& _os, const advcpp::String_t<wchar_t>& _str)
{
	_os << _str.c_str();
	
	return _os;
}
