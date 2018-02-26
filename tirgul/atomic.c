#include <pthread.h>
#include <stdio.h>

typedef struct
{
	int m_lock;
} spinlock;

typedef struct
{
	spinlock m_lock;
	int m_num;
} Context;

void lock(spinlock* _lock)
{
	while(!__sync_bool_compare_and_swap(&_lock->m_lock, 1, 0)){}
}

void unlock(spinlock* _lock)
{
	__sync_val_compare_and_swap(&_lock->m_lock, 0, 1);
}

void* threadFunc(Context* _context)
{
	for(int i = 0; i < 10000; ++i)
	{
		lock(&_context->m_lock);
		++(_context->m_num);
		unlock(&_context->m_lock);
	}
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	Context context;
	context.m_num = 0;
	context.m_lock.m_lock = 1;
	
	pthread_create(&thread1, NULL, (void*(*)(void*))threadFunc, &context);
	pthread_create(&thread2, NULL, (void*(*)(void*))threadFunc, &context);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", context.m_num);
}
