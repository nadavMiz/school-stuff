#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

#define FTOKFILE "message.c"

int CreateMsgQ(int _id)
{
	key_t key;
	int msqid;
	
	key = ftok(FTOKFILE, _id);
	msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
	return msqid;
}

int GetMsgQ(int _id)
{
	key_t key;
	int msqid;
	
	key = ftok(FTOKFILE, _id);
	msqid = msgget(key, 0);
	return msqid;
}

void DestroyMsgQ(int _msqid)
{
	msgctl(_msqid, IPC_RMID, NULL);
}

int MsgSend(int _msgQid, long _msgType, const char* _data)
{
	msgStruct msg;
	
	msg.m_type = _msgType;
	msg.m_info.m_pid = getpid();
	strcpy(msg.m_info.m_data, _data);
	return msgsnd(_msgQid, &msg, sizeof(msg.m_info), 0);
}

int msgRecive(int _msgQId, long _type, int _msgFlag, msgStruct* _msg)
{
	return msgrcv(_msgQId, _msg, sizeof(struct msgInfo), _type, _msgFlag);
}
