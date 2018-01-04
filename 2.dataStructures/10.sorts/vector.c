#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "vector.h"
#include "ADTErr.h"
/********************************** helper functions ************************/
ADTErr increaseCapacity(Vector* _vector)
{
	int* new_numbers;
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(0 == (*_vector).m_blockSize)
	{
		return ERR_OVERFLOW;
	}
	/* increase the memmory */
	new_numbers = realloc((*_vector).m_items, ((*_vector).m_size + (*_vector).m_blockSize) * sizeof(int));
	if(!new_numbers) {
		return ERR_REALLOCATION_FAILED;
	}
	/* if the realocation was succesful increase the arrays capacity and set the new array pointer */
	(*_vector).m_items = new_numbers;
	(*_vector).m_size = (*_vector).m_size + (*_vector).m_blockSize;
	return ERR_OK;
}

ADTErr decreaseCapacity(Vector* _vector)
{
	int newCapacity;
	int* new_numbers;
	if(!_vector)
	{
		return ERR_NOT_INITIALIZED;
	}
	newCapacity = (*_vector).m_size - (*_vector).m_blockSize;
	/* get the new block size */
	if(newCapacity < (*_vector).m_originalSize)
	{
		newCapacity = (*_vector).m_originalSize;
	}
	/* decrease the memmory */
	new_numbers = realloc((*_vector).m_items, newCapacity * sizeof(int));
	if(!new_numbers) {
		return ERR_REALLOCATION_FAILED;
	}
	/* if the realocation was succesful decrease the arrays capacity and set the new array pointer */
	(*_vector).m_items = new_numbers;
	(*_vector).m_size = newCapacity;
	return ERR_OK;
}

/****************************main functions********************************/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	int* array;
	Vector* dynamicVectorPointer;
	if (_initialSize < 0 && _extensionBblockSize < 0)
	{
		return NULL;
	}
	/*create the dynamic vector pointer */
	dynamicVectorPointer = malloc(sizeof(Vector));
	if(!dynamicVectorPointer) return NULL;

	/* create the DVs array */
	array = malloc(_initialSize * sizeof(int));
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
	
	return dynamicVectorPointer;
}

void VectorDestroy(Vector* _vector)
{
	if(!_vector || !(*_vector).m_items)
	{
		return;
	}
	(*_vector).m_items = NULL;
	free((*_vector).m_items);
	free(_vector);
}

ADTErr VectorAdd(Vector *_vector,  int  _item)
{
	if(!_vector || !(*_vector).m_items)
	{
		return ERR_NOT_INITIALIZED;
	}
	/* if the array reached its maximum capicity realocate more space */
	if((*_vector).m_nItems == (*_vector).m_size)
	{
		ADTErr increaseSuccess = increaseCapacity(_vector);
		/*if the capacity increase did not work return the problem */
		if(ERR_OK != increaseSuccess)
		{
			return increaseSuccess;
		}
	}

	/* enter the element to the array. */
	(*_vector).m_items[(*_vector).m_nItems] = _item;
	++((*_vector).m_nItems);
	return ERR_OK;
}

ADTErr VectorDelete(Vector *_vector,  int* _item){
	if(!_vector || !(*_vector).m_items || !_item)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (0 == (*_vector).m_nItems)
	{
		return ERR_UNDERFLOW;
	}
	(*_item) = (*_vector).m_items[(*_vector).m_nItems - 1];
	--(*_vector).m_nItems;
	/* check if need to reduce capacity */
	if(((*_vector).m_size - (*_vector).m_nItems) >  (*_vector).m_blockSize * 2 && (*_vector).m_blockSize != 0)
	{
		ADTErr decreaseSuccess = decreaseCapacity(_vector);
		if(ERR_OK != decreaseSuccess)
		{
			return decreaseSuccess;
		}
	}
	return ERR_OK;
}

ADTErr VectorGet(Vector *_vector, size_t _index, int *_dest)
{
	if(!_vector || !_dest || !(*_vector).m_items)
	{
			return ERR_NOT_INITIALIZED;
	}
	if(_index < 1)
	{
		return ERR_UNDERFLOW;
	}
	if(_index > (*_vector).m_nItems)
	{
		return ERR_OVERFLOW;
	}
	(*_dest) = (*_vector).m_items[_index - 1];
	return ERR_OK;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int  _item)
{
	if(!_vector || !(*_vector).m_items)
		{
			return ERR_NOT_INITIALIZED;
		}
	if(_index > (*_vector).m_nItems)
	{
		return ERR_OVERFLOW;
	}
	if(_index < 1)
	{
		return ERR_UNDERFLOW;
	}
	(*_vector).m_items[_index - 1] = _item;
	return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, size_t*  _numOfItems)
{
	if(!_vector || !_numOfItems)
	{
		return ERR_NOT_INITIALIZED;
	}
	(*_numOfItems) = (*_vector).m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector *_vector)
{
	int i;
	printf("the vectors elements are: ");
	for (i = 0; i < (*_vector).m_nItems; ++i)
		{
			printf("%d ", (*_vector).m_items[i]);
		}
		printf("\n");
}

