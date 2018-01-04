#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "hash.h"
#include "ADTErr.h"

#define MAGIC_NUMBER 666666

struct Hash
{
    int* m_data;
	
    /*original size given by the client*/
    size_t m_originalSize;
    
    /*real array size*/
    size_t m_hashSize;
    
    /*maximum number of collisions*/
    size_t m_maxCollisions;
    
    /*total insertions count*/
    size_t m_numberOfInsertions;
    
    /*total collisions until now*/
    size_t m_totalCollisions;
    
    size_t magicNumber;
};

/*-----------------static functions---------------------*/
static int isHashInitialized(const Hash* _hash)
{
	return (NULL != _hash && MAGIC_NUMBER == _hash->magicNumber);
}

/*----------------------------------*/
static int isPrime(size_t _checkNum){
	size_t number;
	double numSqrt;
	if(_checkNum % 2 == 0 || 1 == _checkNum)
	{
		return 1;
	}
	numSqrt =  sqrt(_checkNum);
	for(number = 3; number <= numSqrt; number = number + 2){
		if(_checkNum % number == 0)
		{
			return 0;
		}
	}
	return 1;
}

/*----------------------------------*/
static size_t getHashCapacity(size_t _size)
{
	size_t newCapacity;
	newCapacity = (size_t)(_size * 1.3);
	while(!isPrime(newCapacity))
	{
		++newCapacity;
	}
	return newCapacity;
}

static size_t HashData(const Hash* _hash, int _originalNum)
{
	return (size_t)(_originalNum % (int)_hash->m_hashSize);
}

static size_t NextIdx(const Hash* _hash, size_t _currentIdx)
{
	return (_currentIdx + 1) % _hash->m_hashSize;
}

static int isEmptySlot(const Hash* _hash, size_t _location)
{
	return (0 == _hash->m_data[_location] || -1 == _hash->m_data[_location]);
}

/*
return 1 if _data is in the hash 0 if it in't
*/
static int isFound(const Hash* _hash, int _data, size_t* _location)
{
	size_t itemIndex;
	int i;
	itemIndex = HashData(_hash, _data);
	for(i = 0; i <= _hash->m_maxCollisions; ++i)
	{
		if(_data == _hash->m_data[itemIndex])
		{
			*_location = itemIndex;
			return 1;
		}
		if(0 == _hash->m_data[itemIndex])
		{
			break;
		}
		itemIndex = NextIdx(_hash, itemIndex);
	}
	return 0;
}

static size_t getNextLocation(Hash* _hash, int _data)
{
	size_t itemIndex;
	size_t numCollisions = 0;
	
	itemIndex = HashData(_hash, _data);
	if(!isEmptySlot(_hash, itemIndex))
	{
		++_hash->m_totalCollisions;
		while(!isEmptySlot(_hash, itemIndex))
		{
			itemIndex = NextIdx(_hash, itemIndex);
			++numCollisions;
		}
		if(numCollisions > _hash->m_maxCollisions)
		{
			_hash->m_maxCollisions = numCollisions;
		}
	}
	return itemIndex;
}

/*------------------main functions----------------------*/

Hash* HashCreate(const size_t _size)
{
	Hash* newHash;
	size_t capacity;
	newHash = calloc(1, sizeof(Hash));
	if(NULL == newHash)
	{
		return NULL;
	}
	capacity = getHashCapacity(_size);
	newHash->m_data = calloc(capacity, sizeof(int));
	if(NULL == newHash->m_data)
	{
		free(newHash);
		return NULL;
	}
	newHash->magicNumber = MAGIC_NUMBER;
	newHash->m_originalSize = _size;
	newHash->m_hashSize = capacity;
	return newHash;
}

/*--------------------------------------*/
void HashDestroy(Hash* _hash)
{
	if(!isHashInitialized(_hash))
	{
		return;
	}
	_hash->magicNumber = 0;
	free(_hash->m_data);
	free(_hash);
}

/*---------------------------------------*/

ADTErr HashInsert(Hash* _hash, int _data)
{
	size_t itemIndex;
	if(!isHashInitialized(_hash))
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_data <= 0)
	{
		return ERR_INVALID_INPUT;
	}
	if(_hash->m_numberOfInsertions == _hash->m_originalSize)
	{
		return ERR_OVERFLOW;
	}
	if(isFound(_hash, _data, &itemIndex))
	{
		return ERR_ELEM_ALREADY_EXISTS;
	}
	
	itemIndex = getNextLocation(_hash, _data);
	_hash->m_data[itemIndex] = _data;
	++_hash->m_numberOfInsertions;
	return ERR_OK;
}

/*------------------------------------------------*/

ADTErr HashRemove(Hash* _hash, int _data)
{
	size_t location;
	if(!isHashInitialized(_hash))
	{
		return ERR_NOT_INITIALIZED;
	}
	if(isFound(_hash, _data, &location))
	{
		_hash->m_data[location] = -1;
		--_hash->m_numberOfInsertions;
		return ERR_OK;
	}
	return ERR_ELEM_NOT_EXISTS;
	
}

/*-----------------------------------------------*/

int HashIsFound(const Hash* _hash, int _data)
{
	size_t location;
	if(!isHashInitialized(_hash))
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_data <= 0)
	{
		return ERR_INVALID_INPUT;
	}
	return isFound(_hash, _data, &location);
}

/*-------------------------------------------------*/

size_t HashNumOfItems(const Hash* _hash)
{
	if(!isHashInitialized(_hash))
	{
		return 0;
	}
	return _hash->m_numberOfInsertions;
}

/*---------------------------------------------------*/

size_t HashCapacity(const Hash* _hash)
{
	if(!isHashInitialized(_hash))
	{
		return 0;
	}
	return _hash->m_originalSize;
}

/*-----------------------------------------------------*/

double HashAverageCollisions(const Hash* _hash)
{
	if(!isHashInitialized(_hash))
	{
		return 0;
	}
	return (double)_hash->m_totalCollisions / (double)_hash->m_numberOfInsertions;
}

/*-----------------------------------------------------*/

size_t HashMaxCollisions(const Hash* _hash)
{
	if(!isHashInitialized(_hash))
	{
		return 0;
	}
	return _hash->m_maxCollisions;
}

/*------------------------------------------------------*/

void HashPrint(const Hash* _hash)
{
	int i;
	for(i = 0; i < _hash->m_hashSize; ++i)
	{
		printf("%d ", _hash->m_data[i]);
	}
	printf("\n");
}

