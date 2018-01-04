#ifndef __MEM_PAGE_T_H__
#define __MEM_PAGE_T_H__

#include <stddef.h>

#include "memManager_t.h"

class MemPage_t: public MemManager_t
{
	public:
		MemPage_t();
		virtual ~MemPage_t();
		
		size_t GetCapacity() const;
		bool IsFull() const;
		
		/*virtual functions*/
		virtual void SetCurrentPosition(size_t _position);
		virtual size_t Read(void* _data, size_t _size);
		virtual size_t Read(void* _data, size_t _size, size_t _position);
		virtual size_t Write(const void* _data, size_t _size);
		virtual size_t Write(const void* _data, size_t _size, size_t _position);
		
		/* static functions */
		static size_t GetDefaultCapacity();
		static void SetDefaultCapacity(size_t _capacity);

	private:
		/* data */
		size_t m_capacity;
		char* m_buffer;
		
		/* static data */
		static size_t m_defaultCapacity; // default to 32
		
	private:
		MemPage_t(const MemPage_t& _memPage); // non copyable
		MemPage_t& operator=(const MemPage_t& _memPage); // non copyable
		
		size_t NumBytesToCopy(size_t _position, size_t _size, size_t _maxSize) const;
};

inline size_t MemPage_t::GetCapacity() const
{
	return m_capacity;
}

inline size_t MemPage_t::GetDefaultCapacity()
{
	return m_defaultCapacity;
}

inline void MemPage_t::SetDefaultCapacity(size_t _capacity) 
{
	m_defaultCapacity = _capacity;
}

inline bool MemPage_t::IsFull() const
{
	return (m_actualSize == m_capacity);
}

inline size_t MemPage_t::Read(void* _data, size_t _size, size_t _position)
{
	SetCurrentPosition(_position);
	return Read(_data, _size);
}

inline size_t MemPage_t::Write(const void* _data, size_t _size, size_t _position)
{
	SetCurrentPosition(_position);
	return Write(_data, _size);
}

#endif /* __MEM_PAGE_T_H__ */

