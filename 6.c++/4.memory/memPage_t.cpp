#include <string.h>

#include "memManager_t.h"
#include "memPage_t.h"

size_t MemPage_t::m_defaultCapacity = 32;

MemPage_t::MemPage_t ()
{
	m_capacity = m_defaultCapacity;
	
	m_buffer = new char[m_capacity];
	if(NULL == m_buffer)
	{
		//TODO something
	}
}

/*--------------------------------------*/

MemPage_t::~MemPage_t()
{
	delete[] m_buffer;
}

/*--------------------------------------*/

void MemPage_t::SetCurrentPosition(size_t _position)
{
	if(m_capacity < _position)
	{
		m_currentPosition = m_capacity;
	}
	else
	{
		m_currentPosition = _position;
	}
}

/*-------------------------------------*/

size_t MemPage_t::NumBytesToCopy(size_t _position, size_t _size, size_t _maxSize) const
{
	int bytesRemaining = _maxSize - _position;
	if(bytesRemaining < 0)
	{
		return 0;
	}
	else if(bytesRemaining < _size)
	{
		return (size_t)bytesRemaining;
	}
	else
	{
		return _size;
	}
}

/*-------------------------------------*/

size_t MemPage_t::Read(void* _data, size_t _size)
{
	_size = NumBytesToCopy(m_currentPosition, _size, m_actualSize);
	
	memcpy(_data, m_buffer + m_currentPosition, _size);
	
	m_currentPosition += _size;
	
	return _size;
}

/*------------------------------------*/

size_t MemPage_t::Write(const void* _data, size_t _size)
{
	_size = NumBytesToCopy(m_currentPosition, _size, m_capacity);
	
	memcpy(m_buffer + m_currentPosition, _data, _size);
	
	m_currentPosition += _size;
	// if new data was written update the actual size
	if(m_actualSize < m_currentPosition)
	{
		m_actualSize = m_currentPosition;
	}
	
	return _size;
}

/*----------------------------------*/


