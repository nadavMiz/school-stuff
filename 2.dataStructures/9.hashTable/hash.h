#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>
#include "ADTErr.h"


typedef struct Hash Hash;

/*
create a new instence of Hash struct
input 
	_size: the capacity of the hash
return:
	pointer to the new hash
	NULL if there was an allocation error.
*/
Hash* HashCreate(size_t _size);

/*
safely destroy an instence of a hash struct
input:
	_hash the hash to destroy.
*/
void HashDestroy(Hash* _hash);

/*
insert a new data to the hash set
input:
	_hash: the hash to enter the element to
	_data: the data to enter to the set
return:
	ERR_OK: element was inserted successfully
	ERR_NOT_INITIALIZED: the hash was not initialized.
	ERR_INVALID_INPUT: data was less or equal to 0
	ERR_OVERFLOW: the hash is full.
	ERR_ELEM_ALREADY_EXISTS: the element aready existed in the hash set.
*/
ADTErr HashInsert(Hash* _hash, int _data);

/*
remove an element from a hash set
input:
	_hash: the set to remove the element from.
	_data: the data to remove from the set.
return:
	ERR_OK: item was removed successfully
	ERR_NOT_INITIALIZED: the hash set was not initiallized.
	ERR_ELEM_NOT_EXISTS: the element was not present in the set.
*/
ADTErr HashRemove(Hash* _hash, int _data);

/*
boolean function that checks if element is in a hash set.
input:
	_hash: the set to search the element in.
	_data: the element to search.
return:
	1: the item is in the set
	0: the item was NOT int the set, or the set was not initialized.
*/
int HashIsFound(const Hash* _hash, int _data);

/*
get the number of items in a hash set.
input:
	_hash: the hash to get the number of elements from.
return:
	number of elements in _hash.
	0 if _hash was not initialized.
*/
size_t HashNumOfItems(const Hash* _hash);

/*
get the capacity of a hash set
input:
	_hash: the set to get the capacity from.
return:
	the capacity of _hash.
	0 if hash was not initialized.
*/
size_t HashCapacity(const Hash* _hash);

/*
get the average collisions in a hash set
input:
	_hash: the set to get the average collisions from.
return:
	the average collisions in _hash(total collisions / number of elements)
*/
double HashAverageCollisions(const Hash* _hash);

/*
get the largest number of collisions in a single index of a hash set.
input:
	_hash: the set to get the max collitions from.
return:
	the largest number of collisions in a single index of a hash set.(the max collisions)
*/
size_t HashMaxCollisions(const Hash* _hash);

/*
prints a hash set to the screen.
input:
	_hash: the set to print
*/    
void HashPrint(const Hash* _hash);
    
#endif /* ifndef __HASH_H__ */
