#ifndef __BARRIER_H__
#define __BARRIER_H__


typedef struct Barrier Barrier;

/**
 * @brief: creates a new barrier
 * @param[in] _capacity: the number of items in the barrier when it relese all the blocked threads
 * @return: pointer to a new barrier
 */
Barrier* BarrierCreate(unsigned int _capacity);

/**
 * @brief: destroys a barrier
 * @param[in] _barrier: barrier to destroy
 * @return: void
 */
void BarrierDestroy(Barrier* _barrier);

/**
 * @brief: blocks the thread in the barrier. relice all blocked threads once the number of threads reached.
 * @param[in] _barrier: the barrier to wait on
 * @return 1: exited sucessfully. 0: thread was not initialized -1: exit with error
 */
int BarrierWait(Barrier* _barrier);

#endif /* __BARRIER_H__ */
