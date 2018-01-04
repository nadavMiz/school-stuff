#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* MyThread(void* tid)
{
	int l_var;
	printf("thread %d address: %p\n",(int)tid, (void*)&l_var);
	while(1);
	pthread_exit(NULL);
	
}

int main()
{
	/* malloc */
	/*
	int count = 1;
	char* a = malloc(1024 * 1024 * sizeof(char));
	while(NULL != a)
	{
		a = malloc(1024 * 1024 * sizeof(char));
		++count;
	}
	printf("number of mallocs: %d\n", count);
	return 1; */
	
	
	/* threads */
	/*
	int threadNum = 0;
	int status = 0;
	pthread_t thread[1];
	while(status == 0)
	{
		status = pthread_create(&thread[0], NULL, MyThread, (void*) threadNum);
		++threadNum;
	}
	sleep(1);
	printf("num of threads: %d\n", threadNum);
	*/
	return 1;
}
