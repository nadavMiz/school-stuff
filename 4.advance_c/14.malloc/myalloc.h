#ifndef __MYALLOC_H__
#define __MYALLOC_H__

#include <stddef.h> /*size_t */

typedef struct Buffer Buffer;

Buffer* CreateBuffer(size_t _sizeOfChunk, size_t _numOfChunk);

void DestroyBuffer(Buffer* _buffer);

void* MyAlloc(Buffer* _buffer);

void myFree(Buffer* _buffer, void* _data);

#endif /* __MYALLOC_H__ */
