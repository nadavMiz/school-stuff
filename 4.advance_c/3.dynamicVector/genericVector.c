#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "ADTErr.h"
#include "/home/nadavmizrahi/Desktop/git/work/inc/genericVector.h"
#include "/home/nadavmizrahi/Desktop/git/work/inc/genericVector.h"

#define MAGIC_NUMBER 666666

struct Vector
{
    int 	m_magicNumber;    /* number to check if the vector was destroyed */
	void**  m_items;		  /* array of items */
	size_t  m_originalSize;   /* original allocated space for items) */
    size_t  m_size;           /* actual allocated space for items) */
    size_t  m_nItems;         /* actual number of items */
    size_t  m_blockSize;      /* the chunk size to be allocated when no space */
};

/*-----------------------static functions----------------------*/

static ADTErr increaseCapacity(Vector* _vector)
{
	void** new_numbers;
	/* increase the memmory */
	new_numbers = realloc((*_vector).m_items, ((*_vector).m_size + (*_vector).m_blockSize) * sizeof(void*));
	if(!new_numbers) 
	{
		return ERR_REALLOCATION_FAILED;
	}
	/* if the realocation was succesful increase the arrays capacity and set the new array pointer */
	(*_vector).m_items = new_numbers;
	(*_vector).m_size = (*_vector).m_size + (*_vector).m_blockSize;
	return ERR_OK;
}

static ADTErr decreaseCapacity(Vector* _vector)
{
	size_t newCapacity;
	void** new_numbers;
	newCapacity = _vector->m_size - _vector->m_blockSize;
	/* get the new block size */
	if(newCapacity < _vector->m_originalSize)
	{
		newCapacity = _vector->m_originalSize;
	}
	/* decrease the memmory */
	new_numbers = realloc(_vector->m_items, newCapacity * sizeof(void*));
	if(NULL == new_numbers) 
	{
		return ERR_REALLOCATION_FAILED;
	}
	/* if the realocation was succesful decrease the arrays capacity and set the new array pointer */
	_vector->m_items = new_numbers;
	_vector->m_size = newCapacity;
	return ERR_OK;
}

/*------------------------------main functions-------------------------------*/

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	void* array;
	Vector* dynamicVectorPointer;
	if (_initialSize == 0 && _extensionBblockSize == 0)
	{
		return NULL;
	}
	/*create the dynamic vector pointer */
	dynamicVectorPointer = malloc(sizeof(Vector));
	if(!dynamicVectorPointer) return NULL;

	/* create the DVs array */
	array = malloc(_initialSize * sizeof(void*));
	if(!array)
	{ 
		free(dynamicVectorPointer);
		return NULL;
	}

	/* set the DVs values */
	(*dynamicVectorPointer).m_originalSize = _initialSize;
	(*dynamicVectorPointer).m_size = _initialSize;
	(*dynamicVectorPointer).m_nItems = 0;
	(*dynamicVectorPointer).m_blockSize = _extensionBblockSize;
	(*dynamicVectorPointer).m_items = array;
	(*dynamicVectorPointer).m_magicNumber = MAGIC_NUMBER;
	
	return dynamicVectorPointer;
}

void VectorDestroy(Vector** _vector, UserInputFunc _destroyElemFunction)
{
	/* check parameters*/
	if(NULL == _vector || 0 == (*_vector)->m_magicNumber)
	{
		return;
	}
	
	(*_vector)->m_magicNumber = 0;
	
	VecForEach(*_vector, _destroyElemFunction, NULL);
	
	/* free the vectors memmory */
	free((*_vector)->m_items);
	free(*_vector);
	*_vector = NULL;
}

ADTErr VectorAdd(Vector *_vector, void*  _item)
{
	ADTErr error;
	if(NULL == _vector || 0 == _vector->m_magicNumber || NULL == _item)
	{
		return ERR_NOT_INITIALIZED;
	}
	/* if the array reached its maximum capicity realocate more space */
	if(_vector->m_nItems == _vector->m_size)
	{
		error = increaseCapacity(_vector);
		/*if the capacity increase did not work return the problem */
		if(ERR_OK != error)
		{
			return error;
		}
	}

	/* enter the element to the array. */
	_vector->m_items[_vector->m_nItems] = _item;
	++(_vector->m_nItems);
	return ERR_OK;
}

ADTErr VectorDelete(Vector *_vector,  void** _item){
	if(!_vector || !_vector->m_items || !_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (0 == _vector->m_nItems)
	{
		return ERR_UNDERFLOW;
	}
	(*_item) = _vector->m_items[_vector->m_nItems - 1];
	--(*_vector).m_nItems;
	/* check if need to reduce capacity */
	if((_vector->m_size - _vector->m_nItems) >  _vector->m_blockSize * 2 && _vector->m_blockSize != 0)
	{
		ADTErr decreaseSuccess = decreaseCapacity(_vector);
		if(ERR_OK != decreaseSuccess)
		{
			return decreaseSuccess;
		}
	}
	return ERR_OK;
}

ADTErr VectorGet(Vector *_vector, size_t _index, void**_dest)
{
	if(NULL == _vector || 0 == _vector->m_magicNumber)
	{
			return ERR_NOT_INITIALIZED;
	}
	if(_index > _vector->m_nItems - 1)
	{
		return ERR_OVERFLOW;
	}
	
	(*_dest) = _vector->m_items[_index];
	return ERR_OK;
}

ADTErr VectorSet(Vector *_vector, size_t _index, void*  _item)
{
	if(!_vector || !_vector->m_items)
		{
			return ERR_NOT_INITIALIZED;
		}
	if(_index > _vector->m_nItems - 1)
	{
		return ERR_OVERFLOW;
	}
	
	_vector->m_items[_index] = _item;
	return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems)
{
	if(!_vector || !_numOfItems)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	(*_numOfItems) = _vector->m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector *_vector, UserInputFunc _printFunc)
{
	printf("the vectors elements are: ");
	VecForEach(_vector, _printFunc, NULL);
	printf("\n");
}

int VecForEach(Vector* _vec, UserInputFunc _userFunc, void* _input)
{
	size_t i;
	if(NULL == _vec || NULL == _userFunc)
	{
		return 0;
	}
	for(i = 0; i < _vec->m_nItems; ++i)
	{
		if(0 == _userFunc (_vec->m_items[i], _input))
		{
			return 0;
		}
	}
	return 1;
}

