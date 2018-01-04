#include <stdio.h>

#define DATA_BUFFER 10

void getUserData()
{
	size_t i;
	char data[DATA_BUFFER];
	for(i = 0; i < 5; ++i)
	{
		scanf("%s\n", data);
		printf("echo: %s\n", data);
	}
}

int main()
{
	getUserData();
	printf("returned to main\n");
	return 1;
}
