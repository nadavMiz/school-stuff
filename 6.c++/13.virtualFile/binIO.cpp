#include <stdio.h>

#include "binIO.h"


biniIO_t& biniIO_t::operator<<(const void* _buffer)
{
	m_isWrite = true;
	m_buffer = (void*)_buffer;
	
	return *this;
}

biniIO_t& biniIO_t::operator>>(void* _buffer)
{
	m_isWrite = false;
	m_buffer = _buffer;
	
	return *this;
}
