#ifndef __MEM_MANAGER_T_H__
#define __MEM_MANAGER_T_H__

#include <stddef.h> /* size_t */

class MemManager_t
{
	public:
		MemManager_t(){m_currentPosition = 0; m_actualSize = 0;}
		virtual ~MemManager_t () = 0;
		bool IsEmpty() const;
		size_t GetActualSize() const;
		size_t GetCurrentPosition() const;
		
		/* virtul functions */
		virtual void SetCurrentPosition(size_t _position) = 0;
		virtual size_t Read(void* _data, size_t _size) = 0;
		virtual size_t Read(void* _data, size_t _size, size_t position) = 0;
		virtual size_t Write(const void* _data, size_t _size) = 0;
		virtual size_t Write(const void* _data, size_t _size, size_t position) = 0;

	protected:
		
		/* data */
		size_t m_currentPosition;
		size_t m_actualSize;
		
	private:
		MemManager_t(const MemManager_t& _memManager); // non copyable
		MemManager_t& operator=(const MemManager_t& _memManager); // non copyable
};

inline MemManager_t::~MemManager_t(){}

inline bool MemManager_t::IsEmpty() const
{
	return (0 == m_actualSize);
}

inline size_t MemManager_t::GetActualSize() const
{
	return  m_actualSize;
}

inline size_t MemManager_t::GetCurrentPosition() const
{
	return m_currentPosition;
}

#endif /* __MEM_MANAGER_T_H__ */

