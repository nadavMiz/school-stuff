#include <stdlib.h>

#include "myalloc.h"

#define BUFFER_MAGIC_NUM 0XDFABBB32
#define CHUNK_MAGIC_NUM 0XCDEFAAAA

#define IS_BUFFER(B) (NULL != (B) && BUFFER_MAGIC_NUM == (B)->m_magicNumber)
#define CHUNK_SIZE (sizeof(Chunk) - 4)

typedef struct Chunk Chunk;

struct Buffer
{
	Chunk* m_free;
	size_t m_magicNumber;
};

struct Chunk
{
	Chunk* m_next;
	size_t m_magicNumber;
	char m_data;
};

/*--------------------------------------------------*/

static void InitializeChunks(Buffer* _buffer, size_t _jumpSize, size_t _numOfChunk)
{
	size_t i;
	Chunk* currentChunk;
	Chunk* nextChunk;
	
	/* get the first chunk */
	_buffer->m_free = (Chunk*)((char*)_buffer + sizeof(Buffer));
	
	/*initialize all chunk values */
	currentChunk = _buffer->m_free;
	for(i = 0; i < _numOfChunk - 1; ++i)
	{
		nextChunk = (Chunk*)((char*)currentChunk + _jumpSize);
		
		currentChunk->m_next = nextChunk;
		currentChunk->m_magicNumber = CHUNK_MAGIC_NUM;
		
		currentChunk = nextChunk;
	}
	
	currentChunk->m_next = NULL;
}

Buffer* CreateBuffer(size_t _sizeOfChunk, size_t _numOfChunk)
{
	Buffer* newBuffer;
	size_t jumpSize;
	
	jumpSize = CHUNK_SIZE + _sizeOfChunk;
	
	/*allocate all memory space*/
	newBuffer = malloc(sizeof(Buffer) + (jumpSize * _numOfChunk));
	if(NULL == newBuffer)
	{
		return NULL;
	}

	newBuffer->m_magicNumber = BUFFER_MAGIC_NUM;
	
	if(0 == _numOfChunk)
	{
		newBuffer->m_free = NULL;
		return newBuffer;
	}
	
	InitializeChunks(newBuffer, jumpSize, _numOfChunk);
	return newBuffer;
}

void DestroyBuffer(Buffer* _buffer)
{
	if(!IS_BUFFER(_buffer))
	{
		return;
	}
	
	_buffer->m_magicNumber = 0;
	free(_buffer);
}

void* MyAlloc(Buffer* _buffer)
{
	void* data;
	
	if(!IS_BUFFER(_buffer) || NULL == _buffer->m_free)
	{
		return NULL;
	}
	
	_buffer->m_free->m_magicNumber = 0;
	data = (void*)(&(_buffer->m_free->m_data));
	_buffer->m_free = _buffer->m_free->m_next;
	
	return data;
}

void myFree(Buffer* _buffer, void* _data)
{
	Chunk* freedChunk;
	size_t magicNum = ((Chunk*)((char*)_data - CHUNK_SIZE))->m_magicNumber;
	
	if(!IS_BUFFER(_buffer) || CHUNK_MAGIC_NUM == magicNum)
	{
		return;
	}
	
	freedChunk = (Chunk*)((char*)_data - CHUNK_SIZE);
	freedChunk->m_next = _buffer->m_free;
	freedChunk->m_magicNumber = CHUNK_MAGIC_NUM;
	_buffer->m_free = freedChunk;
}

