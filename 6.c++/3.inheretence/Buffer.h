#ifndef __CHAR_ARRAY_H__
#define __CHAR_ARRAY_H__

#include <stddef.h>
#include <string.h>

class Buffer
{
	public:
		Buffer (size_t _length = 1);
		Buffer (Buffer& _arr);
		~Buffer ();
		size_t GetCapacity();
		void Resize(size_t _size);
		const char* GetCString();
		void SetBuffer(const char* _string);
		char& operator[](size_t _index);

	protected:
		/* data */
		char* m_buffer;
		size_t m_capacity;
		
	private:
		void BuildByCapacity(size_t _capacity);
};

inline size_t Buffer::GetCapacity()
{
	return m_capacity;
}

inline const char* Buffer::GetCString()
{
	return m_buffer;
}


inline void Buffer::SetBuffer(const char* _string)
{
	memcpy(m_buffer, _string, m_capacity);
}

#endif /* __CHAR_ARRAY_H__ */

