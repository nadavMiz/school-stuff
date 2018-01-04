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

/*--------------------------------------------*/

static void SendMsg(int _msgQId, int _isVerbosity)
{
	char msg[MAX_MSG_SIZE];
	
	/* send message to the server */
	getOneLetterStr(msg, MESSAGE_SIZE);
	if(MsgSend(_msgQId, WRITER_PORT, msg) < 0)
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
	char RegisterMsg[] = "REGISTER";
	msgStruct tmp;
	
	/*get the message queue*/
	msgQId = GetMsgQ(_data->m_ftocFlag);
	if(-1 == msgQId)
	{
		perror("create message queue\n");
	}
	
	/*register at auxilery pipe so reciver know process is sending*/
	MsgSend(msgQId, AUXILERY_PORT, RegisterMsg);
	
	/*send and recive messages*/
	for(i = 0; i < _data->m_loops; ++i)
	{
		SendMsg(msgQId, _data->m_verbosity);
		usleep(_data->m_sleepTime);
		ReadMsg(msgQId, _data->m_verbosity);
	}
	
	/*unregister at auxilery pipe so reciver know process stoped sending messages*/
	msgRecive(msgQId, AUXILERY_PORT, 0, &tmp);
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
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)] [-l number of loops] [-v verbosity]\n", _argv[0]);
				return;
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
