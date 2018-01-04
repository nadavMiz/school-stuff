#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stddef.h>  /* size_t */

/** 
 *  @file HashMap.h
 *  @brief Generic Hash map of key-value pairs implemented with separate chaining using linked lists.
 *	
 *  @details  The hash map (sometimes called dictionary or associative array)
 *  is a set of distinct keys (or indexes) mapped (or associated) to values.
 *  size of allocated table will be the nearest prime number greater than requested capacity.
 *  Lists used for chaining will be allocated eagerly.
 *
 *  @author Nadav Mizrahi  (MuhammadZ@experis.co.il)
 * 
 *  @bug No known bugs! 
 */


typedef struct HashMap HashMap;

typedef enum MapResult {
	MAP_SUCCESS = 0,
	MAP_UNINITIALIZED_ERROR, 		/**< Uninitialized map error 	*/
	MAP_ALLOCATION_ERROR, 			/**< Allocation error 	 		*/
	MAP_KEY_NULL_ERROR, 			/**< Key was null 				*/
	MAP_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	MAP_KEY_NOT_FOUND_ERROR,		/**< Key not found 				*/
	MAP_MUTEX_ERROR
} MapResult;


typedef size_t (*HashFunction)(const void* _key);
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef int	(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);


/** 
 * @brief Create a new hash map with given capcity and key characteristics.
 * @param[in] _capacity - Expected max capacity 
 * 						  actuall capacity will be equal to nearest larger prime number.
 * @param[in] _hashFunc - hashing function for keys
 * @param[in] _keysEqualFunc - equality check function for keys. 
 * @return newly created map or null on failure
 */
HashMap* HashMapCreate(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);


/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMapDestroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));


/** 
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
MapResult HashMapRehash(HashMap *_map, size_t newCapacity);


/** 
 * @brief Insert a key-value pair into the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapInsert(HashMap* _map, const void* _key, const void* _value);


/** 
 * @brief Remove a key-value pair from the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapRemove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue);


/** 
 * @brief Find a value by key
 * complexty(?)
 * @param[in] _map - Hash map to use, must be initialized
 * @param[in] _searchKey - key to serve as index for search
 * @param[out] _pValue - pointer to variable that will get the value assoiciated with the search key.
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
MapResult HashMapFind(const HashMap* _map, const void* _searchKey, void** _pValue);


/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 */
size_t HashMapSize(const HashMap* _map);


/** 
 * This method is optional in the homework 
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.  
 * Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HashMapForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context);

int HashMapMerge(const HashMap* _map, const void* _key, void* _value, KeyValueActionFunction _mergeFunc, void* _context);

int HashMapActionByKey(const HashMap* _map, const void* _key, KeyValueActionFunction _action, void* _context);

#ifndef NDEBUG

typedef struct MapStats {
    size_t m_pairs;               /* number of pairs stored */
	size_t m_collisions;          /* total number of collisions encountered */
	size_t m_buckets;             /* total number of buckets */
	size_t m_chains;              /* none empty buckets (having non zero length list) */
	size_t m_maxChainLength;      /* length of longest chain */
	size_t m_averageChainLength;  /* average length of none empty chains */
} MapStats;

MapStats* HashMapGetStatistics(const HashMap* _map);

#endif /* NDEBUG */


#endif /* __HASHMAP_H__ */
