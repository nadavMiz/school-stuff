#ifndef __LIST_ITR_H__
#define __LIST_ITR_H__

#define LIST_MAGIC_NUMBER 0X222222


typedef void* ListItr;

/** 
 * @brief Get iterator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItr_Begin(const List* _list);

/** 
 * @brief Get iterator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 * @warning returns the tail sentinal. any making actions on this node is inadvisable
 */
ListItr ListItr_End(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItr_Equals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get iterator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItr_Next(ListItr _itr);

/** 
 * @brief Get iterator to the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItr_Prev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
void* ListItr_Get(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
void* ListItr_Set(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItr_InsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItr_Remove(ListItr _itr);

#endif /* ifndef __LIST_ITR_H__ */

