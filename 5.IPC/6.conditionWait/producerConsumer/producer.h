#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include <stddef.h> /*size_t*/
#include <pthread.h>

#include "queue.h"

typedef struct Producers Producers;

/**
 * @brief: construct _size producers that create items for consumers to consume
 * @param[in] _size: number of consumers to create.
 * @return: new pointer to Producers struct.
 */
Producers* CreateProducers(size_t _size, Queue* _queue);

/**
 * @brief: destroys a producer struct
 * @param[in] _producers: producers struct to destroy
 * return: void
 */
void DestroyProducers(Producers* _producers);

/**
 * @brief: waits untill all producers finished their work.
 * @param[in]: _producers: producer struct containing all the producers to wait for
 * return: void
 */
void ProducerJoin(Producers* _producers);

#endif /* __PRODUCER_H__ */
