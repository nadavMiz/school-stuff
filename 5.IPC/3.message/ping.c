#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

#include "message.h"

#define MESSAGE_SIZE 30

typedef struct
{
	size_t m_loops;
	size_t m_sleepTime;
	int m_ftocFlag;
	int m_verbosity;
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

/*---------------------------------------------*/

static void PingFunction(InputData* data)
{
	int msgQId;
	size_t i;
	char SendMsg[MAX_MSG_SIZE];
	msgStruct reciveMsg;
	
	/*get the message queue*/
	msgQId = GetMsgQ(data->m_ftocFlag);
	if(-1 == msgQId)
	{
		perror("create message queue\n");
	}
	
	for(i = 0; i < data->m_loops; ++i)
	{
		/* send message to the server */
		getOneLetterStr(SendMsg, MESSAGE_SIZE);
		if(MsgSend(msgQId, WRITER_PORT, SendMsg) < 0)
		{
			perror("msg send");
		}
		if(data->m_verbosity)
		{
			printf("ping sent message %s\n", SendMsg);
		}
		
		usleep(data->m_sleepTime);
		
		/*recive answer from the server*/
		if(msgRecive(msgQId, RECIVER_PORT, 0, &reciveMsg))
		{
			perror("recive msg");
		}
		if(data->m_verbosity)
		{
			printf("ping recived answer: %s, from: %d\n", reciveMsg.m_info.m_data, reciveMsg.m_info.m_pid);
		}
	}
	
	/*send end of file*/
	MsgSend(msgQId, AUXILERY_PORT, SendMsg);
}

/*-----------------------------------------------*/

static void ReadInput(int _argc, char** _argv, InputData* _input)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "s:l:f:v?")) != -1)
	{
		switch(opt)
		{
			case 's':
				_input->m_sleepTime = (size_t)atoi(optarg);
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
			default:
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)] [-l number of loops] [-v verbosity] \n", _argv[0]);
				exit(1);
	 	}
	}
}

int main(int argc, char* argv[])
{
	InputData data = {3, SECOND, 'A', 0};
	
	ReadInput(argc, argv, &data);
	PingFunction(&data);
	
	return 1;
}
