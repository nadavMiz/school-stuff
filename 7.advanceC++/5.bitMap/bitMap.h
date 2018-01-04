#ifndef MY_BIT_MAP_H
#define MY_BIT_MAP_H

#include <limits.h>
#include <stdexcept>
#include <string.h>
#include <iostream>
#include <algorithm>

#include "bitOperations.h"

namespace advcpp
{

template < std::size_t SIZE, class T = unsigned char >
class MyBitMap
{
public:
    class BitRefrence
    {
    friend class MyBitMap;
    
    public:
        //~BitRefrence(); using default DTOR
        operator bool() const;
        BitRefrence& operator=(bool _value);
        BitRefrence& operator=(BitRefrence& _value);

    private:
        explicit BitRefrence(T& _bite, const T& _mask);
        BitRefrence(const BitRefrence& _refrence);
        
        /* data */
        T& m_bite;
        T m_mask;
    };

public:
    MyBitMap();
    explicit MyBitMap(bool* _array);
    //MyBitMap(const MyBitMap& _other);
    //~MyBitMap(); using default DTOR
    
    const T* GetArray() const {return m_map;} //for testing
    
    bool GetBit(std::size_t _index) const;
    void SetBit(std::size_t _index, bool _value);
    void Flip(std::size_t _index);
    bool All() const;
    bool Any() const;
    bool Empty() const;
    MyBitMap& Reverse();
    std::size_t Count() const;
    
    MyBitMap& operator=(const MyBitMap& _other);
    bool operator[](std::size_t _index) const;
    BitRefrence operator[](std::size_t _index);
    bool operator==(const MyBitMap& _other) const;
    bool operator!=(const MyBitMap& _other) const;
    MyBitMap& operator&=(const MyBitMap& _other);
    MyBitMap operator&(const MyBitMap& _other) const;
    MyBitMap& operator|=(const MyBitMap& _other);
    MyBitMap operator|(const MyBitMap& _other) const;
    MyBitMap operator~() const;
    MyBitMap& operator<<=(std::size_t _count);
    MyBitMap operator<<(std::size_t _count) const;
    MyBitMap& operator>>=(std::size_t _count);
    MyBitMap operator>>(std::size_t _count) const;

private:
	void ResetChunk(T& _chunk);
	bool IsOutOfBounds(std::size_t _index) const;
    void GetBitLocation(std::size_t _index, std::size_t& _chunkIdx, T& _mask) const;
    void SetBitToBool(bool _value, const std::size_t& _chunkIdx, const T& _mask);
    void MakeLastBitsZero();
    void MakeLastBitsOne();
    
    template < class Iterator, T(*LeftShift)(T,std::size_t), T(*RightShift)(T,std::size_t) >
    void ShiftSet(Iterator _begin, Iterator _end, std::size_t _count);
    
    static T AndOp(const T& _a, const T& _b);
    static T OrOp(const T& _a, const T& _b);
    static T DoTilda(const T& _a);

	/* const sizes */
    static const std::size_t m_chunkSize = sizeof(T) * CHAR_BIT;
    static const std::size_t m_numChunks = SIZE/m_chunkSize + (SIZE % m_chunkSize > 0);
    static const std::size_t m_lastChunkSize = (0 == SIZE % m_chunkSize)? CHAR_BIT : SIZE % m_chunkSize;

    /* data */
    T m_map[m_numChunks];

};

/*----------------------------iterator-----------------------------*/

template<class T>
class ReverseItr: public std::iterator<std::input_iterator_tag, T>
{   
public:
    ReverseItr(T* _location): m_location(_location){}
    ReverseItr(const ReverseItr& _itr): m_location(_itr.m_location){}
    
    ReverseItr& operator=(const ReverseItr& _itr)
    {
        m_location = _itr.m_location;
        return *this;
    }
    
    ReverseItr& operator++()
    {
        --m_location;
        
        return *this;
    }
    
    ReverseItr operator+(std::size_t _count)
    {
        return ReverseItr(m_location - _count);
    }
    
    ReverseItr& operator+=(std::size_t _count)
    {
        m_location -= _count;
        
        return *this;
    }
    
    T& operator*(){return *m_location;}
    
    bool operator==(const ReverseItr& _itr)
    {
        return m_location == _itr.m_location;
    }
    
    bool operator!=(const ReverseItr& _itr)
    {
        return m_location != _itr.m_location;
    }
    
