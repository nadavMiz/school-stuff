#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <iostream>

#include "guard.h"

using namespace std;

template<class T>
class ProtectedQueue
{
	public:
		explicit ProtectedQueue(unsigned int _size);
		~ProtectedQueue();
		void Push(const T& _item);
		bool Pop(T& _item);
		bool IsEmpty();

	private:
		ProtectedQueue(const ProtectedQueue& _queue);
		ProtectedQueue& operator=(const ProtectedQueue& _queue);
		
	private:
		/* data */
		queue<T> m_queue;
		sem_t m_full;
		pthread_mutex_t m_mutex;
		unsigned int m_capacity;
};

template<class T>
ProtectedQueue<T>::ProtectedQueue(unsigned int _size): m_capacity(_size)
{
	if(sem_init(&m_full, 0, 0) != 0)
	{
		throw runtime_error("bad semaphore");
	}
	
	if(pthread_mutex_init(&m_mutex, NULL) != 0)
	{
		sem_destroy(&m_full);
		throw runtime_error("bad semaphore");
	}
}

template<class T>
ProtectedQueue<T>::~ProtectedQueue()
{
	sem_destroy(&m_full);
	pthread_mutex_destroy(&m_mutex);
}

template<class T>
void ProtectedQueue<T>::Push(const T& _item)
{
	bool isPush = false;
	
	{
		Guard guard(&m_mutex);
		
		if(m_capacity != m_queue.size())
		{
			m_queue.push(_item);
			isPush = true;
		}
	}
	
	if(isPush)
	{
		sem_post(&m_full);
	}
}

template<class T>
bool ProtectedQueue<T>::Pop(T& _item)
{
	if(sem_wait(&m_full) < 0)
	{
		return false;
	}
	
	{
		Guard guard(&m_mutex);
		_item = m_queue.front();
		m_queue.pop();
	}
	
	return true;
}

template<class T>
bool ProtectedQueue<T>::IsEmpty()
{
	bool isEmpty;
	
	pthread_mutex_lock(&m_mutex);
	isEmpty = m_queue.empty();
	pthread_mutex_unlock(&m_mutex);
	
	return isEmpty;
}

#endif /* __QUEUE_H__ */

