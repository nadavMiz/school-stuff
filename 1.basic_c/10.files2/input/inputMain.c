#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

int main(int argc, char* argv[])
{
	char* age;
	char* name;
	if(3 != argc)
	{
		printf("incorrect number of argument\n");
		return 0;
	}
	if (isdigit(argv[1][0]))
	{
		age = argv[1];
		name = argv[2];
	}
	else
	{
		age = argv[2];
		name = argv[1];
	}
	if(CheckInput(name, age))
	{
		
		printf("%s, %d\n", name, atoi(age));
		return 1;
	}
	printf("invalid input\n");
	return 0;
} 
