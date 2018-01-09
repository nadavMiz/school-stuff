#ifndef __ATOMIC_OPERATIONS__
#define __ATOMIC_OPERATIONS__

namespace advcpp
{
namespace sync
{

int AtomicAdd(int& _numer, int _addNum);

int AtomicSub(int& _number, int _subNum);

bool AtomicIsNull(int _value);

void AtomicCompareAndExchange(int& _value, int _toCompare, int _toExchange);

}

}

#endif // !__ATOMIC_OPERATIONS__
