#include <stddef.h>
#include <string.h>

#include "strings.h"


/*--------------static functions----------------*/

static size_t countLen(char const *_str)
{
	size_t length = 0;
	while('\0' != _str[length])
	{
		++length;
	}
	return length;
}

/*---------------main functions-----------------*/

size_t StrLen(char const *_str)
{
	if(NULL == _str)
	{
		return 0;
	}
	return countLen(_str);
}

/*----------------------------------*/

static size_t StrLenRecHelper(char const *_str)
{
	if(_str[0] == '\0')
	{
		return 0;
	}
	return StrLenRecHelper(_str + 1) + 1;
}

size_t StrLenRec(char const *_str)
{
	if(NULL == _str)
	{
		return 0;
	}
	return StrLenRecHelper(_str);
}

/*-----------------------------------*/

int StrCompare(const char* _s1, const char* _s2)
{
	size_t i = 0;
	if(NULL == _s1 && NULL == _s2)
	{
		return 0;
	}
	if(NULL == _s1 && NULL != _s2)
	{
		return -1;
	}
	if(NULL != _s1 && NULL == _s2)
	{
		return 1;
	}
	while (_s1[i] != '\0' && _s2[i] != '\0' && _s1[i] == _s2[i])
	{
		++i;
	}
	return _s1[i] - _s2[i];
}

/*-----------------------------------------*/

static int StrCompareRecHelp(const char* _s1, const char* _s2)
{
	if(_s1[0] == '\0' || _s2[0] == '\0' || _s1[0] != _s2[0])
	{
		return _s1[0] - _s2[0];
	}
	return StrCompareRecHelp(_s1 + 1, _s2 + 1);
}

int StrCompareRec(const char* _s1, const char* _s2)
{
	if(NULL == _s1 && NULL == _s2)
	{
		return 0;
	}
	if(NULL == _s1 && NULL != _s2)
	{
		return -1;
	}
	if(NULL != _s1 && NULL == _s2)
	{
		return 1;
	}
	return StrCompareRecHelp(_s1, _s2);
}

/*-----------------------------------------*/

char* StrCopy(char* _destination, const char* _source)
{
	size_t i = 0;
	if(NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	
	while(_source[i] != '\0')
	{
		_destination[i] = _source[i];
		++i;
	}
	_destination[i] = '\0';
	
	return _destination;
}

/*------------------------------------------*/

void StrCopyRecHelper(char* _destination, const char* _source)
{
	_destination[0] = _source[0];
	if('\0' == _source[0])
	{
		return;
	}
	StrCopyRecHelper(_destination + 1, _source + 1);
}

char* StrCopyRec(char* _destination, const char* _source)
{
	if(NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	StrCopyRecHelper(_destination, _source);
	return _destination;
}

/*---------------------------------------------*/

char* StrNCopy(char* _destination, const char* _source, size_t _num)
{
	size_t i;
	if(NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	for(i = 0; i < _num; ++i)
	{
		_destination[i] = _source[i];
		if('\0' == _source[i])
		{
			break;
		}
	}
	return _destination;
}

/*-------------------------------------------------*/

static void  StrNCopyRecHelp(char* _destination, const char* _source, size_t num)
{
	_destination[0] = _source[0];
	if(num <= 1 || '\0' == _source[0])
	{
		return;
	}
	StrNCopyRecHelp(_destination + 1, _source + 1, num - 1);
}

char* StrNCopyRec(char* _destination, const char* _source, size_t num)
{
	if(NULL == _destination || NULL == _source)
	{
		return NULL;
	}
	StrNCopyRecHelp(_destination, _source, num);
	return _destination;
}

/*-----------------------------------------------------*/

char* StrConcat(char* _destination, const char* _source)
{
	size_t destIdx;
	size_t i = 0;
	if(NULL == _destination || NULL == _source)
	{
		return _destination;
	}
	destIdx = countLen(_destination);
	while('\0' != _source[i])
	{
		_destination[destIdx++] = _source[i++];
	}
	_destination[destIdx] = '\0';
	return _destination;
}

/*---------------------------------------------------*/

char* StrSubString(const char* _str, const char* _search)
{
	size_t searchLen;
	int i = 0;
	if(NULL == _str || NULL == _search)
	{
		return NULL;
	}
	searchLen = countLen(_search);
	while('\0' != _str[i])
	{
		if(0 == strncmp(&_str[i], _search, searchLen))
		{
			return (char*)&_str[i];
		}
		++i;
	}
	return NULL;
}
