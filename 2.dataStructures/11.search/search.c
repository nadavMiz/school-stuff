#include <math.h>
#include <stddef.h>
#include "search.h"

/*--------------static functions----------------*/

static void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
returns the index to swap the searched value for the adapted linear search.
returns index proportionaly to the arrays length
*/
static size_t getSwapIdx( size_t _toSwapIdx , size_t _arrayLength)
{
	size_t targetIdx = _toSwapIdx - _arrayLength /10;
	return (targetIdx < _arrayLength) ? targetIdx : 0;
}

/* returns the index of the proportipnal position between the searched element and the segment between start and and
so that if start value = 20, end value = 30, search = 37 the return index will be the 0.7 index between end and start 
(proportion * length + start)*/
static size_t getProportionalIdx(int* _array, size_t _start, size_t _end, int search)
{
	if(_array[_end] == _array[_start])
	{
		return (_end + _start) / 2;
	}
	return ((search - _array[_start]) / (_array[_end] - _array[_start])) * (_end - _start) + _start;
}

/*---------------main functions-----------------*/

int LinearSearch(int* _array, size_t _arrayLength, int _search)
{
	size_t i;
	for(i = 0; i < _arrayLength; ++i)
	{
		if(_search == _array[i])
		{
			return 1;
		}
	}
	return 0;
}

/*-----------------------------*/

int ModifiedLinearSearch(int* _array, size_t _arrayLength, int _search)
{
	size_t i = 0;
	size_t swapIdx;
	_array[_arrayLength] = _search;
	/* find the item */
	while(1)
	{
		if(_search == _array[i])
		{
			break;
		}
		++i;
	}
	/* if the item was found move it bakwards*/
	if(i < _arrayLength)
	{
		swapIdx = getSwapIdx(i, _arrayLength);
		swap(&_array[i], &_array[swapIdx]);
		return 1;
	}
	return 0;
}

/*-------------------------------*/

int ProportionalSearch(int* _array, size_t _arrayLength, int _search)
{
	size_t middle;
	size_t start = 0;
	size_t end = _arrayLength - 1;
	if(_search < _array[0] || _search > _array[_arrayLength - 1])
	{
		return 0;
	}
	
	/*check the first item in case there is only one item*/
	if(_search == _array[0])
	{
		return 1;
	}
	
	/* search for the item in the array according to its proprtional location in the segment
	   exit when the segmant is the length of one (the last or first element is always checked in the previous iteration)*/
	while(end - start > 0)
	{
		middle = getProportionalIdx(_array, start, end, _search);
		if( _search == _array[middle])
		{
			return 1;
		}
		else if(_search < _array[middle])
		{
			end = middle;
		}
		else
		{
			start = middle + 1;
		}
	}
	return 0;
}

/*-------------------------------------*/

int JumpSearch(int* _array, size_t _arrayLength, int _search)
{
	size_t i;
	size_t start = 0;
	size_t jump = _arrayLength;
	size_t end = _arrayLength;
	
	/* check that the value is not out of bounds */
	if(_search < _array[0] || _search > _array[_arrayLength - 1] || 0 == _arrayLength)
	{
		return 0;
	}
	
	do /*while (jump > 1)*/
	{
		/*after every iteration the size of the new array is the size of the previous jump. so the new jump is the sqrt of jump*/
		jump = (int)sqrt((double)jump);
		for(i = start; i < end ;i += jump)
		{
			if(_search == _array[i])
			{
				return 1;
			}
			if(_search < _array[i])
			{
				break;
			}
		}
		start = i - jump;
		end = (i < end) ? i: end;
		
	} while (jump > 1);
	
	return 0;
}


