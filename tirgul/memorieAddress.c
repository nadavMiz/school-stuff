#include <stdio.h>
#include <stdlib.h>

static size_t g_char[999999];
static size_t g_char1[999999];

int func()
{
	int stack = 5;
	printf("stack: %p\n", &stack);
	return 1;
}

int main()
{
	int stack = 5;
	int* heap = malloc(sizeof(int));
	
	printf("main: %p\n", &stack);
	func();
	printf("heap: %p\n", heap);
	printf("global: %p\n", g_char1);
	printf("code: %p\n", func);
	
	return 0;
}
