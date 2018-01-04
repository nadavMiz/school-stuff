#include <unistd.h>
#include <iostream>
#include <queue>

#include "nPrioretyQueue.h"
#include "mu_test.h"
#include "threadable.h"
#include "nthread.h"
#include "threadPool.h"


using namespace advcpp;

const unsigned int NUM_LOOPS = 1000;

class AddEvent: public Threadable
{
public:

    AddEvent(nPrioretyQueue<char>& _queue): m_queue(_queue) {}
    
    void RunThread() 
    {
        for(unsigned int i = 0; i < NUM_LOOPS; ++i)
        {
            m_queue.Push('a');
        }
    }
    
    nPrioretyQueue<char>& m_queue;
};

class RemoveEvent: public Threadable
{
public:

    RemoveEvent(nPrioretyQueue<char>& _queue): m_queue(_queue) {}
    
    void RunThread() 
    {
        for(unsigned int i = 0; i < NUM_LOOPS; ++i)
        {
            m_queue.Pop();
        }
    }
    
    nPrioretyQueue<char>& m_queue;
};

class TaskAdder: public Threadable
{
public:

    TaskAdder(ThreadPool& _pool): m_pool(_pool) {}
    
    void RunThread() 
    {
        for(unsigned int i = 0; i < NUM_LOOPS; ++i)
        {
            Threadable* threadClass = new TaskAdder(m_pool);
            std::tr1::shared_ptr<Task> task(new Task(threadClass, i));
            m_pool.AddTask(task);
        }
    }
    
    ThreadPool& m_pool;
};

class Here: public Threadable
{
public:
    Here(unsigned int* _data): m_data(_data){}
    void RunThread() 
    {
        Guard guard(m_mutex);
        ++(*m_data);
    }
    
    unsigned int* m_data;
    Nmutex m_mutex;
};

UNIT(NP_QUEUE)
nPrioretyQueue<char> queue;

unsigned int add = 500;
unsigned int sub = 200;
Nthread** threads = new Nthread*[add + sub];

RemoveEvent subtructor(queue);
for(unsigned int i = 0; i < sub; ++i)
{
    threads[i] = new Nthread(subtructor);
}

AddEvent addator(queue);
for(unsigned int i = 0; i < add; ++i)
{
    threads[sub + i] = new Nthread(addator);
}

for(unsigned int i = 0; i < add + sub; ++i)
{
    threads[i]->Join();
    delete threads[i];
}

ASSERT_THAT((add - sub)*NUM_LOOPS == queue.Size());

delete threads;
END_UNIT

typedef std::tr1::shared_ptr<Task> taskPtr;

UNIT(ThreadPool_Add)
const unsigned int numThreads = 100;
Nthread** threads = new Nthread*[numThreads];

ThreadPool pool(0);
Threadable* addator = new TaskAdder(pool);
std::tr1::shared_ptr<Task> current(new Task(addator, 1));

for(unsigned int i = 0; i < numThreads; ++i)
{
    threads[i] = new Nthread(*addator);
}

for(unsigned int i = 0; i < numThreads; ++i)
{
    threads[i]->Join();
    delete threads[i];
}

for(unsigned int i = 0; i < NUM_LOOPS; ++i)
{
    for(unsigned int j = 0; j < numThreads; ++j)
    {
        current = (pool.GetQueue()).Pop();
        ASSERT_THAT(NUM_LOOPS - i - 1 == (*current).GetPriority());
    }
    
}
delete threads;

END_UNIT

UNIT(thread_pool)

unsigned int numTasks = 50;

ThreadPool pool(5);
unsigned int data = 0;

Threadable* here = new Here(&data);
std::tr1::shared_ptr<Task> current(new Task(here, 1));
for(unsigned int i = 0; i < numTasks; ++i)
{
    pool.AddTask(current);
}
sleep(1);

ASSERT_THAT(numTasks == data);

END_UNIT

TEST_SUITE(MEM-POOL)
TEST(NP_QUEUE)
TEST(ThreadPool_Add)
TEST(thread_pool)
END_SUITE
