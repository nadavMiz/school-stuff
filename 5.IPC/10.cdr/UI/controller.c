#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>

#include "controller.h"
#include "communication.h"
#include "zlog4c.h"

#define CONFIG_PATH "../config/ControllerConf"
#define NUM_COMMENDS 6

struct Controller
{
	pthread_t m_thread;
};

struct ControllerData
{
	Channel m_inChannel;
	Channel m_outChannel;
	ZLog m_log;
};

/*--------------------------------------------*/

ControllerData* InitControllerData()
{
	ControllerData* data = malloc(sizeof(ControllerData));
	if(NULL == data)
	{
		return NULL;
	}
	
	data->m_inChannel = CreateChannel(UI_FROM_PROCESSOR_CHANNEL);
	data->m_outChannel = CreateChannel(UI_TO_PROCESSOR_CHANNEL);
	data->m_log = ZLogGet("#", CONFIG_PATH);
	
	return data;
}

/*--------------------------------------------*/

Controller* CreateControllerStruct()
{
	Controller* controller = malloc(sizeof(Controller));
	if(NULL == controller)
	{
		return NULL;
	}
	
	return controller;
}

/*--------------------------------------------*/

static void DestroyControllerStruct(Controller* _controller)
{
	free(_controller);
}

/*--------------------------------------------*/

static void PrintReply(ControllerData* _data)
{
	char responseStr[LINE_LENGTH];
	
	if(msgRecive(_data->m_inChannel, LINE_LENGTH, responseStr) < 0)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "msg recive failed error #%d", errno)
	}
	
	/*print response*/
	printf("%s\n", responseStr);
	
}

/*--------------------------------------------*/

void* ControllerFunc(ControllerData* _data)
{
	int isEnd = 0;
	int isPrintReply = 0;
	CommendMsg commend;
	
	while(!isEnd)
	{
		printf("what would you like to do\n");
		printf("1) retrieve subscribers data by MSIDN\n");
		printf("2) retrieve operators data by MCC\\MNC\n");
		printf("3) retrieve all subscribers report\n");
		printf("4) retrieve all operators report\n");
		printf("5) retrieve agregated report\n");
		printf("6) pause system\n");
		printf("7) resume system\n");
		printf("8) shut down system\n");
		
		scanf("%u", &(commend.m_commend));
		
		switch(commend.m_commend)
		{
			case MSISDN_RETRIVE:
				printf("please enter MSIDN\n");
				scanf("%s", commend.m_context);
				isPrintReply = 1;
				break;
				
			case OPERATOR_RETRIVE:
				printf("please enter MCC\\MNC\n");
				scanf("%s", commend.m_context);
				isPrintReply = 1;
				break;
			
			case SHUT_DOWN:
				isEnd = 1;
				break;
				
			case ALL_SUBSCIBERS_REPORT:
			case ALL_OPERATOR_REPORT:
			case AGGREGATED_INFORMATION:
			case PAUSE:
			case RESUME:
				break;
			
			default:
				printf("invalid argument: %d", commend.m_commend);
				continue;
		}
		
		/*send commend message*/		
		if(MsgSend(_data->m_outChannel, sizeof(CommendMsg), &commend) < 0)
		{
			ZLOG(_data->m_log, LOG_ERROR, "msg recive failed error #%d", errno)
			continue;
		}
		
		if(1 == isPrintReply)
		{
			PrintReply(_data);
			isPrintReply = 0;
		}
	}
	
	pthread_exit(NULL);
}

/*--------------------------------------------*/

Controller* CreateController(ControllerData* _data)
{
	Controller* controller = CreateControllerStruct();
	if(NULL == controller)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "allocation failed. cant create thread")
		return NULL;
	}
	
	if(0 != pthread_create(&(controller->m_thread), NULL, (void * (*)(void *))ControllerFunc, _data))
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "can't creat thread error #%d", errno)
		free(controller);
		return NULL;
	}
	
	return controller;
}

/*-------------------------------------------*/

int JoinController(Controller* _controller)
{
	int status;
	
	status = pthread_join(_controller->m_thread ,NULL);
	DestroyControllerStruct(_controller);
	
	return status;
}

/*------------------------------------------*/

void DestroyControllerData(ControllerData* _data)
{
	free(_data);
}
