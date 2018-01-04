#include <stdlib.h>
#include <math.h>

#include "HashMap.h"
#include "doubleLinkedList.h"
#include "ListIteratorFuncs.h"

#define MAGIC_NUMBER 0X555555
#define IS_HASH_MAP(H) ((NULL != (H)) && (MAGIC_NUMBER == (H)->m_magicNumber))

typedef List* Bucket

struct HashMap
{
	size_t m_magicNumber;
	Bucket* m_buckets;
	size_t m_capacity;
	HashFunction m_hashf;
	EqualityFunction m_equalf;
	#ifndef NDEBUG
	size_t m_collitions;
	#endif /*NDEBUG*/
};

typedef struct
{
	void* m_key;
	void* m_value;
} Pair;

typedef void (*DestroyFunc) (void* _key);

typedef struct 
{
	KeyValueActionFunction m_KeyValueFunc;
	void* m_context;
} WraperAction;

typedef struct
{
	EqualityFunction m_equalf;
	void* m_context;
} WraperSearch;

/*------------------static function---------------------*/

static int FreePair(void* _pair, void* _context)
{
	free(_pair);
	return 1;
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
	while(!isPrime(_size))
	{
		++_size;
	}
	return _size;
}

/*-----------------------------------------*/

static Pair* CreatePair(const void* _key, const void* _value)
{
	Pair* pair;
	
	pair = malloc(sizeof(Pair));
	if(NULL == pair)
	{
		return NULL;
	}
	pair->m_key = (void*)_key;
	pair->m_value = (void*)_value;
	
	return pair;
}

/*-------------------------------------------------------*/

static int PredicateKeyWraper(Pair* _pair, WraperSearch* _wraperSearch)
{
	return _wraperSearch->m_equalf(_pair->m_key, _wraperSearch->m_context);
}

ListItr GetListItrByKey(const HashMap* _map, const void* _searchKey)
{
	WraperSearch _wraperSearch;
	size_t index;
	ListItr begin, end, target;
	
	/*build the context struct to insert to the wraper function*/
	_wraperSearch.m_equalf = _map->m_equalf;
	_wraperSearch.m_context = (void*)_searchKey;
	
	index = _map->m_hashf(_searchKey) % _map->m_capacity;
	
	/* find the item in the Bucket*/
	begin = ListItr_Begin(_map->m_buckets[index]);
	end = ListItr_End(_map->m_buckets[index]);
	target = ListItrFindFirst(begin, end, (PredicateFunc)PredicateKeyWraper, &_wraperSearch);
	
	return target;
}

Pair* GetPairBykey(const HashMap* _map, const void* _searchKey)
{
	ListItr targetItr;
	
	targetItr = GetListItrByKey(_map, _searchKey);
	return ListItr_Get(targetItr);
}

/*---------------------main hash functions------------------------------*/
static int WraperActionFunction(Pair* _pair, WraperAction* _wraperAction)
{
	return _wraperAction->m_KeyValueFunc(_pair->m_key, _pair->m_value, _wraperAction->m_context);
}

size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t i;
	size_t count = 0;
	WraperAction actionStruct;
	
	if(!IS_HASH_MAP(_map) || NULL == _action)
	{
		return 0;
	}
	
	actionStruct.m_KeyValueFunc = _action;
	actionStruct.m_context = _context;
	
	for(i = 0; i < _map->m_capacity; ++i)
	{
		count += ListForEach(_map->m_buckets[i], (UserActionFunc)WraperActionFunction, (void*)(&actionStruct));
	}
	return count;
}

/*------------------------------------------------------------------------*/

static void DestroyBuckets(Bucket* _buckets, size_t _bucketsLength)
{
	size_t i;
	
	for(i = 0; i < _bucketsLength; ++i)
	{	
		ListDestroy(&(_buckets[i]), FreePair);
	}
	free(_buckets);
}


static Bucket* CreateBuckets(size_t _capacity)
{
	size_t i;
	Bucket* buckets;
	
	buckets = malloc(_capacity * sizeof(Bucket));
	if(NULL == buckets)
	{
		return NULL;
	}
	
	for(i = 0; i < _capacity; ++i)
	{
		buckets[i] = ListCreate();
		if(NULL == buckets[i])
		{
			DestroyBuckets(buckets, i);
			return NULL;
		}
	}
	return buckets;
}

HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hashMap;
	if(0 == _capacity)
	{
		return NULL;
	}
	
	hashMap = malloc(sizeof(HashMap));
	if(NULL == hashMap)
	{
		return NULL;
	}
	
	hashMap->m_capacity = getHashCapacity(_capacity);
	
	hashMap->m_buckets = CreateBuckets(_capacity);
	if(NULL == hashMap->m_buckets)
	{
		return NULL;
	}
	
	hashMap->m_magicNumber = MAGIC_NUMBER;
	hashMap->m_hashf = _hashFunc;
	hashMap->m_equalf = _keysEqualFunc;
	
	return hashMap;
}

/*-------------------------------------------*/
static void VoidDestroyFunc(void* _value)
{
	return;
}

static void DestroyPair(Pair* _pair, DestroyFunc _destroyKey, DestroyFunc _destroyValue)
{
	_destroyKey(_pair->m_key);
	_destroyValue(_pair->m_value);
	free(_pair);
}

