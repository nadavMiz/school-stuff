#include "memPool_t.h"

void MemPool_t::AddPage()
{
	MemPage_t* page = new MemPage_t;
	m_pageList->insert(m_pageList->end(), page);
}

MemPool_t::MemPool_t()
{
	m_pageList = new vector<MemPage_t*>;
	
	AddPage();
	
	UpdatePageLocation();
}

/*-----------------------------------------*/

MemPool_t::~MemPool_t()
{
	for(size_t i = 0; i < m_pageList->size(); ++i)
	{
		delete m_pageList->at(i);
	}
	delete m_pageList;
}

/*-----------------------------------------*/

void MemPool_t::UpdatePageLocation()
{
	m_pageNum = 0;
	size_t bytesLeft = m_currentPosition;
	size_t pageSize;
	// count pages until current page is reached
	while((pageSize = ((*m_pageList)[m_pageNum])->GetCapacity()) < bytesLeft)
	{
		++m_pageNum;
		bytesLeft -= pageSize;
	}
	
	m_pageLocation = bytesLeft;
	
	
}	

/*-----------------------------------------*/

void MemPool_t::SetCurrentPosition(size_t _position)
{
	if(m_actualSize < _position)
	{
		throw _position;
	}
	else
	{
		m_currentPosition = _position;
	}
	
	UpdatePageLocation();
}

/*------------------------------------------*/

void MemPool_t::MoveNextPage()
{
	++m_pageNum;
	m_pageLocation = 0;
}

/*------------------------------------------*/

size_t MemPool_t::Read(void* _data, size_t _size)
{

	if(m_currentPosition == m_actualSize)
	{
		return 0;
	}
	
	size_t bytesRead = 0;
	while(true)
	{
		bytesRead += ((*m_pageList)[m_pageNum])->Read((char*)_data + bytesRead, _size - bytesRead, m_pageLocation);
		
		//if all data was read
		if(bytesRead == _size || m_currentPosition + bytesRead >= m_actualSize)
		{
			m_pageLocation += bytesRead;
			break;
		}
		else
		{
			MoveNextPage();
		}
	}
	
	m_currentPosition += bytesRead;
	return bytesRead;
}


/*----------------------------------------*/

void MemPool_t::AddToPosition(size_t _sizeToAdd)
{
	m_currentPosition += _sizeToAdd;
	if(m_actualSize < m_currentPosition)
	{
		m_actualSize = m_currentPosition;
	}
}

/*----------------------------------------*/

size_t MemPool_t::Write(const void* _data, size_t _size)
{
	size_t bytesWritten = 0;
	while(true)
	{
		bytesWritten += ((*m_pageList)[m_pageNum])->Write((char*)_data + bytesWritten
							,_size - bytesWritten, m_pageLocation);
		
		if(bytesWritten == _size)
		{
			m_pageLocation += bytesWritten;
			break;
		}
		else
		{
			MoveNextPage();
			if(m_pageNum == m_pageList->size())
			{
				AddPage();
			}
		}
	}
	
	AddToPosition(bytesWritten);
	
	return bytesWritten;
}

