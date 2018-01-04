#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "message.h"

typedef struct
{
	size_t m_sleepTime;
	int m_ftocFlag;
	int m_verbosity;
	int m_create;
	int m_destroy;
	
} InputData;

/*--------------------------------------*/

void PongFunction(InputData* _data)
{
	int msgQId;
	size_t count = 0;
	msgStruct reciveMsg;
	char answer[] = "got it! :)";
	
	msgQId = CreateMsgQ(_data->m_ftocFlag);
	if(-1 == msgQId)
	{
		perror("get message queue\n");
	}
	
	for(;;)
	{
		/*get messgage from client*/
		if(msgRecive(msgQId, -AUXILERY_PORT, 0, &reciveMsg) < 0)
		{
			perror("msg recive");
		}
		/*if end of file reached*/
		if(AUXILERY_PORT == reciveMsg.m_type)
		{
			if(_data->m_destroy)
			{
				DestroyMsgQ(msgQId);
			}
			exit(1);
		}
		/*print message*/
		if(_data->m_verbosity)
		{
			printf("pong recived message: %s, from: %d\n", reciveMsg.m_info.m_data, reciveMsg.m_info.m_pid);
		}
		
		usleep(_data->m_sleepTime);
		
		/*send message to the client*/
		if(MsgSend(msgQId, RECIVER_PORT, answer) < 0)
		{
			perror("msg send");
		}
		if(_data->m_verbosity)
		{
			printf("pong sent back message\n");
		}
		++count;
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
				_input->m_sleepTime = (size_t)atoi(optarg);
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
				return;
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
