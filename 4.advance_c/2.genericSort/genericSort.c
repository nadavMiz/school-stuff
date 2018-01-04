#include <stdlib.h>
#include <string.h>

#include "ADTErr.h"
#include "genericSort.h"

static void swapGeneric(void* _first, void* _second, void* _tmp, size_t _elemSize)
{
	memcpy(_tmp, _second, _elemSize);
	memcpy(_second, _first, _elemSize);
	memcpy(_first, _tmp, _elemSize);
}

ADTErr GenericBubbleSort(void* _data, size_t _arrLength, size_t _elemSize ,CompareFunc _compareFunc)
{
	size_t i, j;
	void* currentItem = NULL;
	void* prevItem = NULL;
	size_t arrBitesLength = _arrLength * _elemSize;
	int isSorted;
	void* tmpVal;
	
	/*errors checks*/
	if(NULL == _data || NULL == _compareFunc)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(0 == _elemSize)
	{
		return ERR_INVALID_INPUT;
	}
	
	/*set temporary value for swap*/
	tmpVal = malloc(_elemSize);
	if(NULL == tmpVal)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	/* sort the array */
	for(i = 0; i < arrBitesLength; i = i + _elemSize)
	{
		isSorted = 1;
		for(j = _elemSize; j < arrBitesLength - i; j = j + _elemSize)
		{
			prevItem = (void*)((char*)_data + (j - _elemSize));
			currentItem = (void*)((char*)_data + j);
			if(_compareFunc(prevItem , currentItem))
			{
				swapGeneric(prevItem, currentItem, tmpVal, _elemSize);
				isSorted = 0;
			}
		}
		if(isSorted)
		{
			break;
		}
	}
	free(tmpVal);
	return ERR_OK;
}

