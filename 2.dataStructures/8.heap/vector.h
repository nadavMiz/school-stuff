#ifndef _DYNAMIC_VECTOR_
#define _DYNAMIC_VECTOR_
#include "ADTErr.h"
#include <stddef.h>

typedef struct

{
	int*    m_items;		  /* array of items */
	size_t  m_originalSize;   /* original allocated space for items) */
    size_t  m_size;           /* actual allocated space for items) */
    size_t  m_nItems;         /* actual number of items */
    size_t  m_blockSize;      /* the chunk size to be allocated when no space*/

} Vector;

/* creates a new vector */
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);

/* destroy the vector and free all space */
void VectorDestroy(Vector* _vector);

/* Add item to end. */
ADTErr VectorAdd(Vector *_vector,  int  _item);

/* Delete item from the end. */
ADTErr VectorDelete(Vector *_vector,  int* _item);

/**** The Index range in the following functions is : 1..numOfItems ****/

/*get item at index _index of the vector*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_dest);

/* set item at index _index*/
ADTErr VectorSet(Vector *_vector, size_t _index, int  _item);

/* get the number of elements */
ADTErr VectorItemsNum(Vector *_vector, int*  _numOfItems);

/*  Unit-Test functions  */

/* print the vector */
void VectorPrint(Vector *_vector);



#endif /*_DYNAMIC_VECTOR_ */
