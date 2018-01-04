#include <stdio.h>

typedef struct
{
	char a;
	int  b;
	char c;
	int d;
	char e;
	
}	a_t;

typedef struct
{
	char a;
	char b;
	char c;
	char d;
	int h;
	int f;
} b_t;

void printDaBits(int _num)
{
	int a = 1 << (8 * sizeof(int) - 2);
	size_t i;
	for(i = (8 * sizeof(int) - 1); i > 0; --i)
	{
		printf("%d", (_num & a) >> (i-1));
		a = a >> 1;
	}
	printf("\n");
}

int main()
{
	printDaBits(-3);
	return 1;
}

