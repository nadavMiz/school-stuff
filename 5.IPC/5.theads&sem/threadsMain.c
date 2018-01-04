#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "queue.h"
#include "consumer.h"
#include "producer.h"

#define QUEUE_SIZE 20
#define NUM_PRODUCERS 5
#define NUM_CONSUMERS 3

typedef struct
{
	size_t m_NumConsumers;
	size_t m_NumProducers;
	
} InputData;

/*----------------------------*/

static void CloseProcess(Consumers* _consumers, Producers* _producers, Queue* _queue)
{
	DestroyConsumers(_consumers);
	DestroyProducers(_producers);
	QueueDestroy(_queue);
}

/*---------------------------*/

static void ReadInput(int _argc, char** _argv, InputData* _input)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "c:p:?")) != -1)
	{
		switch(opt)
		{
			case 'c':
				_input->m_NumConsumers = (size_t)atoi(optarg);
				break;
			case 'p':
				_input->m_NumProducers = (size_t)atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-c consumers = number of consumers] [-p producers = number of producers]", _argv[0]);
				exit(1);
	 	}
	}
}

int main(int argc, char* argv[])
{
	InputData input = {NUM_CONSUMERS, NUM_PRODUCERS};
	Consumers* consumers;
	Producers* producers;
	Queue* queue;
	
	ReadInput(argc, argv, &input);
	
	queue = QueueCreate(QUEUE_SIZE);
	if(NULL == queue)
	{
		return 0;
	}
	
	/*create consumers and producers*/
	consumers = CreateConsumers(input.m_NumConsumers, queue);
	if(0 == consumers)
	{
		QueueDestroy(queue);
		return 0;
	}
	
	producers = CreateProducers(input.m_NumProducers, queue);
	if(0 == producers)
	{
		QueueDestroy(queue);
		DestroyConsumers(consumers);
		return 0;
	}
	
	/*wait for all threads to end and exit*/
	ProducerJoin(producers);
	SignalEndConsumeCycle(consumers);
	ConsumersJoin(consumers);
	CloseProcess(consumers, producers, queue);
}
