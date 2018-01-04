#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h> /*semaphore*/
#include <string.h> /*strcpy*/

#include "message.h"

#define MESSAGE_SIZE 30

typedef struct
{
	size_t m_loops;
	unsigned int m_sleepTime;
	int m_ftocFlag;
	int m_verbosity;
	char m_semName[MESSAGE_SIZE];
} InputData;

/*-------------------------------------------*/

static void getOneLetterStr(char* _dest, size_t _numLetters)
{
	static char letter = 'A';
	
	size_t i;
	
	assert(_numLetters < MAX_MSG_SIZE);
	
	for(i = 0; i < _numLetters; ++i)
	{
		_dest[i] = letter;
	}
	_dest[i] = '\0';
	
	++letter;
}

/*--------------------------------------------*/

static void SendMsg(int _msgQId, int _isVerbosity)
{
	char msg[MAX_MSG_SIZE];
	
	/* send message to the server */
	getOneLetterStr(msg, MESSAGE_SIZE);
	if((int)MsgSend(_msgQId, WRITER_PORT, msg) < 0)
	{
		perror("send message");
	}
	if(_isVerbosity)
	{
		printf("ping sent message %s\n", msg);
	}
}

static void ReadMsg(int _msgQId, int _isVerbosity)
{
	msgStruct msg;
	
	/*recive answer from the server*/
	if(msgRecive(_msgQId, RECIVER_PORT, 0, &msg) < 0)
	{
		perror("msg recive");
	}
	if(_isVerbosity)
	{
		printf("ping recived answer: %s, from: %d\n", msg.m_info.m_data, msg.m_info.m_pid);
	}
}

static void PingFunction(InputData* _data)
{
	int msgQId;
	size_t i;
	sem_t* pingCount;
	
	/*get the message queue*/
	msgQId = GetMsgQ(_data->m_ftocFlag);
	if(-1 == msgQId)
	{
		perror("get message queue\n");
		exit(1);
	}
	
	/*increment semaphore so pong know you are here*/
	pingCount = sem_open(_data->m_semName, 0);
	if(SEM_FAILED == pingCount)
	{
		perror("get semaphore");
		exit(1);
	}
	sem_post(pingCount);
	
	/*send and recive messages*/
	for(i = 0; i < _data->m_loops; ++i)
	{
		SendMsg(msgQId, _data->m_verbosity);
		usleep(_data->m_sleepTime);
		ReadMsg(msgQId, _data->m_verbosity);
	}
	
	/*tell pong that the process stoped sending messages*/
	sem_wait(pingCount);
	sem_close(pingCount);
	if(MsgSend(msgQId, AUXILIARY_PORT, "end") < 0)
	{
		perror("send message");
	}
}

/*-----------------------------------------------*/

static void ReadInput(int _argc, char** _argv, InputData* _input)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "s:l:f:n:v?")) != -1)
	{
		switch(opt)
		{
			case 's':
				_input->m_sleepTime = (unsigned int)atoi(optarg);
				break;
			case 'l':
				_input->m_loops = (size_t)atoi(optarg);
				break;
			case 'f':
				_input->m_ftocFlag = atoi(optarg);
				break;
			case 'v':
				_input->m_verbosity = 1;
				break;
			case 'n':
				strcpy(_input->m_semName, optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)] \
				[-l number of loops] [-v verbosity] [-n semaphore name]\n", _argv[0]);
				return;
	 	}
	}
}

int main(int argc, char* argv[])
{
	InputData data = {3, SECOND, 'A', 0, "/sem"};
	
	ReadInput(argc, argv, &data);
	PingFunction(&data);
	
	return 1;
}
