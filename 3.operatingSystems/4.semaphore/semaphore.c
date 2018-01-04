#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 100

typedef enum
{
	CONSUMER,
	PRODUCER
	
} t_names;

int item = 0;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void* Comsumer(void* _tid)
{
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		--item;
		printf("consumer: %d\n", item);
		pthread_mutex_unlock(&mutex); 
		sem_post(&empty);
	}
	pthread_exit(NULL);
}

void* Producer(void* _tid)
{
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		++item;
		printf("producer: %d\n", item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
	pthread_exit(NULL);
}

int main()
{
	int status;
	pthread_t consumer;
	pthread_t producer;
	status = pthread_mutex_init(&mutex, NULL);
	if(0 != status)
	{
		return 1;
	}
	status = sem_init(&empty, 0, N);
	if(0 != status)
	{
		pthread_mutex_destroy(&mutex);
		return 1;
	}
	status = sem_init(&full, 0, 0);
	if(0 != status)
	{
		pthread_mutex_destroy(&mutex);
		sem_destroy(&empty);
		return 1;
	}
	status = pthread_create(&consumer, NULL, Comsumer, (void*) CONSUMER);
	if(status != 0)
	{
		printf("an error has accured at thread \n");
	}
	
	status = pthread_create(&producer, NULL, Producer, (void*) CONSUMER);
	if(status != 0)
	{
		printf("an error has accured at thread \n");
	}
	
	status = pthread_join(producer ,NULL);
	if(status != 0)
	{
		printf("thread join failed\n");
	}
	
	status = pthread_join(consumer ,NULL);
	if(status != 0)
	{
		printf("thread join failed\n");
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 1;
}
