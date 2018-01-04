#include <pthread.h>
#include <stdio.h>

#define NUM_OF_THREADS 10

int g_var = 0;
int colorIdx = 0;

void* PrintFunk(void* tid)
{
	int i;
	int l_var = 0;
	for(i = 0; i < 1000; ++i)
	{
		++l_var;
		++g_var;
		printf(" %d) thread: l_var: %d g_var: %d\n", (int)tid, l_var, g_var);
	}
	pthread_exit(NULL);
}

int main()
{
	int i;
	int status = 0;
	pthread_t threads[NUM_OF_THREADS];
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&threads[i], NULL, PrintFunk, (void*) i);
		if(status != 0)
		{
			printf("an error has accured at thread %d\n", i);
		}
	}
	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_join(threads[i] ,NULL);
		if(status != 0)
		{
			printf("thread join failed\n");
		}
	}
	return 1;
}
