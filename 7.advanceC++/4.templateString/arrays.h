#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include <cstring>
#include <cwchar>

namespace advcpp
{

template<class T>
unsigned int ArrayLength(const T* _array);

template<class T>
unsigned int ArrayCompare(const T* _a, const T* _b);

}

#endif /* __ARRAYS_H__ */

