#include <string.h>
#include <stdio.h>
#include "fibonachi.h"

unsigned int Fib(unsigned int _index)
{
	int i;
	int result = 0;
	int preNum = 1;
	int prePreNum = 0;
	if(1 == _index)
	{
		result = 1;
	}
	for (i = 1; i < _index; ++i)
	{
		result = prePreNum + preNum;
		prePreNum = preNum;
		preNum = result;
	}
	return result;
	
	
}

unsigned int Factorial(unsigned int _index)
{
	if(_index == 0)
	{
		return 1;
	}
	return (_index * Factorial(_index - 1));
}


unsigned int FibRecursive(unsigned int _index)
{
	if(_index == 0)
	{
		return 0;
	}
	if(_index == 1)
	{
		return 1;
	}
	return FibRecursive(_index - 1) + FibRecursive(_index - 2);
}

int palindromeRecursive(char* _string, int _stringLength)
{
	int result = 1;
	if(_stringLength >= 2)
	{
		result = (*_string == _string[_stringLength - 1]);
		if(_stringLength > 2 && result == 1)
		{
			result = palindromeRecursive(_string + 1, _stringLength - 2);
		}
	}
	return result;
}



