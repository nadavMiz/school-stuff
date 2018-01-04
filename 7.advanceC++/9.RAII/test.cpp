#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "mu_test.h"
#include "Nmutex.h"
#include "nthread.h"
#include "threadable.h"
#include "ncond.h"
#include "guard.h"

using namespace advcpp;

class AddOne: public Threadable
{
public:
	AddOne(unsigned int* _data): m_data(_data){}
	void RunThread()
	{
		for(unsigned int i = 0; i < 1000; ++i)
    	{
			Guard nadav(AddOne::m_mutex);
			++(*m_data);
		}
	}
	
	static void* Run(void* _one){((AddOne*)_one)->RunThread(); return 0;}
	static void* RunMutex(void* _data)
	{
		for(unsigned int i = 0; i < 1000; ++i)
    	{
			m_mutex.Lock();
			(++*((unsigned int*)_data));
			m_mutex.Unlock();
		}
		return 0;
	}
	
	static void* RunCond(void* _data)
	{
		m_mutex.Lock();
		(++*((unsigned int*)_data));
		m_cond.Wait(AddOne::m_mutex);
		m_mutex.Unlock();
		return 0;
	}
private:
	static Nmutex m_mutex;
	unsigned* m_data;
	
public:
	static advcpp::Ncond m_cond;
};

Nmutex AddOne::m_mutex;
advcpp::Ncond AddOne::m_cond;

UNIT(mutex_test)

unsigned int numThreads = 1000;
unsigned int* data = new unsigned int(0);

pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, AddOne::RunMutex, data);
}

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_join(threads[i], 0);
}

ASSERT_THAT(numThreads*1000 == *data);

delete threads;
delete data;
END_UNIT

UNIT(guard_test)

unsigned int numThreads = 1000;
unsigned int* data = new unsigned int(0);
AddOne adder(data);

pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, AddOne::Run, &adder);
}

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_join(threads[i], 0);
}

ASSERT_THAT(numThreads*1000 == *data);

delete threads;
delete data;
END_UNIT

UNIT(thread_test)

unsigned int numThreads = 1000;
unsigned int* data = new unsigned int(0);
AddOne adder(data);

Nthread** threads = new Nthread*[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    threads[i] = new Nthread(adder);
}

for(unsigned int i = 0; i < numThreads; ++i)
{
    threads[i]->Join();
    delete threads[i];
}

ASSERT_THAT(numThreads*1000 == *data);

delete data;
delete threads;
END_UNIT

UNIT(cond_test)

unsigned int numThreads = 1000;
unsigned int* data = new unsigned int(0);

pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, AddOne::RunCond, data);
}

sleep(1);
AddOne::m_cond.Broadcast();

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_join(threads[i], 0);
}

ASSERT_THAT(numThreads == *data);

delete threads;
delete data;
END_UNIT



TEST_SUITE(RAII)
TEST(mutex_test)
TEST(guard_test)
TEST(thread_test)
TEST(cond_test)
END_SUITE
