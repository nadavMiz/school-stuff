#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <stdio.h> /*printf, perror*/
#include <sys/socket.h> /* messages */
#include <errno.h> /* errno */
#include <sys/stat.h> /* semaphore */
#include <semaphore.h> /* semaphore */
#include <sys/msg.h> /* IPC_NOWAIT */
#include <string.h> /* strcpy */

#include "message.h"

#define NAME_LENGTH 16

typedef struct
{
	unsigned int m_sleepTime;
	int m_ftocFlag;
	int m_verbosity;
	int m_create;
	int m_destroy;
	char m_semName[NAME_LENGTH];
	
} InputData;

/*---------------------------------------*/

void exitProcess(int _msgQId, sem_t* _pingSemaphore, InputData* _data)
{
	if(_data->m_destroy)
	{
		DestroyMsgQ(_msgQId);
	}
	sem_close(_pingSemaphore);
	sem_unlink(_data->m_semName);
	exit(1);
}

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

static void ReadData(int _msgQId, InputData* _data, sem_t* _pingCount)
{
	msgStruct reciveMsg;
	int pingNum = 5;
	
	/*get messgage from client*/
	if(msgRecive(_msgQId, -AUXILIARY_PORT, 0, &reciveMsg) < 0)
	{
		perror("msg recive");
	}
	
	/*ping stoped sending messages*/
	if(AUXILIARY_PORT == reciveMsg.m_type)
	{
		/*check that there are no pings left*/
		sem_getvalue(_pingCount, &pingNum);
		if(0 == pingNum)
		{
			exitProcess(_msgQId, _pingCount, _data);
		}
	}
	
	/*print message*/
	if(_data->m_verbosity)
	{
		printf("pong recived message: %s, from: %d\n", reciveMsg.m_info.m_data, reciveMsg.m_info.m_pid);
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
	sem_t* pingCount;
	
	msgQId = GetMsgQId(_data->m_create, _data->m_ftocFlag);
	pingCount = sem_open(_data->m_semName, O_CREAT | O_EXCL, 0644, 0);
	if(SEM_FAILED == pingCount)
	{
		perror("get semaphore");
		exit(1);
	}
	
	for(;;)
	{
		
		ReadData(msgQId, _data, pingCount);
		usleep(_data->m_sleepTime);
		SendData(msgQId, _data->m_verbosity);
	}
}

/*-----------------------------------------*/

static void ReadInput(int _argc, char** _argv, InputData* _input)
{	
	/*read input*/
	int opt;
	while ((opt = getopt(_argc, _argv, "s:f:n:vcd?")) != -1)
	{
		switch(opt)
		{
			case 's':
				_input->m_sleepTime = THOUSEND * (unsigned int)atoi(optarg);
				break;
			case 'f':
				_input->m_ftocFlag = atoi(optarg);
				break;
			case 'n':
				strcpy(_input->m_semName, optarg);
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
				fprintf(stderr, "Usage: %s [-l loops = number of loops] [-t type = s(server) / c(client)] \
				[-n semaphore name] [-c create new message queue] [-d destroy message queue at end]\n", _argv[0]);
				exit(1);
	 	}
	}
}


int main(int argc, char* argv[])
{
	InputData input = {SECOND, 'A', 0, 0, 0, "/sem"};
	
	ReadInput(argc, argv, &input);
	PongFunction(&input);
	return 1;
}