    T& Get()
    {
        return *m_location;
    }
    
private:
    T* m_location;
};

/*---------------------------------------------------------------------*/

template < class T>
struct InitializeChunk
{   
public:
    InitializeChunk(const bool* _from, std::size_t _chunkSize): 
                m_boolArray(_from), m_chunkSize(_chunkSize){}
                
    void operator()(T& _chunk)
    {
       for(std::size_t j = 0; j < m_chunkSize; ++j, ++m_boolArray)
       {
           if(*m_boolArray)
           {
               BitOn<T>(_chunk, static_cast<T>(1) << j);
           }
           else
           {
               BitOff<T>(_chunk, static_cast<T>(1) << j);
           }
       }
    }
    
private:
    const bool* m_boolArray;
    std::size_t m_chunkSize;
};

template < class T >
struct IsNotValue
{
    T m_value;
    IsNotValue(const T& _value): m_value(_value){}
    
    bool operator() (const T& _toCompare)
    {
        return (_toCompare != m_value);
    }
};


template < class T >
struct CountBitsFunctom
{
    std::size_t& m_count;
    
    CountBitsFunctom(std::size_t& _counter): m_count(_counter) {}
    
    void operator()(const T& _chunk)
    {
       m_count = CountBits<T>(_chunk);
    }
};

/*-------------------------------BitRefrence--------------------------------*/

template < std::size_t SIZE, class T>
MyBitMap<SIZE, T>::BitRefrence::BitRefrence(T& _bite, const T& _mask):
                 m_bite(_bite), m_mask(_mask)
{}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>::BitRefrence::operator bool() const
{
    return m_mask & m_bite;
}

template < std::size_t SIZE, class T >
typename MyBitMap<SIZE, T>::BitRefrence& MyBitMap<SIZE, T>::BitRefrence::operator=(bool _value)
{
    if(_value)
    {
        BitOn(m_bite, m_mask);
    }
    else
    {
        BitOff(m_bite, m_mask);
    }
    
    return *this;
}

template < std::size_t SIZE, class T >
inline typename MyBitMap<SIZE, T>::BitRefrence& MyBitMap<SIZE, T>::BitRefrence::operator=(BitRefrence& _value)
{
    *this = bool(_value);
    
    return *this;
}

/*---------------------------------bit map----------------------------------*/

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>::MyBitMap()
{
	std::fill_n(m_map, m_numChunks, 0);
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>::MyBitMap(bool* _array)
{
    std::for_each(m_map, m_map + m_numChunks - 1 , InitializeChunk<T>(_array ,m_chunkSize));
    
    InitializeChunk<T> initializer = InitializeChunk<T>(_array + SIZE - m_lastChunkSize, m_lastChunkSize);
    initializer(m_map[m_numChunks - 1]);
    
    MakeLastBitsZero();
    
}

template < std::size_t SIZE, class T >
inline void MyBitMap<SIZE, T>::ResetChunk(T& _chunk)
{
	_chunk = 0;
}

template < std::size_t SIZE, class T >
inline void MyBitMap<SIZE, T>::MakeLastBitsZero()
{
	m_map[m_numChunks - 1] &= ((static_cast<T>(1) << m_lastChunkSize) - 1);
}


void MakeLastBitsOne();

template < std::size_t SIZE, class T >
inline bool MyBitMap<SIZE, T>::IsOutOfBounds(std::size_t _index) const
{
	return (_index >= SIZE);
}

template < std::size_t SIZE, class T >
void MyBitMap<SIZE, T>::SetBitToBool(bool _value, const std::size_t& _chunkIdx, const T& _mask)
{
    if(_value)
   {
        BitOn(m_map[_chunkIdx], _mask);
   }
   else
   {
        BitOff(m_map[_chunkIdx], _mask);
   }
}

template < std::size_t SIZE, class T >
void MyBitMap<SIZE, T>::GetBitLocation(std::size_t _index, std::size_t& _chunkIdx, T& _mask) const
{
	if(IsOutOfBounds(_index))
    {
        throw std::overflow_error("index out of bounds");
    }
    
    _chunkIdx = _index / m_chunkSize;
    
    _mask = GetMask<T>(_index % m_chunkSize); // 1 << bit location in chunk
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator=(const MyBitMap& _other)
{
	std::copy(_other.m_map, _other.m_map + m_numChunks, m_map);
	
	return *this;
}

template < std::size_t SIZE, class T >
bool MyBitMap<SIZE, T>::GetBit(std::size_t _index) const
{
    T mask;
    std::size_t chunkIdx;
    
    GetBitLocation(_index, chunkIdx, mask);
    
    return m_map[chunkIdx] & mask;
}

template < std::size_t SIZE, class T >
void MyBitMap<SIZE, T>::SetBit(std::size_t _index, bool _value)
{
    T mask;
    std::size_t chunkIdx;
    
    GetBitLocation(_index, chunkIdx, mask);
    
    SetBitToBool(_value, chunkIdx, mask);
}

template < std::size_t SIZE, class T >
typename MyBitMap<SIZE, T>::BitRefrence MyBitMap<SIZE, T>::operator[](std::size_t _index)
{
    T mask;
    std::size_t chunkIdx;
    
    GetBitLocation(_index, chunkIdx, mask);
    
    return BitRefrence(m_map[chunkIdx], mask);
}

template < std::size_t SIZE, class T >
bool MyBitMap<SIZE, T>::operator[](std::size_t _index) const
{
    std::size_t chunkIdx;
    T mask;
    
    GetBitLocation(_index, chunkIdx, mask);
    
    return m_map[_index] & mask;
}


template < std::size_t SIZE, class T >
inline bool MyBitMap<SIZE, T>::operator==(const MyBitMap& _other) const
{
	return std::equal(m_map, m_map + m_numChunks, _other.m_map);
}

template < std::size_t SIZE, class T >
inline bool MyBitMap<SIZE, T>::operator!=(const MyBitMap& _other) const
{
	return !(*this == _other);
}
 
template < std::size_t SIZE, class T >
void MyBitMap<SIZE, T>::Flip(std::size_t _index)
{
	std::size_t chunkIdx;
    T mask;
    
    GetBitLocation(_index, chunkIdx, mask);
    
    BitFlip(m_map[chunkIdx], mask);
}

template < std::size_t SIZE, class T >
bool MyBitMap<SIZE, T>::All() const
{
	T allOnes = ~static_cast<T>(0);

    const T* end = m_map + m_numChunks - 1;
	if(end != std::find_if(m_map, end, IsNotValue<T>(allOnes)))
	{
	    return false;
	}
	
    //last Chunk
    allOnes = (static_cast<T>(1) << m_lastChunkSize) - 1;
    if(allOnes != m_map[m_numChunks - 1])
    {
    	return false;
    }
    
    return true;
}

template < std::size_t SIZE, class T >
inline bool MyBitMap<SIZE, T>::Any() const
{
    const T* end = m_map + m_numChunks;
	if(end == std::find_if(m_map, end, IsNotValue<T>(0)))
	{
	    return false;
	}
	
	return true;
}

template < std::size_t SIZE, class T >
inline T MyBitMap<SIZE, T>::DoTilda(const T& _a)
{
    return ~_a;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::Reverse()
{
	std::transform(m_map, m_map + m_numChunks, m_map, DoTilda);
	
	MakeLastBitsZero();
	
	return *this;
}

template < std::size_t SIZE, class T >
inline bool MyBitMap<SIZE, T>::Empty() const
{
	return !Any();
}

template <std::size_t SIZE, class T >
inline T MyBitMap<SIZE, T>::AndOp(const T& _a, const T& _b)
{
    return _a & _b;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator&=(const MyBitMap& _other)
{
	std::transform(m_map, m_map + m_numChunks, _other.m_map, m_map, AndOp);
	
	MakeLastBitsZero();
	
	return *this;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T> MyBitMap<SIZE, T>::operator&(const MyBitMap& _other) const
{
	MyBitMap result(*this);
	
	result &= _other;
	
	return result;
}

template < std::size_t SIZE, class T >
inline T MyBitMap<SIZE, T>::OrOp(const T& _a, const T& _b)
{
    return _a | _b;
}

template < std::size_t SIZE, class T >
inline MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator|=(const MyBitMap& _other)
{
	std::transform(m_map, m_map + m_numChunks, _other.m_map, m_map, OrOp);
	
	return *this;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T> MyBitMap<SIZE, T>::operator|(const MyBitMap& _other) const
{
	MyBitMap result(*this);
	
	result |= _other;
	
	return result;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T> MyBitMap<SIZE, T>::operator~() const
{
	MyBitMap result(*this);
	
	result.Reverse();
	
	return result;
}


template <class T>
inline T LeftShiftOp(T _value, std::size_t _count)
{
    return _value << _count;
}

template <class T>
inline T RightShiftOp(T _value, std::size_t _count)
{
    return _value >> _count;
}

template < std::size_t SIZE, class T >
template < class Iterator, T(*LeftShift)(T,std::size_t),  T(*RightShift)(T,std::size_t) >
void MyBitMap<SIZE, T>::ShiftSet(Iterator _begin, Iterator _end, std::size_t _count)
{
    Iterator dest = _begin;
    Iterator source = _begin + _count / m_chunkSize;
    std::size_t leftShift = _count % m_chunkSize;
	std::size_t rightShift = m_chunkSize - _count % m_chunkSize;
	
	*dest = LeftShift(*source, leftShift);
	
	for(++source; source != _end; ++source, ++dest)
	{
		*dest |= RightShift(*source, rightShift);
		Iterator next = (dest + 1);
		*next = LeftShift(*source, leftShift);
	} 
	
	std::fill(++dest, _end, 0);
}


template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator<<=(std::size_t _count)
{
	ShiftSet<T*, RightShiftOp<T>, LeftShiftOp<T> >(m_map, m_map + m_numChunks, _count);
	
	return *this;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T> MyBitMap<SIZE, T>::operator<<(std::size_t _count) const
{
	MyBitMap result(*this);
	
	result <<= _count;
	
	return result;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator>>=(std::size_t _count)
{
	ShiftSet<ReverseItr<T>, LeftShiftOp<T>, RightShiftOp<T> >
	            (ReverseItr<T>(m_map + m_numChunks - 1), ReverseItr<T>(m_map - 1), _count);
	
	return *this;
}

template < std::size_t SIZE, class T >
MyBitMap<SIZE, T> MyBitMap<SIZE, T>::operator>>(std::size_t _count) const
{
	MyBitMap result(*this);
	
	result >>= _count;
	
	return result;
}

template < std::size_t SIZE, class T >
std::size_t MyBitMap<SIZE, T>::Count() const
{
    std::size_t count = 0;
    
    std::for_each(m_map, m_map + m_numChunks, CountBitsFunctom<T>(count));

    return count;
}

/*template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator<<=(std::size_t _count)
{
    
	std::size_t toIdx = 0;
	std::size_t fromIdx = _count / m_chunkSize;
	std::size_t leftShift = _count % m_chunkSize;
	std::size_t rightShift = m_chunkSize - _count % m_chunkSize;
	
	m_map[toIdx] = m_map[fromIdx] >> leftShift;
	
	for(++fromIdx; fromIdx < m_numChunks; ++fromIdx, ++toIdx)
	{
		m_map[toIdx] |= m_map[fromIdx] << rightShift;
		m_map[toIdx + 1] = m_map[fromIdx] >> leftShift;
	}
	
	++toIdx;
	std::fill_n( m_map + toIdx, m_numChunks - toIdx, 0 );
	
	return *this;
	ShiftSet<T*, RightShiftOp<T>, LeftShiftOp<T> >(m_map, m_map + m_numChunks, _count);
	
	return *this;
}*/

/*template < std::size_t SIZE, class T >
MyBitMap<SIZE, T>& MyBitMap<SIZE, T>::operator>>=(std::size_t _count)
{
	std::size_t toIdx = m_numChunks - 1;
	std::size_t fromIdx = m_numChunks - (_count / m_chunkSize) - 1;
	std::size_t rightShift = _count % m_chunkSize;
	std::size_t leftShift = m_chunkSize - rightShift;
	
	while(fromIdx > 0)
	{
		m_map[toIdx] = m_map[fromIdx] << rightShift;
		--fromIdx;
		m_map[toIdx] += m_map[fromIdx] >> leftShift;
		--toIdx;
	}
	
	m_map[toIdx] = m_map[fromIdx] << rightShift;
	
	std::fill_n(m_map, toIdx, 0);

	MakeLastBitsZero();
	
	ShiftSet<ReverseItr<T>, LeftShiftOp<T>, RightShiftOp<T> >(ReverseItr<T>(m_map + m_numChunks - 1), ReverseItr<T>(m_map - 1), _count);
	
	return *this;
}*/

}


#endif /* MY_BIT_MAP_H */

