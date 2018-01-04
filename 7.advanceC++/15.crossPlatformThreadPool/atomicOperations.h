#ifndef __ATOMIC_OPERATIONS__
#define __ATOMIC_OPERATIONS__

namespace advcpp
{
namespace sync
{

int AtomicAdd(int& _numer, int _addNum);

int AtomicSub(int& _number, int _subNum);

void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange);

int Fetch();

#ifdef __GNUC__

	inline int AtomicAdd(int& _numer, int _addNum)
	{
		return __sync_fetch_and_add (&_numer, _addNum);
	}

	inline int AtomicSub(int& _number, int _subNum)
	{
		return __sync_fetch_and_sub (&_number, _subNum);
	}

	inline void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange)
	{
		__sync_val_compare_and_swap(&_value, _toCompare, _toExchange);
	}

	inline int Fetch(int& _number)
	{
		return __sync_fetch_and_add (&_number, 0);
	}

#elif defined _MSC_VER && WIN32

#include <Windows.h>

	inline int AtomicAdd(int& _number, int _addNum)
	{
		return System::Threading::Interlocked::Add(_number, _addNum);
		MemoryBarrier();
	}

	inline int AtomicSub(int& _number, int _subNum)
	{
		return System::Threading::Interlocked::Exchange(_number, _number - _subNum);
		MemoryBarrier();
	}

	inline void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange)
	{
		System::Threading::Interlocked::CompareExchange(_value, _toExchange, _toCompare);
		MemoryBarrier();
	}

	inline int Fetch(int& _number)
	{
		return System::Threading::Interlocked::Add(_number, 0);
	}

#endif/* OS */

}

}

#endif // !__ATOMIC_OPERATIONS__
