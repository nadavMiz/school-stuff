#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "queue.h"

typedef struct Consumers Consumers;

/**
 * @brief construct _size consumers that consumes items made by producers
 * @param[in] _size: number of consumers to create
 * @return: new struct of consumers
 */
Consumers* CreateConsumers(size_t _size, Queue* _queue);

/**
 * @brief: safely destroys a consumers struct
 * @param[in]: _consumers: struct containing all consumers to destroy
 * @return void
 */
void DestroyConsumers(Consumers* _consumers);

/**
 * @brief: signal to all consumers that there are no more producers running and 
 *			therefore they should quit once queue is empty.
 * @param[in] _consumers: consumers to end.
 * @return: void
 */
void SignalEndConsumeCycle(Consumers* _consumers);

/**
 * @brief: waits until all consumers finished their work. assumes the consumers are th only ones working on queue
 * @param[in] _consumers: consumer struct to wait for
 * @return void.
 */
void ConsumersJoin(Consumers* _consumers);
#endif /* __CONSUMER_H__ */
