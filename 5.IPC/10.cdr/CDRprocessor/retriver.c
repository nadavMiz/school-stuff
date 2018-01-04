#include <string.h>
#include <stdlib.h>

#include "retriver.h"
#include "HashMap.h"

void FreeFunc(void* _key)
{
	free(_key);
}

/*----------------------------------------------*/

Retriver* RetriverCreate(size_t _capacity, size_t(*_hashFunc)(const void* _key),
						 int (*_EqualityFunck)(const void* _a, const void* _b))
{
	return HashMapCreate(_capacity, _hashFunc, _EqualityFunck);
}

/*----------------------------------------------*/

void RetriverDestroy(Retriver** _retriver, void (*_valDestroy)(void* _value))
{
	HashMapDestroy(_retriver, FreeFunc, _valDestroy);
}

/*------------------------------------------------*/

RetriverResult RetriverFind(const Retriver* _retriver, const void* _key, void** _data)
{
	return HashMapFind(_retriver, _key, _data);
}

/*-----------------------------------------------*/

RetriverResult RetriverInsert(Retriver* _retriver, const void* _key, const void* _data)
{
	return HashMapInsert(_retriver, _key, _data);
}

/*-----------------------------------------------------*/

int RetriverMerge(Retriver* _retriver, const void* _key, void* _value, KeyValueActionFunction _mergeFunc, void* _context)
{
	return HashMapMerge(_retriver, _key, _value, _mergeFunc, _context);
}

/*-----------------------------------------------*/

size_t RetriverForEach(const Retriver* _retriver, ActionFunction _action, void* _context)
{
	return HashMapForEach(_retriver, _action, _context);
}

/*-----------------------------------------------*/

int RetriverActionByKey(const Retriver* _retriver, const void* _key, ActionFunction _action, void* _context)
{
	return HashMapActionByKey(_retriver, _key, _action, _context);
}
