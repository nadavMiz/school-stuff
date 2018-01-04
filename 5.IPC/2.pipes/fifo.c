#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>  /*waitpid*/

#define FIFO_NAME "nadav"

void getOneLetterStr(char* _dest, size_t _numLetters)
{
	char letter = 'A';
	
	size_t i;
	for(i = 0; i < _numLetters; ++i)
	{
		_dest[i] = letter;
	}
	_dest[i] = '\0';
}

void ClientFunction(size_t _bufferSize, size_t _loops)
{
	int fifo;
	size_t i;
	char* word = malloc(_bufferSize * sizeof(char));
	
	fifo = open(FIFO_NAME, O_WRONLY);
	getOneLetterStr(word, _bufferSize - 1);
	
	for(i = 0; i < _loops; ++i)
	{
		write(fifo, word, _bufferSize);
	}
	close(fifo);
	printf("client: all messeges sent.\n");
	free(word);
}

/*---------------------------------*/

void ServerFunction(size_t _bufferSize)
{
	int fifo;
	char* buffer = malloc(sizeof(char) * _bufferSize);
	
	
	if(-1 == mkfifo(FIFO_NAME ,S_IRUSR| S_IWUSR| S_IFIFO))
	{
		perror("mkfifo");
	}
	
	fifo = open(FIFO_NAME, O_RDONLY);
	
	for(;;)
	{
		sleep(1);
		if(0 == read(fifo, buffer, _bufferSize))
		{
			/*exit process*/
			printf("server: end of file reached. exit process\n");
			close(fifo);
			remove(FIFO_NAME);
			free(buffer);
			exit(1);
		}
		printf("messege recived: %s\n", buffer);
	}
}

/*-----------------------------------------------------------------*/

void ReadInput(int _argc, char** _argv, char* _type, size_t* _loops, size_t* _bufferSize)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "l:t:")) != -1)
	{
		switch(opt)
		{
			case 't':
				*_type = optarg[0];
				break;
			case 'l':
				*_loops = (size_t)atoi(optarg);
				break;
			case 'b':
				*_bufferSize = (size_t)atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)]\n", _argv[0]);
				return;
	 	}
	}
}

int main(int argc, char *argv[])
{
	extern char *optarg;
	char type = 'c';
	size_t loops = 3;
	size_t bufferSize = 32;
	
	ReadInput(argc, argv, &type, &loops, &bufferSize);
	/*build the pipe*/
	if('s' == type)
	{
		ServerFunction(bufferSize);
	}
	else
	{
		ClientFunction(bufferSize, loops);
	}
}
