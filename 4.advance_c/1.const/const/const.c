#include <stdio.h>

void abc1(int const* a, int* b)
{
	*a = 6;
	a = b;
	printf("ghjh %d\n", *a);
}

void abc2(int* const a, int* b)
{
	*a = 6;
	a = b;
	printf("retret %d\n", *a);
}

void abc3(const int* a, int* b)
{
	*a = 6;
	a = b;
	printf("retret %d\n", *a);
}

void abc4(const int* const a, int* b)
{
	*a = 6;
	a = b;
	printf("retret %d\n", *a);
}


int main()
{
	int a = 4;
	int b = 6;
	abc1(&a, &b);
	abc2(&a, &b);
	abc3(&a, &b);
	
	return 1;
}
