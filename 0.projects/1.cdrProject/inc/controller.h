#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "retriver.h"

#define MAX_CONTEXT_SIZE 32
#define LINE_LENGTH 512

typedef struct ControllerData ControllerData;

typedef struct Controller Controller;

typedef enum
{
	MSISDN_RETRIVE = 1,
	OPERATOR_RETRIVE,
	ALL_SUBSCIBERS_REPORT,
	ALL_OPERATOR_REPORT,
	AGGREGATED_INFORMATION,
	PAUSE,
	RESUME,
	SHUT_DOWN
} CGFCommend;

typedef struct
{
	CGFCommend m_commend;
	char m_context[MAX_CONTEXT_SIZE];
} CommendMsg;

ControllerData* InitControllerData();

void DestroyControllerData(ControllerData* _data);

Controller* CreateController(ControllerData* _data);

int JoinController(Controller* _controller);

#endif /* __CONTROLLER_H__ */
