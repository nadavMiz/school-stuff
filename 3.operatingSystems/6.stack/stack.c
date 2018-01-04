#include <stdio.h>

void* g_mainRet;

void Hack(int a)
{
	int* itr = (void*)(&a);
	printf("i'm in hack function ;)\n");
	itr -= 1;
	*((void**)itr) = g_mainRet;
}

void myfunc(int a, int b)
{
	char* start = (char*)(&b);
	int k = -5;
	printf("im in function myfunc\n");
	printf("adress of b: %p, value of b: %d\n", start, *((int*)(start)));
	start -= sizeof(int);
	printf("adress of a: %p, value of a: %d\n", start, *((int*)(start)));
	start -= sizeof(int);
	printf("adress of ret: %p, value of ret: %p\n", start, *((void**)(start)));
	
	/*hack the stack*/
	g_mainRet = *((void**)start);
	*((void**)start) = (void*)Hack;
	
	start -= sizeof(size_t);
	printf("adress of ebp: %p, value of ebp: %p\n", start, *((void**)(start)));
	start -= sizeof(size_t);
	printf("adress canari 1: %p, value of canari 1: %p\n", start, *((void**)(start)));
	start -= sizeof(size_t);
	printf("adress canari 2: %p, value of canari 2: %p\n", start, *((void**)(start)));
	start -= sizeof(size_t);
	printf("adress of k: %p, value of k: %d\n", start, *((int*)(start)));
	
}

void foo(int a, int b)
{
	char* start = (char*)(&b);
	start -= 2*sizeof(int);
	/*hack the stack*/
	g_mainRet = *((void**)start);
	*((void**)start) = (void*)Hack;
}

/*------------------------------------------*/

int main()
{
	int mainVal = 3;
	printf("adress in main: %p\n", &mainVal);
	myfunc(1, 5);
	printf("back to main\n");
}
