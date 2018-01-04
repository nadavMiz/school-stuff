#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> /*waitpid*/
#include <sys/wait.h>  /*waitpid*/

void getOneLetterStr(char* _dest, size_t _numLetters)
{
	static char letter = 'A';
	
	size_t i;
	for(i = 0; i < _numLetters; ++i)
	{
		_dest[i] = letter;
	}
	_dest[i] = '\0';
	
	++letter;
}

void ProducerFunction(size_t _bufferSize, int _loops, int _pfds[2])
{
	int i;
	char* word = malloc(_bufferSize * sizeof(char));
	
	close(_pfds[0]);
	
	for(i = 0; i < _loops; ++i)
	{
		getOneLetterStr(word, _bufferSize - 1);
		write(_pfds[1], word, _bufferSize);
	}
	close(_pfds[1]);
	printf("producer: all messeges sent.\n");
	free(word);
}

/*--------------------------------------------------------*/

void ConsumerFunction(size_t _bufferSize, int _pfds[2])
{
	char* buffer = malloc(_bufferSize * sizeof(char));
	
	close(_pfds[1]);
	for(;;)
	{
		sleep(1);
		if(0 == read(_pfds[0], buffer, _bufferSize))
		{
			printf("consumer: end of file reached. exit process\n");
			free(buffer);
			exit(1);
		}
		printf("%s", buffer);
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	extern char *optarg;
	int opt, status, pid;
	int pfds[2];
	size_t bufferSize = 32;
	int loops = 3;
	
	/*read input*/
	while ((opt = getopt(argc, argv, "b:l:")) != -1)
	{
		switch(opt)
		{
			case 'b':
				bufferSize = (size_t)atoi(optarg);
				break;
			case 'l':
				loops = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-b Buffer size] [-l loops = number of loops]\n", argv[0]);
				return 1;
	 	}
	}
	
	/*build the pipe*/
	pipe(pfds);
	/*make new process and run it*/
	pid = fork();
	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid > 0)
	{
		ProducerFunction(bufferSize, loops, pfds);
		waitpid(pid, &status, 0);
	}
	else
	{
		ConsumerFunction(bufferSize, pfds);
	}
	return 0;
}
