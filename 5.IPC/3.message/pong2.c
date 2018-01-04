#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/msg.h>

#include "message.h"

typedef struct
{
	size_t m_sleepTime;
	int m_ftocFlag;
	int m_verbosity;
	int m_create;
	int m_destroy;
	
} InputData;

/*---------------------------------------*/

static int GetMsgQId(int _isCreate, int _flag)
{
	int msgQId;
	
	if(_isCreate)
	{
		msgQId = CreateMsgQ(_flag);
		if(-1 == msgQId)
		{
			perror("get message queue\n");
			exit(1);
		}
	}
	else
	{
		msgQId = GetMsgQ(_flag);
		if(-1 == msgQId)
		{
			perror("get message queue\n");
			exit(1);
		}
	}
	return msgQId;
}

/*---------------------------------------*/

static void ReadData(int _msgQId, InputData* _data)
{
	static int firstTime = 1;
	msgStruct reciveMsg;
	int error;
	
	/*get messgage from client*/
	if(firstTime)
	{
		error = msgRecive(_msgQId, -AUXILERY_PORT, 0, &reciveMsg);
		firstTime = 0;
	}
	else
	{
		error = msgRecive(_msgQId, -AUXILERY_PORT, IPC_NOWAIT, &reciveMsg);
	}
	/*END OF WORLD REACHED*/
	if(error < 0)
	{
		if(errno == ENOMSG)
		{
			if(_data->m_destroy)
			{
				DestroyMsgQ(_msgQId);
			}
			exit(1);
		}
		perror("msg recive");
	}
	
	/*print message*/
	if(_data->m_verbosity)
	{
		printf("pong recived message: %s, from: %d\n", reciveMsg.m_info.m_data, reciveMsg.m_info.m_pid);
	}
	
	/*if got REGISTER msg*/
	if(AUXILERY_PORT == reciveMsg.m_type)
	{
		if(MsgSend(_msgQId, AUXILERY_PORT, reciveMsg.m_info.m_data) < 0)
		{
			perror("send message");
		}
	}
}

/*--------------------------------------*/

static void SendData(int _msgQId, int _isVerbosity)
{
	static char answer[] = "got it! :)";
	
	/*send message to the client*/
	if(MsgSend(_msgQId, RECIVER_PORT, answer) < 0)
	{
		perror("send message");
	}
	if(_isVerbosity)
	{
		printf("pong sent back message\n");
	}
}

/*--------------------------------------*/

static void PongFunction(InputData* _data)
{
	int msgQId;
	
	msgQId = GetMsgQId(_data->m_create, _data->m_ftocFlag);
	
	for(;;)
	{
		
		ReadData(msgQId, _data);
		usleep(_data->m_sleepTime);
		SendData(msgQId, _data->m_verbosity);
	}
}

/*-----------------------------------------*/

static void ReadInput(int _argc, char** _argv, InputData* _input)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "s:f:vcd?")) != -1)
	{
		switch(opt)
		{
			case 's':
				_input->m_sleepTime = THOUSEND * (size_t)atoi(optarg);
				break;
			case 'f':
				_input->m_ftocFlag = atoi(optarg);
				break;
			case 'v':
				_input->m_verbosity = 1;
				break;
			case 'c':
				_input->m_create = 1;
				break;
			case 'd':
				_input->m_destroy = 1;
				break;
			default:
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)]\n", _argv[0]);
				exit(1);
	 	}
	}
}


int main(int argc, char* argv[])
{
	InputData input = {SECOND, 'A', 0, 0, 0};
	
	ReadInput(argc, argv, &input);
	PongFunction(&input);
	return 1;
}
