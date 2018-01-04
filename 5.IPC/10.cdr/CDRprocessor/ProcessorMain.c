#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "Recievers.h"
#include "processorConfigParser.h"
#include "CDRparser.h"
#include "communication.h"
#include "CGF.h"

#define CONFIG_PATH "../config/billerConfig.ini"

int main()
{
	RecieverData* data;
	Recievers* recivers;
	Recievers* uiHandler;
	ProcessorConfigue* config;
	
	config = ParseProcessorConfigue(CONFIG_PATH);
	data = CDRreciverInit(config);
	recivers = CreateCdrReadingThreads(data);
	uiHandler = CreateUIReadingThreads(data, recivers);
	
	JoinCdrRecieverThreads(recivers);
	JoinCdrRecieverThreads(uiHandler);
	
	DestroyProcessorConfig(config);
	DestroyRecieverData(data);
	
	return 1;
}
