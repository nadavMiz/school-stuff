#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void * ThreadFunction1(void *arg)
{
	puts("Hello world from thread1\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("1");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread 1\n");
	return(NULL);
}

void * ThreadFunction2(void *arg)
{
	puts("Hello world from thread2\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("2");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread 2\n");
	return(NULL);
}

void * ThreadFunction3(void *arg)
{
	puts("Hello world from thread1\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("3");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread 3\n");
	return(NULL);
}

void * ThreadFunction4(void *arg)
{
	puts("Hello world from thread2\n");
	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("4");
		fflush(stdout);
	}
		printf("\n");
	puts("Exiting thread 4\n");
	return(NULL);
}

int main()
{
	int Rc;
	pthread_t Thread1,Thread2,Thread3,Thread4;
	void * Arg = NULL;
	puts("Hello world\n");
	puts("CreatingThread 1\n");
	Rc = pthread_create(&Thread1, NULL, ThreadFunction1, Arg);
	puts("Thread 1 Created\n");
	printf("Rc from pthread_create is %i \n", Rc);
	printf("pthread_t is %lu \n", Thread1);
	puts("CreatingThread 2\n");
	Rc = pthread_create(&Thread2, NULL, ThreadFunction2, Arg);
	puts("Thread 2 Created\n");
	printf("Rc from pthread_create is %i \n", Rc);
	printf("pthread_t is %lu \n", Thread1);
	puts("CreatingThread 3\n");
	Rc = pthread_create(&Thread3, NULL, ThreadFunction3, Arg);
	puts("Thread 3 Created\n");
	printf("Rc from pthread_create is %i \n", Rc);
	printf("pthread_t is %lu \n", Thread1);
	puts("CreatingThread 4\n");
	Rc = pthread_create(&Thread4, NULL, ThreadFunction4, Arg);
	puts("Thread 4 Created\n");
	printf("Rc from pthread_create is %i \n", Rc);
	printf("pthread_t is %lu \n", Thread1);

	for (int i = 0; i<500; i++) {
		sleep(1);
		printf("*");
		fflush(stdout);
	}
		printf("\n");
	puts("Press ENTER to exit\n");
	getchar();
	puts("Exiting Program\n");
	return 0;
}
