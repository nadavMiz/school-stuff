#include <string.h>
#include <stdlib.h>

#include "queue.h"
#include "zlog4c.h"
#include "communication.h"
#include "CDRparser.h"
#include "fileDiscoverer.h"
#include "feederWatchdog.h"
#include "feederConfigParser.h"

#define CONFIG_PATH  "../config/billerConfig.ini"
#define LOG_PATH "../config/feederConf"
#define MASK ".cdr"
#define QUEUE_SIZE 10

int main()
{
	ZLog log;
	Queue* innerQueue;
	Channel outChannel;
	Channel uiInChannel;
	Channel uiOutChannel;
	FeederConfigue* feederConfig;
	ParserThreads* parser;
	Discoverer* discoverer;
	WachDogThread* watchdog;
	
	/*initialize stuff*/
	log = ZLogGet("#", LOG_PATH);
	innerQueue = QueueCreate(QUEUE_SIZE);
	outChannel = GetChannel(CDR_MOVER_CHANNEL);
	uiInChannel = GetChannel(PROCESSOR_TO_FEEDER);
	uiOutChannel = GetChannel(FEEDER_TO_PROCESSOR);
	feederConfig = ParseFeederConfigue(CONFIG_PATH);
	
	/*run threads*/
	parser = CreateParseThreads(innerQueue, outChannel, feederConfig->m_outputPath, log);
	discoverer = CreateFileDiscovererThread(innerQueue, feederConfig->m_inputPath, feederConfig->m_outputPath,
											 feederConfig->m_invalidPath, feederConfig->m_mask, log);
	watchdog = CreateWatchdog(uiInChannel, uiOutChannel, parser, discoverer);
	
	/*join threads*/
	JoinWatchDog(watchdog);
	JoinParseThreads(parser);
	JoinFileDiscoverer(discoverer);
	
	/*close stuff*/
	DestroyFeederConfig(feederConfig);
	QueueDestroy(innerQueue);
	
	return 1;
}
