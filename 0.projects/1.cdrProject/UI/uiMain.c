#include "communication.h"
#include "controller.h"

int main()
{
	ControllerData* data;
	Controller* controller;
	
	data = InitControllerData();
	
	controller = CreateController(data);
	JoinController(controller);
	
	DestroyControllerData(data);
}
