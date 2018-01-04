#ifndef bitOperations_H
#define bitOperations_H

#include <cstddef>
#include <climits>
#include <stdexcept>

namespace advcpp
{
template<class T>
T GetMask(std::size_t _index);

template<class T>
void BitOn(T& _chunk, const T& _mask);

template<class T>
void BitOff(T& _chunk, const T& _mask);

template<class T>
void BitFlip(T& _chunk, const T& _mask);

template<class T>
std::size_t CountBits(T _chunk);


/*------------------------------------------------------------*/

template<class T>
T GetMask(std::size_t _index)
{
    if(_index >= (CHAR_BIT * sizeof(T)))
    {
        throw std::overflow_error("out of bounds");
    }
    
    return static_cast<T>(1) <<  _index;
}

template<class T>
inline void BitOn(T& _chunk, const T& _mask)
{
    _chunk |= _mask;
}

template<class T>
inline void BitOff(T& _chunk, const T& _mask)
{
    _chunk &= ~_mask;
}

template<class T>
inline void BitFlip(T& _chunk, const T& _mask)
{
    _chunk ^= _mask;
}

template<class T>
inline bool IsOn(T& _chunk, T _mask)
{
    return _chunk & _mask;
}

template<class T>
std::size_t CountBits(T _chunk)
{
   std::size_t count = 0;
   T mask = 1;
   for(std::size_t j = 0; j < sizeof(T) * CHAR_BIT; ++j)
   {
       count += bool(mask & _chunk);
       mask <<= 1;
   }
   
   return count;
}

}

#endif /* bitOperations_H */

