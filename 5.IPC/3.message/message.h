#ifndef __MESSEGE_H__
#define __MESSEGE_H__
 
#define MAX_MSG_SIZE 128  /* maximum size for messeges to send */
#define RECIVER_PORT 4
#define WRITER_PORT 2
#define AUXILERY_PORT 3

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

int msgRecive(int _msgQId, long _type, int _msgFlag, msgStruct* _dataRecive);

#endif /* __MESSEGE_H__ */