static void DestroyBucket(Bucket _bucket, DestroyFunc _destroyKey, DestroyFunc _destroyValue)
{
	Pair* pair;
	while(LIST_IS_EMPTY != ListPopHead(_bucket, (void**)(&pair)))
	{
		DestroyPair(pair, _destroyKey, _destroyValue);
	}
	ListDestroy(&_bucket, FreePair);
}

static void DestroyAllBuckets(HashMap* _map, DestroyFunc _destroyKey, DestroyFunc _destroyValue)
{
	size_t i;
	for(i = 0; i < _map->m_capacity; ++i)
	{
		DestroyBucket(_map->m_buckets[i], _destroyKey, _destroyValue);
	}
}

void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(NULL == _map || !IS_HASH_MAP(*_map))
	{
		return;
	}
	if(NULL == _keyDestroy)
	{
		_keyDestroy = VoidDestroyFunc;
	}
	if(NULL == _valDestroy)
	{
		_valDestroy = VoidDestroyFunc;
	}
	DestroyAllBuckets(*_map, _keyDestroy, _valDestroy);
	(*_map)->m_magicNumber = 0;
	free((*_map));
	*_map = NULL;
}

/*-----------------------------------------------------------------------------*/

MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value)
{
	Pair* pair;
	ListErrors error;
	size_t index;
	
	if(!IS_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _key)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	pair = GetPairBykey(_map, _key);
	if(NULL != pair)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	pair = CreatePair(_key, _value);
	if(NULL == pair)
	{
		return MAP_ALLOCATION_ERROR;
	}

	index = (_map->m_hashf(_key) % _map->m_capacity);
	error = ListPushHead(_map->m_buckets[index], pair);
	
	#ifndef NDEBUG
	if(1 < ListCountItems(_map->m_buckets[index]))
	{
		++_map->m_collisions;
	}
	#endif /*NDEBUG*/
	return error;
}

/*---------------------------------------------------------------------------------*/

MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	Pair* targetPair;
	
	if(!IS_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	targetPair = GetPairBykey(_map, _searchKey);
	
	if(NULL == targetPair)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	*_pValue = targetPair->m_value;
	return MAP_SUCCESS;
}

/*----------------------------------------------------------------------------------*/

MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr targetListItr;
	Pair* targetPair;
	
	if(!IS_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	targetListItr = GetListItrByKey(_map, _searchKey);
	targetPair = ListItr_Remove(targetListItr);
	
	if(NULL == targetPair)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	*_pKey = targetPair->m_key;
	*_pValue = targetPair->m_value;
	
	free(targetPair);
	
	return MAP_SUCCESS;
}

/*-------------------------------------------------------------------------------------*/

/* rehash all the items in the hash map and move them to new buckets*/
static void RehashToNewBuckets(HashMap* _map, Bucket* _dest, size_t _destSize)
{
	size_t i, newIndex;
	ListItr current, end, next;
	Pair* pair;
	
	for(i = 0; i < _map->m_capacity; ++i)
	{
		current = ListItr_Begin(_map->m_buckets[i]);
		end = ListItr_End(_map->m_buckets[i]);
		
		while(!ListItr_Equals(current, end))
		{
			next = ListItr_Next(current);
			pair = ListItr_Get(current);
			
			newIndex = _map->m_hashf(pair->m_key) % _destSize;
			
			ListItr_Splice(ListItr_Begin(_dest[newIndex]), current, next);
			
			current = next;
		}
	}
	
	DestroyAllBuckets(_map, VoidDestroyFunc, VoidDestroyFunc);
	_map->m_buckets = _dest;
}

MapResult HashMapRehash(HashMap *_map, size_t _newCapacity)
{
	Bucket* newBuckets;
	
	if(!IS_HASH_MAP(_map))
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(_map->m_capacity == _newCapacity)
	{
		return MAP_SUCCESS;
	}
	if(0 == _newCapacity)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	newBuckets = CreateBuckets(_newCapacity);
	if(NULL == newBuckets)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	_newCapacity = getHashCapacity(_newCapacity);
	RehashToNewBuckets(_map, newBuckets, _newCapacity);
	_map->m_capacity = _newCapacity;
	return MAP_SUCCESS;
}

/*-------------------------------------------------*/

static int countActionFunction(const void* _dummy1, void* _dummy2, void* _context)
{
	return 1;
}

size_t HashMapSize(const HashMap* _map)
{
	if(!IS_HASH_MAP(_map))
	{
		return 0;
	}
	return HashMapForEach(_map, countActionFunction, NULL);
}

/*-----------------------------------------------------*/

#ifndef NDEBUG

MapStats* HashMapGetStatistics(const HashMap* _map)
{
	size_t i, bucketSize, sumChains;
	size_t longestChain = 0;
	MapStats* stats = calloc(1, sizeof(MapStats));
	
	stats->m_pairs = HashMapSize(_map);
	stats->m_buckets = _map->m_capacity;
	stats->m_collisions = _map->m_collisions;
	
	for(i = 0; i < _map->m_capacity; ++i)
	{
		bucketSize = ListCountItems(_map->m_buckets[i]);
		/*all statistics require the bucket to have at least one item*/
		if(0 != bucketSize)
		{
			++stats->m_chains;
			
			sumChains += bucketSize;
			
			if(longestChain < bucketSize)
			{
				longestChain = bucketSize;
			}
		}
	}
	stats->m_maxChainLength = longestChain;
	stats->m_averageChainLength = sumChains / stats->m_buckets;
	
	return stats;
}
#endif /* NDEBUG */
