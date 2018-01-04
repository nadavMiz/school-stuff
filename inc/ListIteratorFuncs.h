/** 
 * @brief Predicate function returns a none zero value if predicate holds for element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return none zero if predicate holds
 */
typedef int (*PredicateFunction)(void * _element, void* _context);

/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
typedef int (*ListActionFunction)(void* _element, void* _context);

/** 
 * @brief Action function to check if a < b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a < _b
 */
typedef int (*LessFunction)(void* _a, void* _b);

/** 
 * @brief Action function to check if a == b
 *
 * @param _a : element to test
 * @param _b : element to test against
 * @return none zero if _a == _b
 */
typedef int (*EqualsFunction)(void* _a, void* _b);


/** 
 * @brief Finds the first element in a range satsifying a predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return an iterator pointing to the first node with data found or to _end if not
 */
ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context);

/** 
 * @brief count elements in a sub list satisfying predicate
 * @details find the element for which the predicate reuturns a non zero value
 *  in the half open range [begin..end)
 *
 * @param _begin : start search from here
 * @param _end : end search here - not included
 * @param _predicate : Predicate function
 * @param _context : context to be passed to the predicate
 * @return count of all elements e where _predicate(e, _context) != 0
 */
size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunc _predicate, void* _context);

/** 
 * @brief Sorts a sublist in place using the bubble sort algorithm
 * Complexity O(n^2)
 *
 * @params _begin : Iterator to sublist start
 * @params _end : Iterator to sublist end
 * @params _less : less compare function
 * 
 */
void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less);


/** 
 * @brief Splice all element from [_begin.._end) into _dst
 * @details remove all elements from the half open range [_begin.._end)
 * and insert them before _dest
 * O(?)
 *
 * @warning The function assumes that : 
 *  _begin and _end are in the correct order and on the same list
 *  _dset is not between them
 * Otherwise behavior is undefined
 * all three iterators can belong to same list
 */
ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end);

/** 
 * @brief Merges two given sub lists into destination 
 * @details Merge elements from two sub lists defined by [_firstbegin.._firstEnd)
 * and [_secondBegin.._secondEnd) in optionaly sorted order using _less function.
 * merged elements will be inserted before _destBegin
 * if a _less function is provided then merge will be sorted
 * 
 * @warning this will removes all merged items from source ranges.
 * O(?)
 *  
 */
ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less);

/** 
 * @brief Removes a sublist [_begin.._end) from a list and creates a new list
 * with all removed items.
 * O(?)
 *
 */
List* ListItr_Cut(ListItr _begin, ListItr _end);

/** 
 * @brief Removes all duplicate elements from a sorted sublist [_begin.._end) 
 * and rertun a new list with all removed items.
 * O(?)
 * post condition: [_begin.._end) contains only unique elements
 */
List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals);


