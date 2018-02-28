#include "atomicOperations.h"

#if defined _MSC_VER && WIN32
#include <Windows.h>
#endif /* _MSC_VER && WIN32 */


namespace advcpp
{
namespace sync
{

#ifdef __GNUC__

	int AtomicAdd(int& _numer, int _addNum)
	{
		return __sync_fetch_and_add (&_numer, _addNum);
	}

	int AtomicSub(int& _number, int _subNum)
	{
		return __sync_fetch_and_sub (&_number, _subNum);
	}

	bool AtomicIsNotNull(int _value)
	{
		return __sync_fetch_and_or (&_value, 0);
	}

	void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange)
	{
		__sync_val_compare_and_swap(&_value, _toCompare, _toExchange);
	}

#elif defined _MSC_VER && WIN32

	int AtomicAdd(int& _number, int _addNum)
	{
		return System::Threading::Interlocked::Add(_number, _number + _addNum);
	}

	int AtomicSub(int& _number, int _subNum)
	{
		return System::Threading::Interlocked::Add(_number, _number - _subNum);
	}

	void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange)
	{
		System::Threading::Interlocked::CompareExchange(_value, _toExchange, _toCompare);
	}

#endif/* OS */
}

}
