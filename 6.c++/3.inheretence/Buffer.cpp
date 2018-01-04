#include <string.h>

#include "Buffer.h"

void Buffer::BuildByCapacity(size_t _capacity)
{
	m_buffer = new char[_capacity];
	m_capacity = _capacity;
}

Buffer::Buffer(size_t _capacity)
{
	BuildByCapacity(_capacity);
}

Buffer::Buffer(Buffer& _arr)
{
	BuildByCapacity(_arr.m_capacity);
	memcpy(m_buffer, _arr.m_buffer, _arr.m_capacity);
}

Buffer::~Buffer()
{
	delete[] m_buffer;
}

char& Buffer::operator[](size_t _index)
{
	if(_index > m_capacity)
	{
		return m_buffer[m_capacity];
	}
	
	return m_buffer[_index];
}

void Buffer::Resize(size_t _size)
{
	if(_size == m_capacity)
	{
		return;
	}
	char* newBuffer = new char[_size];
	memcpy(newBuffer, m_buffer, m_capacity);
	
	m_buffer = newBuffer;
	m_capacity = _size;
}

