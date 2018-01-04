#include <unistd.h>
#include <stdio.h>

int g_var = 0;

int main()
{
	int n;
	int i;
	int l_var = 0;
	
	n = fork();
	if(n < 0){}
	else if(n > 0)
	{
		for(i = 0; i < 10; ++i)
		{
			++g_var;
			printf("parent g_var: %d\n", g_var);
			++l_var;
			printf("parent l_var: %d\n", l_var);
			sleep(1);
		}
	}
	else
	{
		for(i = 0; i < 10; ++i)
		{
			--g_var;
			printf("daughter g_var: %d\n", g_var);
			--l_var;
			printf("daughter l_var: %d\n", l_var);
			sleep(1);
		}
	}
	return 1;
}
