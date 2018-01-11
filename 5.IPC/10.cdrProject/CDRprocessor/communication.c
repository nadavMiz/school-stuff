#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "communication.h"

#define DEFAULT_TYPE 2

typedef struct
{
	long m_type;
	char m_data[1];
} msgStruct;

int CreateChannel(int _flag)
{
	key_t key;
	Channel channel;
	
	key = ftok(FTOK_FILE, _flag);
	channel = msgget(key, 0666 | IPC_CREAT);
	if(channel < 0)
	{
		perror("create communication channel");
	}
	return channel;
}

int GetChannel(int _flag)
{
	key_t key;
	Channel channel;
	
	key = ftok(FTOK_FILE, _flag);
	channel = msgget(key, 0666 | IPC_CREAT);
	if(channel < 0)
	{
		perror("get communication channel");
	}
	return channel;
}

void DestroyChannel(int _channel)
{
	msgctl(_channel, IPC_RMID, NULL);
}

int MsgSend(int _channel, size_t _size, void* _data)
{
	int result;
	
	msgStruct* msg = malloc(sizeof(msgStruct) + _size*sizeof(char) - 1);
	if(NULL == msg)
	{
		fprintf(stderr, "allocation failed");
		return 0;
	}
	
	msg->m_type = DEFAULT_TYPE;
	memcpy(&(msg->m_data), _data, _size);
	result = msgsnd(_channel, msg, _size, 0);
	
	free(msg);
	
	return result;
}

int msgRecive(int _channel, size_t _size ,void* _data)
{
	int result;
	msgStruct* msg = malloc(sizeof(msgStruct) + _size*sizeof(char) - 1);
	if(NULL == msg)
	{
		fprintf(stderr, "allocation failed");
		return 0;
	}
	
	if((result = msgrcv(_channel, msg, _size, DEFAULT_TYPE, 0)) < 0)
	{
		free(msg);
		return result;
	}
	
	memcpy(_data, &(msg->m_data), _size);
	free(msg);
	return 1;
}
