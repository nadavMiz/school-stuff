#ifndef __MESSAGE_H__
#define __MESSAGE_H__
 
#define MAX_MSG_SIZE 128  /* maximum size for messeges to send */
#define RECIVER_PORT 4
#define WRITER_PORT 2
#define AUXILIARY_PORT 3

#define THOUSEND 1000
#define SECOND 1000000

typedef struct
{
	long m_type;
	struct msgInfo
	{
		int m_pid;
		char m_data[MAX_MSG_SIZE];
	} m_info;

} msgStruct; 

int CreateMsgQ(int _id);

int GetMsgQ(int _id);

void DestroyMsgQ(int _msqid);

int MsgSend(int _msgQid, long _msgType, const char* _data);

ssize_t msgRecive(int _msgQId, long _type, int _msgFlag, msgStruct* _dataRecive);

#endif /* __MESSAGE_H__ */
