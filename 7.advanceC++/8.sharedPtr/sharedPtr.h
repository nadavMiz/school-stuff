#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <stdexcept>
#include <stdio.h>
#include "guard.h"

namespace advcpp
{

template <class T>
class SharedPtr
{

typedef void (*SafeBool) (void);

template<class U>
friend class SharedPtr;

public:

    SharedPtr(T* _element);
    SharedPtr(const SharedPtr& _ptr);
    template<class U>
    SharedPtr(const SharedPtr<U>& _ptr);
    ~SharedPtr();

    SharedPtr& operator=(const SharedPtr& _sharedPtr);
    template<class U>
    SharedPtr& operator=(const SharedPtr<U>& _sharedPtr);
    template<class U>
    bool operator==(SharedPtr<U>& _ptr) const;
    template<class U>
    bool operator!=(SharedPtr<U>& _ptr) const;
    T& operator*();
    const T* operator*() const;
    const T* GetPtr() const;
    T* operator->();
    const T* operator->() const;
    operator SafeBool() const;
    
    unsigned int GetCounter() { return *m_NumCopies; }
    
    static unsigned int*(*Count[2])(void);
    static unsigned int* GetNull();
    static unsigned int* GetNewCounter();
    static unsigned int m_nullCounter;
    
    static void TrueFunc(){}

private:
    template<class U>
    void CopyElement(const SharedPtr<U>& _event);
    void DecreaseCopy();

private:
    /* data */
    T* m_data;
    unsigned int* m_NumCopies;
        
};

template <class T>
unsigned int SharedPtr<T>::m_nullCounter = 1;

template <class T>
unsigned int*(*SharedPtr<T>::Count[2])(void) = {GetNull, GetNewCounter};

template <class T>
unsigned int* SharedPtr<T>::GetNull()
{
    return &(++m_nullCounter);
}

template <class T>
unsigned int* SharedPtr<T>::GetNewCounter()
{
    return new unsigned int(1);
}

template <class T>
static unsigned int* RealNew()
{
    return 0;
}

template <class T>
SharedPtr<T>::SharedPtr(T* _element): m_data(_element)
{
    try
    {
        m_NumCopies = Count[bool(_element)]();
    }
    catch(std::exception& _err)
    {
        delete m_data;
        throw;
    }
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    DecreaseCopy();
}

template <class T>
template <class U>
void SharedPtr<T>::CopyElement(const SharedPtr<U>& _sharedPtr)
{	
	m_data = _sharedPtr.m_data;
	m_NumCopies = _sharedPtr.m_NumCopies;
	__sync_fetch_and_add(m_NumCopies, 1);
}

template <class T>
template<class U>
inline SharedPtr<T>::SharedPtr(const SharedPtr<U>& _sharedPtr)
{
    CopyElement(_sharedPtr);
}

template <class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& _sharedPtr)
{
	CopyElement(_sharedPtr);
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& _sharedPtr)
{
	if(m_data == _sharedPtr.m_data)
	{
		return *this;
	}
	
	DecreaseCopy();
	
	// copy the other event and increase its counter
	CopyElement(_sharedPtr);
	
	return *this;
}

template<class T>
template<class U>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& _sharedPtr)
{
	if(m_data == _sharedPtr.m_data)
	{
		return *this;
	}
	
	DecreaseCopy();
	
	// copy the other event and increase its counter
	CopyElement(_sharedPtr);
	
	return *this;
}

template <class T>
void SharedPtr<T>::DecreaseCopy()
{	
	if(!__sync_bool_compare_and_swap(m_NumCopies, 0, 0))
	{	
		__sync_fetch_and_sub(m_NumCopies, 1);
		if(__sync_bool_compare_and_swap(m_NumCopies, 0, 0))
		{
			delete m_data;
			delete m_NumCopies;
		}
	}
}

template <class T>
inline T& SharedPtr<T>::operator*()
{
    return *m_data;
}

template <class T>
inline const T* SharedPtr<T>::operator*() const
{
    return *m_data;
}

template <class T>
inline const T* SharedPtr<T>::GetPtr() const
{
    return m_data;
}

template <class T>
inline T* SharedPtr<T>::operator->()
{
    return m_data;
}

template <class T>
inline const T* SharedPtr<T>::operator->() const
{
   return m_data; 
}

template <class T>
inline SharedPtr<T>::operator SafeBool() const
{
    return (m_data != 0) ? TrueFunc: 0;
}

template <class T>
template <class U>
inline bool SharedPtr<T>::operator==(SharedPtr<U>& _ptr) const
{
    return (m_data == _ptr.m_data);
}

template <class T>
template <class U>
inline bool SharedPtr<T>::operator!=(SharedPtr<U>& _ptr) const
{
    return !(*this == _ptr);
}

}

#endif /* SHARED_PTR_H */

