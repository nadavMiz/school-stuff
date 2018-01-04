#include "input.h"
#include <ctype.h>
#include <stdio.h>

int IsName(char* _string)
{
	int i = 1;
	if(NULL == _string || !isupper(_string[0]))
	{
		return 0;
	}
	while(1)
	{
		if(_string[i] == '\0')
		{
			break;
		}
		if(!islower(_string[i]))
		{
			return 0;
		}
		++i;
	}
	return 1;
}

int IsAge(char* _string)
{
	int result = 1;
	int i = 0;
	if(NULL == _string)
	{
		return 0;
	}
	while(1)
	{
		if(_string[i] == '\0')
		{
			break;
		}
		if(!isdigit(_string[i]))
		{
			result = 0;
			break;
		}
		++i;
	}
	return result;
}


int CheckInput(char* _name, char* age_)
{
	if(IsName(_name) && IsAge(age_))
	{
		return 1;
	}
	return 0;
}
