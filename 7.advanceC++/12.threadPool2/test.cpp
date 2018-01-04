#include <iostream>
#include <tr1/memory>
#include <unistd.h>

#include "threadPool.h"
#include "mu_test.h"
#include "atomicOperations"
#include "nthread.h"

using namespace advcpp;

class Here
{
public:
    Here(unsigned int* _data): m_data(_data){}
    void Run()
    {
        AtomicAdd(m_data, 1);
    }
    unsigned int* m_data;
};

class Infinit
{
public:
    void Run()
    {
        while(true)
        {
            sleep(1);
        }
    }
};

/*-------------------------------------*/

UNIT(THREADS)

unsigned int a = 5;
Nthread<Here> imHere(std::tr1::shared_ptr<Here>(new Here(&a)), &Here::Run);

imHere.Join();

ASSERT_THAT(1);

END_UNIT

/*-------------------------------------*/

UNIT(thread_pool)

unsigned int numTasks = 500;

ThreadPool pool(5);
unsigned int data = 0;

std::tr1::shared_ptr<Here> here(new Here(&data));
for(unsigned int i = 0; i < numTasks; ++i)
{
    pool.AddTask(here, &Here::Run, 5);
}
sleep(1);

ASSERT_THAT(numTasks == data);

pool.GracefullShutDown();

/*-------------------------------------*/

END_UNIT

UNIT(bruteShutDown)

unsigned int numTasks = 3;

ThreadPool pool(5);

std::tr1::shared_ptr<Infinit> inf(new Infinit);
for(unsigned int i = 0; i < numTasks; ++i)
{
    pool.AddTask(inf, &Infinit::Run, 5);
}

//pool.GracefullShutDown();
pool.BruteShutDown();

END_UNIT

/*-----------------------------------*/

UNIT(fullySafeShutDown)

unsigned int numTasks = 5000;

for(unsigned int j = 0; j < 1000; ++j)
{
    ThreadPool pool(50);
    unsigned int data = 0;

    std::tr1::shared_ptr<Here> here(new Here(&data));
    for(unsigned int i = 0; i < numTasks; ++i)
    {
        pool.AddTask(here, &Here::Run, 5);
    }

    pool.FullyGracefullShutDown();

    ASSERT_THAT(numTasks == data);
}

END_UNIT

/*--------------------------*/

UNIT(insert_task_after_shut_down)

unsigned int data = 0;
ThreadPool pool(5);

pool.FullyGracefullShutDown();

try
{
    std::tr1::shared_ptr<Here> here(new Here(&data));
    pool.AddTask(here, &Here::Run, 5);
    ASSERT_THAT(1);
}
catch(std::runtime_error& _er){}

END_UNIT

/*-------------------------------------*/

TEST_SUITE(MEM-POOL)

TEST(THREADS)
TEST(thread_pool)
TEST(bruteShutDown)
TEST(fullySafeShutDown)
TEST(insert_task_after_shut_down)

END_SUITE
