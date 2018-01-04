#include <stdlib.h>
#include "alloc.h"
#define MEMORY_PULL 1024000

int* MemmoryInit()
{
	size_t i;
	int memmorySize = EMPTY_MEMMORY / sizeof(int);
	int* memmory = malloc(memmorySize);
	for(i = 0; i < memmorySize - 1; ++i)
	{
		memmory[i] = (int)&memmory[i+1];
	}
	head[memmorySize - 1] = 0;
	return memmory;
}

void MemmoryDestroy(int** _memmory)
{
	if(NULL != *_memmory)
	{
		free(**_memmory);
	}
	*_memmory = NULL;
}

int* Alloc(int* _memmory)
{
	if(0 == _memmory[0])
	{
		return NULL;
	}
	int* location = (int*)_memmory[0];
	_memmory[0] = location[0];
	return location;
}

void AllocFree(int* _adress, int* _memmory)
{
	_adress[0] = _memmory[0];
	_memmory[0] = (int)_adress;
}

int main()
{
	return 1;
}
