#ifndef __RETRIVER_H__
#define __RETRIVER_H__

#include "HashMap.h"

typedef HashMap Retriver;

typedef size_t* RetriverItr;

typedef int (*ActionFunction)(const void* _key, void* _value, void* _context);

typedef enum RetriverResult {
	RETRIVER_SUCCESS = 0,
	RETRIVER_UNINITIALIZED_ERROR, 		/**< Uninitialized map error 	*/
	RETRIVER_ALLOCATION_ERROR, 			/**< Allocation error 	 		*/
	RETRIVER_KEY_NULL_ERROR, 			/**< Key was null 				*/
	RETRIVER_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	RETRIVER_KEY_NOT_FOUND_ERROR 		/**< Key not found 				*/
} RetriverResult;

/*---------------main retriver functions---------------------*/

/**
 * @brief: creates a new retriver
 * @param[in] _capacity: number of elements for the retriver to hold
 * @return pointer to a new retriver
 */
Retriver* RetriverCreate(size_t _capacity, size_t(*_hashFunc)(const void* _key),
						 int (*_EqualityFunck)(const void* _a, const void* _b));

/**
 * @brief: destroys a retriver
 * @param[in] retriver to destroy
 * @return void
 */
void RetriverDestroy(Retriver** _retriver, void (*_valDestroy)(void* _value));

/**
 * @brief: get data from the retriver by key
 * @param[in] _retriver - retriver to get data from
 * @param[in] _key: id of the item to get data of (MSISDN for subscriber, MCC/MNC for operator)
 * @param[out] pointer to store the data in
 *
 * @return OK on sucess ERRORR on failure
 * @retval  RETRIVER_OK - success
 * @retval  RETRIVER_KEY_DUPLICATE_ERROR - if key alread present in the map
 * @retval  RETRIVER_SUCCESS	on success
 * @retval  RETRIVER_KEY_NULL_ERROR
 * @retval  RETRIVER_KEY_NOT_FOUND_ERROR if key not found
 * @retval  RETRIVER_UNINITIALIZED_ERROR
 */
RetriverResult RetriverFind(const Retriver* _retriver, const void* _key, void** _data);

/**
 * @brief insert a new item to the retriver
 * @param[in] _retriver - retriver to insert data to
 * @param[in] _key - key of the data to insert.
 * @param[in] _data - data to insert
 *
 * @return OK on sucess ERRORR on failure
 * @retval RETRIVER_KEY_DUPLICATE_ERROR - if key alread present in the map
 * @retval RETRIVER_KEY_NULL_ERROR
 * @retval RETRIVER_ALLOCATION_ERROR on failer to allocate key-value pair
 * @retval RETRIVER_UNINITIALIZED_ERROR
 */
RetriverResult RetriverInsert(Retriver* _retriver, const void* _key, const void* _data);

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
size_t RetriverForEach(const Retriver* _retriver, ActionFunction _action, void* _context);

int RetriverMerge(Retriver* _retriver, const void* _key, void* _value, KeyValueActionFunction _mergeFunc, void* _context);

int RetriverActionByKey(const Retriver* _retriver, const void* _key, ActionFunction _action, void* _context);

#endif /* __RETRIVER_H__ */
