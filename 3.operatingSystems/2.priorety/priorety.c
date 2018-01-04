#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h> 

int main()
{
	int i;
	int a;
	int status;
	a = fork();
	if(a == 0)
	{
		for(i = 0; i < 30; ++i)
		{
			printf("%d",i);
			sleep(1);
		}
		nice(10);
		for(i = 0; i < 30; ++i)
		{
			printf("%d",i);
			sleep(1);
		}
	}
	if(a > 0)
	{
		waitpid(-1, &status, 0);;
	}
	return 1;
}
