#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#include "sharedPtr.h"
#include "mu_test.h"

using namespace advcpp;

void* CreadHundredPtr(SharedPtr<int>* _a)
{
    std::vector< SharedPtr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(*_a);
    }
    
    pause();
    
    return 0;
}

void* assignHundredPtr(SharedPtr<int>* _a)
{
    SharedPtr<int> newPtr(new int(0));
    std::vector< SharedPtr<int> > ptrs;
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs.push_back(newPtr);
    }
    
    for(unsigned int i = 0; i < 1000; ++i)
    {
        ptrs[i] = *_a;
    }
    
    pause();
    
    return 0;
}

/*----------------------------------*/

UNIT(COPY_CTOR)

unsigned int numThreads = 1000;
SharedPtr<int> ptr(new int(1));
pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, (void * (*)(void *))CreadHundredPtr, &ptr);
}

sleep(2);

ASSERT_THAT(1000001 == ptr.GetCounter());

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_cancel(threads[i]);
    pthread_join(threads[i], 0);
}

ASSERT_THAT(1 == ptr.GetCounter());

delete threads;

END_UNIT

/*----------------------------------*/

UNIT(null_pointer)

unsigned int numThreads = 1000;

SharedPtr<int> ptr(0);
pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, (void * (*)(void *))CreadHundredPtr, &ptr);
}

sleep(2);

ASSERT_THAT(1000002 == ptr.GetCounter());

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_cancel(threads[i]);
    pthread_join(threads[i], 0);
}

ASSERT_THAT(2 == ptr.GetCounter());

delete threads;

END_UNIT

/*----------------------------------*/

UNIT(assignment_operator)

unsigned int numThreads = 1000;

SharedPtr<int> ptr(new int(1));
pthread_t* threads = new pthread_t[numThreads];
for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_create(threads + i, 0, (void * (*)(void *))assignHundredPtr, &ptr);
}

sleep(2);

ASSERT_THAT(1000001 == ptr.GetCounter());

for(unsigned int i = 0; i < numThreads; ++i)
{
    pthread_cancel(threads[i]);
    pthread_join(threads[i], 0);
}

ASSERT_THAT(1 == ptr.GetCounter());

delete threads;

END_UNIT

/*----------------------------------*/

UNIT(derefrence_operator)

SharedPtr<int> ptr(new int(1));
*ptr = 2;
ASSERT_THAT(2 == *ptr);

END_UNIT

/*----------------------------------*/

UNIT(arrow_operator)

SharedPtr< SharedPtr<int> > ptr(new SharedPtr<int>(new int(1)));
ASSERT_THAT(1 == ptr->GetCounter());

END_UNIT

/*----------------------------------*/

UNIT(operator_safeBool)

SharedPtr<int> a(0);
ASSERT_THAT(!a);

SharedPtr<int> b(new int(1));
ASSERT_THAT(b);

//should not compile
//if((b + 1) == 2) {b + 2}

END_UNIT

UNIT(randStuff)
std::cout << std::cin << std::endl;
END_UNIT
/*----------------------------------*/

UNIT(operator_equal)

SharedPtr<int> a(0);
SharedPtr<int> b = a;

ASSERT_THAT(a == b);

SharedPtr<int> c(new int(0));
ASSERT_THAT(a != c);

END_UNIT

TEST_SUITE(sharedPtr)
TEST(COPY_CTOR)
TEST(null_pointer)
TEST(assignment_operator)
TEST(derefrence_operator)
TEST(arrow_operator)
TEST(operator_safeBool)
TEST(operator_equal)
TEST(randStuff)

END_SUITE
