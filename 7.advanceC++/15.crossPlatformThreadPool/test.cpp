#include <iostream>
#ifdef __linux__
#include <tr1/memory>
#include <unistd.h>
#elif WIN32
#include <memory>
#endif

#include "threadPool.h"
#include "mu_test.h"
#include "atomicOperations.h"
#include "nthread.h"

using namespace advcpp;
using namespace advcpp::sync;

class Here
{
public:
    Here(int& _data): m_data(_data){}
    void Run()
    {
        AtomicAdd(m_data, 1);
    }
    int& m_data;
};

class Infinit
{
public:
    void Run()
    {
        while(true)
        {
			#ifdef __linux__
            sleep(1);
			#elif defined WIN32
			Sleep(1000);
			#endif
        }
    }
};

/*-------------------------------------*/

UNIT(THREADS)

int a = 5;
Nthread<Here> imHere(std::tr1::shared_ptr<Here>(new Here(a)), &Here::Run);

imHere.Join();

ASSERT_THAT(1);

END_UNIT

/*-------------------------------------*/

UNIT(thread_pool)

int numTasks = 500;

ThreadPool pool(5);
int data = 0;

std::tr1::shared_ptr<Here> here(new Here(data));
for(int i = 0; i < numTasks; ++i)
{
    pool.AddTask(here, &Here::Run, 5);
}
#ifdef __linux__
sleep(1);
#elif defined WIN32
Sleep(1000);
#endif

ASSERT_THAT(numTasks == data);

pool.GracefullShutDown();

END_UNIT

/*-----------------------------------*/

UNIT(fullySafeShutDown)

int numTasks = 1000;

for(unsigned int j = 0; j < 1; ++j)
{
    ThreadPool pool(10);
    int data = 0;

    std::tr1::shared_ptr<Here> here(new Here(data));
    for(int i = 0; i < numTasks; ++i)
    {
        pool.AddTask(here, &Here::Run, 5);
    }

    pool.FullyGracefullShutDown();

    ASSERT_THAT(numTasks == data);
}

END_UNIT

/*--------------------------*/

UNIT(insert_task_after_shut_down)

int data = 0;
ThreadPool pool(5);

pool.FullyGracefullShutDown();

try
{
    std::tr1::shared_ptr<Here> here(new Here(data));
    pool.AddTask(here, &Here::Run, 5);
    ASSERT_THAT(1);
}
catch(std::runtime_error& _er){}

END_UNIT

/*-------------------------------------*/

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

/*-------------------------------------*/

TEST_SUITE(MEM-POOL)

TEST(THREADS)
TEST(thread_pool)
TEST(fullySafeShutDown)
TEST(insert_task_after_shut_down)
TEST(bruteShutDown)


END_SUITE
