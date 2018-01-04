#include <string.h>
#include <stdio.h>

int StrLen(char const *_str)
{
	int length = 1;
	char currentChar = _str[0];
	if(NULL == _str)
	{
		return 0;
	}
	while('\0' != currentChar)
	{
		currentChar = _str[length];
		++length;
	}
	return length - 1;
}

/*----------------------------------*/

int StrLenRecHelper(char const *_str)
{
	if(_str[0] == '\0')
	{
		return 0;
	}
	return StrLenRecHelper(_str + 1) + 1;
}

int StrLenRec(char const *_str)
{
	if(NULL == _str)
	{
		return 0;
	}
	return StrLenRecHelper(_str);
}

/*-----------------------------------*/

int main()
{
	char* str = "bloop";
	printf("length: %d\n", StrLen(str));
	printf("length rec: %d\n", StrLenRec(str));
	return 0;
}
