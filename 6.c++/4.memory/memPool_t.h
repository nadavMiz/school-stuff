#ifndef __MEM_POOL_T_H__
#define __MEM_POOL_T_H__

#include <iostream>
#include <vector>

using namespace std;

#include "memManager_t.h"
#include "memPage_t.h"

class MemPool_t: public MemManager_t
{
	public:
		MemPool_t ();
		virtual ~MemPool_t ();
		
		size_t GetDefaultPageCapacity() const;
		void SetDefaultPageCapacity(size_t _capacity);
		
		/* virtul functions */
		virtual void SetCurrentPosition(size_t _position);
		virtual size_t Read(void* _data, size_t _size); // returns num of bytes read
		virtual size_t Read(void* _data, size_t _size, size_t _position); // returns num of bytes read
		virtual size_t Write(const void* _data, size_t _size);// returns num of bytes written
		virtual size_t Write(const void* _data, size_t _size, size_t _position);// returns num of bytes written

	private:
		/* data */
		vector<MemPage_t*>* m_pageList;
		
		size_t m_pageNum;
		size_t m_pageLocation;
		
	private:
		MemPool_t(const MemPool_t& _memPool); // non copyable
		MemPool_t& operator=(const MemPool_t& _memPool); // non copyable
		
		void UpdatePageLocation();
		void MoveNextPage();
		void AddPage();
		void AddToPosition(size_t _sizeToAdd);
};

inline size_t MemPool_t::Read(void* _data, size_t _size, size_t _position)
{
	SetCurrentPosition(_position);
	Read(_data, _size);
}

inline size_t MemPool_t::Write(const void* _data, size_t _size, size_t _position)
{
	SetCurrentPosition(_position);
	Write(_data, _size);
}

inline size_t MemPool_t::GetDefaultPageCapacity() const
{
	return (*m_pageList)[0]->GetDefaultCapacity();
}

inline void MemPool_t::SetDefaultPageCapacity(size_t _capacity)
{
	return (*m_pageList)[0]->SetDefaultCapacity(_capacity);
}

#endif /* __MEM_POOL_T_H__ */

