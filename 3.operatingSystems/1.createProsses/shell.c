#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h> 

#define LINE_LENGTH 128
#define MAX_PARAMATERS 64

/*---------------static function----------------------*/

static void ReadCommend(char* _commend,char** _paramaters)
{
	int i = 0;
	char* token;
	char delim[] = " \t\n";
	fgets(_commend, LINE_LENGTH, stdin);
	token = strtok(_commend ,delim);
	if(NULL == token)
	{
		_paramaters[i] = NULL;
		return;
	}	
	while(token != NULL)
	{
		_paramaters[i] = token;
		token = strtok(NULL, delim);
		++i;
	}
	_paramaters[i] = NULL;
}

/*----------------main functions--------------------*/

void GetCommend()
{
	int pad;
	int status;
	char commend[LINE_LENGTH] = "";
	char* paramaters[MAX_PARAMATERS];
	
	while(1)
	{
		printf("myShell:");
		ReadCommend(commend, paramaters);
		if(strcmp(commend, "exit") == 0)
			{
				return;	
			}
		pid = fork();
		if(pid != 0)
		{
			/*parent code*/
			waitpid(-1, &status, 0);
		}
		else
		{
			/*child code*/
			execvp(commend, paramaters);
			printf("%s: command not found\n", commend);
			exit(EXIT_FAILURE);
		}
		
	}
}

int main()
{
	GetCommend();
	return 1;
}
