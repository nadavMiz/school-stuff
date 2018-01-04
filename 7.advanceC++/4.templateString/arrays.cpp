#include "arrays.h"

namespace advcpp
{

template<>
unsigned int ArrayCompare(const char* _a, const char* _b)
{
	return strcmp(_a, _b);
}

template<>
unsigned int ArrayCompare(const wchar_t* _a, const wchar_t* _b)
{
	return wcscmp(_a, _b);
}

template<>
unsigned int ArrayLength(const char* _array)
{
	return strlen(_array);
}

template<>
unsigned int ArrayLength(const wchar_t* _array)
{
	return wcslen(_array);
}

}
