#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define MAX_TMP 50
#define MIN_TMP -10
#define NUM_BALAGANERS 5
#define NUM_FIXERS 3

typedef void*(*ThreadFunc)(void*);

typedef struct
{
	pthread_mutex_t m_mutex;
	pthread_mutex_t m_condMutex;
	pthread_cond_t m_cond;
	int m_tmp;
} ThreadData;

void* TempertureChangerFunction(ThreadData* _threadData)
{
	while(TRUE)
	{
		pthread_mutex_lock((&(_threadData->m_mutex)));
		_threadData->m_tmp += (rand() % 3) - 1;
		printf("changer: tmp = %d\n", _threadData->m_tmp);
		pthread_mutex_unlock((&(_threadData->m_mutex)));
		
		if(_threadData->m_tmp < MIN_TMP || _threadData->m_tmp > MAX_TMP)
		{
			pthread_cond_signal(&(_threadData->m_cond));
		}
	}
}

void* TmpFixer(ThreadData* _threadData)
{
	while(TRUE)
	{
		if(pthread_cond_wait(&(_threadData->m_cond), &(_threadData->m_condMutex))< 0)
		{
			perror("cond wait");
			pthread_exit(NULL);
		}
		printf("wok up\n");
		if(_threadData->m_tmp > MAX_TMP)
		{
			while(_threadData->m_tmp > MAX_TMP)
			{
				pthread_mutex_lock((&(_threadData->m_mutex)));
				--_threadData->m_tmp;
				printf("fixer: tmp = %d\n", _threadData->m_tmp);
				pthread_mutex_unlock((&(_threadData->m_mutex))); 
			}
		}
		else
		{
			while(_threadData->m_tmp < MIN_TMP)
			{
				pthread_mutex_lock((&(_threadData->m_mutex)));
				++_threadData->m_tmp;
				printf("fixer: tmp = %d\n", _threadData->m_tmp);
				pthread_mutex_unlock((&(_threadData->m_mutex))); 
			}
		}
	} 
}





int main()
{
	int i, j, status;
	ThreadData data;
	pthread_t balaganers[NUM_BALAGANERS + NUM_FIXERS];
	
	data.m_tmp = 10;
	pthread_mutex_init(&(data.m_mutex), NULL);
	pthread_mutex_init(&(data.m_condMutex), NULL);
	pthread_cond_init(&(data.m_cond), NULL);
	
	for(i = 0; i < NUM_FIXERS; ++i)
	{
		if(0 != pthread_create(&(balaganers[i]), NULL, (ThreadFunc)TmpFixer, &data))
		{
			perror("thread create");
		}
	}
	for(j = 0; j < NUM_BALAGANERS; ++j)
	{
		if(0 != pthread_create(&(balaganers[i + j]), NULL, (ThreadFunc)TempertureChangerFunction, &data))
		{
			perror("thread create");
		}
	}
	status = pthread_join(balaganers[0] ,NULL);
	if(status != 0)
	{
		printf("%d thread join failed\n", status);
	}
	return 1;
}
